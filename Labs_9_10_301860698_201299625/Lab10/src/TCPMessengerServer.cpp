
#include "TCPMessengerServer.h"
#include "TCPMessengerProtocol.h"

TCPMessengerServer::TCPMessengerServer()
{
	this->isRunning = 1;
	this->dispatcher = NULL;
	this->tcpSocket = new TCPSocket(PORT);
	this->start();
}

void TCPMessengerServer::run()
{
	this->dispatcher = new Dispatcher();
	this->dispatcher->start();
	TCPSocket * peer;


	// wait for client to be connected
	while(isRunning)
	{
		peer = this->tcpSocket->listenAndAccept();
		// and the new peer to the dispatcher peers list
		if((this->dispatcher->addPeer(peer))) {
			printf("New client has joined:\n");
			cout << peer->fromAddr().c_str() << ":" << ntohs(peer->peerAddr.sin_port) << endl;
		}
	}
}

void TCPMessengerServer::listPeers()
{
	unsigned int i;
	for(i=0;i<this->dispatcher->peersMgr->socketVector.size();i++)
	{
		cout << "Online Peers:" << endl;
		printf("IP : %s \n Port : %d \n\n",this->dispatcher->peersMgr->socketVector[i]->fromAddr().c_str(),htons(this->dispatcher->peersMgr->socketVector[i]->peerAddr.sin_port));
	}
}

void TCPMessengerServer::close()
{
	isRunning=0;
	sleep(1);
	this->tcpSocket->cclose();
}

