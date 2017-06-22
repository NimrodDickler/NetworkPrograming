
#include "TCPMessengerServer.h"
#include "TCPMessengerProtocol.h"


/***********************   TCPMessengerServer implementation ******************************/

/**
 * Construct a TCP server socket
 */
TCPMessengerServer::TCPMessengerServer()
{
	this->isRunning = 1;
	this->dispatcher = NULL;
	this->tcpSocket = new TCPSocket(PORT);
	this->start();
}

/**
 * the messenger server main loop- this loop waits for incoming clients connection,
 * once a connection is established the new connection is added to the openedPeers
 * on which the dispatcher handle further communication
 */

void TCPMessengerServer::run()
{
	this->dispatcher = new Dispatcher();
	this->dispatcher->start();
	TCPSocket * peer;

	while(isRunning)
	{
		peer = this->tcpSocket->listenAndAccept();
		if((this->dispatcher->addPeer(peer))) {
			printf("New client has joined\n");
			this->listPeers();
		}

	}
}

/**
 * print out the list of connected clients (for debug)
 */
void TCPMessengerServer::listPeers()
{
	unsigned int i;

	for(i=0;i<this->dispatcher->peersMgr->socketVector.size();i++)
	{
		printf("IP : %s \n Port : %d \n\n",this->dispatcher->peersMgr->socketVector[i]->fromAddr().c_str(),htons(this->dispatcher->peersMgr->socketVector[i]->peerAddr.sin_port));
	}
}

/**
 * close the server
 */
void TCPMessengerServer::close()
{
	isRunning=0;
	sleep(1);
	this->tcpSocket->cclose();
}

