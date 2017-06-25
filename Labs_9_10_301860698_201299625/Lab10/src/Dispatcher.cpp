#include "Dispatcher.h"
#include "Broker.h"

Dispatcher::Dispatcher() {
	// init for listen for new messages from the active peers
	this->peersMgr = new MultipleTCPSocketsListener();

	this->peersMap = new map<string, TCPSocket *>();
}

bool Dispatcher::addPeer(TCPSocket * peer) {
	// add new peer to map, by ip and port
	char * temp = new char[SIZE];
	string address;
	if (this->peersMgr->addSocket(peer)) {
		snprintf(temp, SIZE, "%s:%d", peer->fromAddr().c_str(),
				ntohs(peer->peerAddr.sin_port));
		address = temp;
		this->peersMap->insert(pair<string, TCPSocket*>(address, peer));
		return true;
	}
	return false;
}
bool Dispatcher::removePeer(TCPSocket * peer) {
	// remove active peer from map
	string address = peer->addrPort();
	if (this->peersMap->find(address) != this->peersMap->end())
		this->peersMap->erase(address);
	this->peersMgr->RemoveAndCloseSocket(peer);
	return true;
}

void Dispatcher::run() {
	// wait from new incoming message
	this->listenToMessages();
}

// wait for peering request from one of the active peers
void Dispatcher::listenToMessages() {
	TCPSocket * newSocket;
	int command;

	while (1) {
		newSocket = this->peersMgr->listenToSocket();
		if (newSocket == NULL)
			continue;

		newSocket->recv((char*) &command, 4);
		command = htonl(command);
		if (command == OPEN_SESSION_WITH_PEER)
			this->startSession(newSocket);
		sleep(0.5);
	}
}

void Dispatcher::startSession(TCPSocket * sessionPeer) {
	int size, msg;
	char * temp;
	string peerAddress, lastPeer;
	string sessionPeerAddress = sessionPeer->addrPort();
	Broker * broker;

	msg = sessionPeer->recv((char*) &size, 4);
	size = ntohs(size);
	temp = new char[size + 1];
	sessionPeer->recv(temp, size);
	temp[size] = '\0';

	char buffer[SIZE];
	size = sessionPeer->recv(buffer, SIZE);
	buffer[size] = '\0';
	peerAddress = buffer;
	int command = htonl(SESSION_REFUSED);
	// verify that the target and the source peers are valid and active
	if (this->peersMap->find(sessionPeerAddress) != this->peersMap->end()
			&& this->peersMap->find(peerAddress) != this->peersMap->end()) {
		if (this->peersMap->at(sessionPeerAddress) != NULL
				&& this->peersMap->at(peerAddress) != NULL) {
			// peer the two clients & remove from the active peer map
			broker = new Broker(this, sessionPeer, this->peersMap->at(peerAddress));
			this->peersMgr->removeSocket(sessionPeer);
			this->peersMgr->removeSocket(this->peersMap->at(peerAddress));
			this->peersMap->at(peerAddress) = NULL;
			this->peersMap->at(sessionPeerAddress) = NULL;
			broker->start();
		} else {
			// return connection refuse in case of invalid source or target
			sessionPeer->send((char*) &command, 4);
		}
	} else {
		// return connection refuse in case of invalid source or target
		sessionPeer->send((char*) &command, 4);
	}
}

void Dispatcher::openConnection(vector<TCPSocket*> tcpSocketVector,
		TCPSocket * exitSocket) {
	for (unsigned int i = 0; i < tcpSocketVector.size(); i++) {
		// in case of closing peer to peer connection, return the clients to active peers map
		if (this->peersMap->find(tcpSocketVector[i]->addrPort())
				!= this->peersMap->end()) {
			string address = tcpSocketVector[i]->addrPort();
			this->peersMap->at(address) = tcpSocketVector[i];
			this->peersMgr->addSocket(tcpSocketVector[i]);
		}
	}
	if (exitSocket != NULL)
		this->removePeer(exitSocket);
}

Dispatcher::~Dispatcher() {
	for (unsigned int i = 0; i < this->peersMgr->socketVector.size(); i++)
		this->peersMgr->socketVector[i]->cclose();
	delete this->peersMgr;
	delete this->peersMap;
}

