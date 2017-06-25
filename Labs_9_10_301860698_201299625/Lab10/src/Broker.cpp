#include "Broker.h"

Broker::Broker(Dispatcher * dis, TCPSocket * peerOne, TCPSocket * peerTwo) {

	int command = htonl(SESSION_ESTABLISHED);

	this->dispatcher = dis;

	this->socketListener.addSocket(peerOne);
	this->socketListener.addSocket(peerTwo);

	// send session established to both peers.
	peerOne->send((char*) &command, 4);
	peerTwo->send((char*) &command, 4);

}

void Broker::run() {
	TCPSocket * callingSocket;
	int command;
	while (1) {
		// waiting for incoming command from one of the active peers
		callingSocket = this->socketListener.listenToSocket();
		if (callingSocket == NULL)
			continue;
		callingSocket->recv((char*) &command, 4);
		command = ntohl(command);
		switch (command) {
		case CLOSE_SESSION_WITH_PEER:
			this->close(false, NULL);
			break;
		case EXIT:
			this->close(true, callingSocket);
			break;
		case SEND_MSG_TO_PEER:
			this->sendMessage(callingSocket);
			break;
		}
	}
}

void Broker::sendMessage(TCPSocket * sender) {

	int size, msg;
	for (unsigned int i = 0; i < this->socketListener.socketVector.size();
			i++) {
		if (this->socketListener.socketVector[i]->getSocketFid()
				!= sender->getSocketFid()) {
			// get the message size
			msg = sender->recv((char*) &size, 4);
			size = ntohl(size);
			char temp[size + 1];
			// get the message content
			msg = sender->recv(temp, size);
			temp[size] = '\0';
			string data = temp;

			char com[4];
			*((int*) com) = htonl(SEND_MSG_TO_PEER);
			// send incoming message command for the second peer
			this->socketListener.socketVector[i]->send(com, 4);
			char len[4];
			*((int*) len) = htonl(size);
			// send message size
			this->socketListener.socketVector[i]->send(len, 4);
			strcpy(temp, data.c_str());
			// send message content
			this->socketListener.socketVector[i]->send(temp, data.length());
		}
	}

}

void Broker::close(bool closeConn, TCPSocket * closeSocket) {
	if (closeConn)
		this->dispatcher->openConnection(this->socketListener.socketVector,
				closeSocket);
		// in case of closing connection between peers and server
	else
		this->dispatcher->openConnection(this->socketListener.socketVector);
		// in case closing connection between peers but return the active peers map

}

Broker::~Broker() {
	if (dispatcher != NULL)
		delete dispatcher;
}

