#include "Dispatcher.h"
#include "Broker.h"

/*
 * Inits members
 */
Dispatcher::Dispatcher() {
	this->peersMgr = new MultipleTCPSocketsListener();
	this->peersMap = new map<string, TCPSocket *>();
}
/*
 * Adds a new peer connection to the server vector handler
 */
bool Dispatcher::addPeer(TCPSocket * peer) {
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
/*
 * Removes a peer from server connected peers, closing session if he has one open
 */
bool Dispatcher::removePeer(TCPSocket * peer) {
	string address = peer->addrPort();
	if (this->peersMap->find(address) != this->peersMap->end())
		this->peersMap->erase(address);
	this->peersMgr->RemoveAndCloseSocket(peer);
	return true;
}
/*
 * Begins the thread
 */
void Dispatcher::run() {
	this->listenToMessages();
}
/*
 * Endless loop to listen to messages from peers and handle them
 */
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
/*
 * Opens a new session, session peer is the connecting side, received message for ip:port is the connected side
 */
void Dispatcher::startSession(TCPSocket * sessionPeer) {
	int size, msg;
	string peerAddress, lastPeer;
	char * temp;
	msg = sessionPeer->recv((char*) &size, 4);
	size = ntohs(size);
	temp = new char[size + 1];
	sessionPeer->recv(temp, size);
	temp[size] = '\0';
	//
	char buffer[1024];
	string sessionPeerAddress = sessionPeer->addrPort();
	Broker * broker;
	int bufferSize;
	bufferSize = sessionPeer->recv(buffer, SIZE);
	buffer[bufferSize] = '\0';
	peerAddress = buffer;
	int command = htonl(SESSION_REFUSED);
	if (this->peersMap->find(sessionPeerAddress) != this->peersMap->end()
			&& this->peersMap->find(peerAddress) != this->peersMap->end()) {
		if (this->peersMap->at(sessionPeerAddress) != NULL
				&& this->peersMap->at(peerAddress) != NULL) {
			broker = new Broker(this, sessionPeer, this->peersMap->at(peerAddress));
			broker->start();
			this->peersMgr->removeSocket(sessionPeer);
			this->peersMgr->removeSocket(this->peersMap->at(peerAddress));
			this->peersMap->at(peerAddress) = NULL;
			this->peersMap->at(sessionPeerAddress) = NULL;
		} else {
			sessionPeer->send((char*) &command, 4);
		}
	} else {
		sessionPeer->send((char*) &command, 4);
	}
}
void Dispatcher::openConnection(vector<TCPSocket*> tcpSocketVector,
		TCPSocket * exitSocket) {
	for (unsigned int i = 0; i < tcpSocketVector.size(); i++) {
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
/*
 * Closes sessionPeer's session, closes both sides
 */

Dispatcher::~Dispatcher() {
	for (unsigned int i = 0; i < this->peersMgr->socketVector.size(); i++)
		this->peersMgr->socketVector[i]->cclose();
	delete this->peersMgr;
	delete this->peersMap;
}

