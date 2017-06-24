/*
0 * MTCPListenerTest.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#include "MultipleTCPSocketsListener.h"
#include <unistd.h>
namespace npl {

#define TEST_SIZE 30
#define TEST_PORT 8768
bool MTCPListenerTest::test(){
	cout<<"MultipleTCPSocketsListener started"<<endl;
	start();
	sleep(1);
	bool testPass = true;
	//start the server on new thread

	//create TEST_SIZE client sockets
	TCPSocket* clients[TEST_SIZE];
	for(int i=0;i<TEST_SIZE;i++){
		clients[i] = new TCPSocket("127.0.0.1",TEST_PORT);
	}

	//w/r msg from each socket
	for(int i=0;i<TEST_SIZE;i++){
		if(!clientSendAndRecv(clients[i])){
			testPass=false;
		}
	}

	//w/r msg from each socket
	for(int i=0;i<TEST_SIZE;i++){
		if(!clientSendAndRecv(clients[i])){
			testPass=false;
		}
	}

	//close all sockets
	for(int i=0;i<TEST_SIZE;i++){
		clients[i]->close();
		delete clients[i];
	}
	waitForThread();
	cout<<"MultipleTCPSocketsListener ended"<<endl;
	return testPass;
}

bool MTCPListenerTest::clientSendAndRecv(TCPSocket* client){
	string msg = "12345678901234567890";
	client->send(msg);
	//cout<<"client sent: "<<msg<<endl;
	char buff[1024];
	int rc = client->recv(buff,sizeof(buff));
	buff[rc] = '\0';
	//cout<<"client recv: "<<buff<<endl;

	if(rc == (int)msg.size()){
		if(strcmp(msg.c_str(),buff) == 0){
			return true;
		}
	}
	return false;
}

bool MTCPListenerTest::serverRecvAndSend(TCPSocket* peer){
	char buff[1024];
	int rc = peer->recv(buff,sizeof(buff));

	buff[rc] = '\0';
	//cout<<"server recv: "<<buff<<endl;

	peer->send(buff);
	//cout<<"server sent: "<<buff<<endl;

	return true;
}

void MTCPListenerTest::run(){
	//the server implementation

	//open server socket
	TCPSocket* server = new TCPSocket(TEST_PORT);
	//cout<<"starting server"<<endl;

	//accept 5 client connections
	TCPSocket* peers[TEST_SIZE];
	vector<TCPSocket*> peersVec;

	for(int i=0;i<TEST_SIZE;i++){
		peers[i] = server->listenAndAccept();
		peersVec.push_back(peers[i]);
	}

	//r/w from peers
	for(int i=0;i<TEST_SIZE;i++){
		MTCPListener mtcpLis;
		for(int j=0;j<TEST_SIZE;j++){
			mtcpLis.add(peers[j]);
		}
		TCPSocket* readyPeer = mtcpLis.listen();
		//TCPSocket* readyPeer = peers[i];
		serverRecvAndSend(readyPeer);
	}

	//r/w from peers using vector
	for(int i=0;i<TEST_SIZE;i++){
		MTCPListener mtcpLis;
		mtcpLis.add(peersVec);
		TCPSocket* readyPeer = mtcpLis.listen();
		//TCPSocket* readyPeer = peers[i];
		serverRecvAndSend(readyPeer);
	}

	//close all peers
	for(int i=0;i<TEST_SIZE;i++){
		peers[i]->close();
		delete peers[i];
	}
	server->close();
	delete server;
}

} /* namespace npl */
