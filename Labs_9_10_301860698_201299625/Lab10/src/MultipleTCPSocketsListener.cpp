
#include "MultipleTCPSocketsListener.h"

using namespace std;

bool MultipleTCPSocketsListener::addSocket(TCPSocket* socket) {
	// add new socket to the socket maps
	this->socketVector.push_back(socket);
	return true;
}

void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec) {
	this->socketVector.clear();
	this->socketVector = socketVec;
}

// listen to all active peers for new incoming messages
TCPSocket* MultipleTCPSocketsListener::listenToSocket() {
	fd_set SocketSet;
	int check, maxfd = 0;
	timeval timeout;
	FD_ZERO(&SocketSet);

	// in case of no active peers
	if (this->socketVector.size() == 0)
		return NULL;

	// once receive new message from peer, return the peer socket
	for (unsigned int i = 0; i < this->socketVector.size(); i++) {
		FD_SET(this->socketVector[i]->getSocketFid(), &SocketSet);
		if (this->socketVector[i]->getSocketFid() > maxfd)
			maxfd = this->socketVector[i]->getSocketFid();
	}
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	sleep(0.5);
	check = select(maxfd + 1, &SocketSet, NULL, NULL, &timeout);
	if (check == -1) {
		perror("Error has occured");
	} else {
		for (unsigned int i = 0; i < this->socketVector.size(); i++) {
			if (FD_ISSET(this->socketVector[i]->getSocketFid(), &SocketSet)) {
				FD_CLR(this->socketVector[i]->getSocketFid(), &SocketSet);
				return this->socketVector[i];
			}
		}
	}
	// no incoming messages
	return NULL;
}

void MultipleTCPSocketsListener::removeSocket(TCPSocket * sock) {
	// remove the needed peer for the socket map
	for (unsigned int i = 0; i < socketVector.size(); i++)
		if (this->socketVector[i]->getSocketFid() == sock->getSocketFid())
			this->socketVector.erase(this->socketVector.begin() + i);
}

void MultipleTCPSocketsListener::RemoveAndCloseSocket(TCPSocket* socket) {
	// remove the needed peer for the socket map and close the socket connection
	for (unsigned int i = 0; i < socketVector.size(); i++)
		if (this->socketVector[i]->getSocketFid() == socket->getSocketFid()) {
			this->socketVector.erase(this->socketVector.begin() + i);
			socket->cclose();
			return;
		}
}

