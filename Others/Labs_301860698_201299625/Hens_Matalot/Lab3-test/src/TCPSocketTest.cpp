/*
 * TcpSocketTest.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#include "TCPSocketTest.h"


using namespace npl;

bool TCPSocketTest::test(){
	start();
	sleep(1);

	TCPSocket* client = new TCPSocket("127.0.0.1",1234);
	string msg = "12345678901234567890";
	char* buff1= new char[msg.length()+1];
	strcpy(buff1,msg.c_str());
	client->write(buff1,strlen(buff1));
	char buff[1024];
	int rc = client->read(buff,sizeof(buff));
	buff[rc] = '\0';
	client->close();
	delete client;

	if(rc == (int)msg.size()){
		if(strcmp(msg.c_str(),buff) == 0){
			return true;
		}
	}
	cerr<<"TCP test failed"<<endl;
	waitForThread();
	return false;
}

void TCPSocketTest::run(){
	cout<<"open server"<<endl;
	TCPSocket* server = new TCPSocket(1234);
	TCPSocket* peer = server->listenAndAccept();
	char buff[1024];
	cout<<"got client connection"<<endl;
	int rc = peer->read(buff,sizeof(buff));
	buff[rc] = '\0';
	cout<<"server :"<<buff<<endl;
	peer->write(buff,1024);
	cout<<"server sent msg"<<endl;
	peer->close();
	server->close();
	delete peer;
	delete server;
}
