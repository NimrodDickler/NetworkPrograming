/*
 * P2PServer.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: user
 */

#include "P2PServer.h"
using namespace npl;
P2PServer::P2PServer(int port) {
	cout << "open server" << endl;
	runing = true;
	this->server = new TCPSocket(port);
	this->peer = NULL;
	this->start();

}

void P2PServer::reply(const string&msg){
	peer->reply(msg);
		cout << "server sent msg back to client" << endl;
}

void P2PServer::close(){
	cout<< "P2PServer::close"<<endl;
	runing = false;
	server->close();
}

void P2PServer::run(){
	peer = this->server->listenAndAccept();
while(runing){

	//TCPSocket* peerClient = peer;
	char buff[1024];
	cout << "got client connection" << endl;
	int rc = peer->recv(buff, sizeof(buff));
	if( rc < 0){
		perror ("p2pserver run: recve error");
	}
	buff[rc] = '\0';
	cout << "P2PServer the recvie msg ---> :" << buff << endl;
	cout << "P2PServer from ---> :" << peer->fromAddr() << endl;

}

}
P2PServer::~P2PServer() {
	cout<< "P2PServer::d'tor"<<endl;

}
