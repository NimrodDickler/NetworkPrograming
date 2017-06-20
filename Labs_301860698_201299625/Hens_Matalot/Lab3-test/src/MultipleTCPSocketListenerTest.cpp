/*

 * MultipleTCPSocketListenerTest.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: user


#include "MultipleTCPSocketListenerTest.h"

using namespace npl;

bool MultipleTCPSocketListenerTest::Test() {

	bool success = true;
	this->start();
	sleep(1);
	TCPSocket* Clients[Test_Size];

	for (int i = 0; i < Test_Size; i++) {
		TCPSocket* sock = new TCPSocket("127.0.0.1", 1234);
		Clients[i] = sock;
	}

	string msg = "12345678901234567890";
	char buff[1024];
	for (int i = 0; i < Test_Size; i++) {

		Clients[i]->send(msg);
		cout << "client sent: " << msg << endl;

		int rc = Clients[i]->recv(buff, sizeof(buff));
		cout<< rc << endl;
		buff[rc] = '\0';
		cout << "client recv: " << buff << endl;

		Clients[i]->close();
		delete Clients[i];

		if (rc == (int) msg.size()) {
			if (strcmp(msg.c_str(), buff) == 0) {
				cout<<"success"<<endl;


			}
		}
		if(i == Test_Size)
			return success;
	}

	for (int i = 0; i < Test_Size; i++) {
		Clients[i]->close();
		delete Clients[i];
	}
	cerr << "TCP test failed" << endl;
	waitForThread();
	success = false;
	return success;



}


void MultipleTCPSocketListenerTest::run(){
	vector<TCPSocket*> peerVec;
	TCPSocket* server = new TCPSocket(1234);

	for (int i = 0;i < Test_Size; i++) {
		this->snClient ++;
		TCPSocket* peer = server->listenAndAccept();
		printf("Client #%d is connected \n",this->snClient);
		peerVec.push_back(peer);
		MultipleTCPSocketListener listener;
		listener.add(peerVec);
		TCPSocket* readyPeer = listener.listen();
		char buff[1024];
			cout<<"got client connection"<<endl;
			int rc = readyPeer->recv(buff,sizeof(buff));
			buff[rc] = '\0';
			cout<<"server :"<<buff<<endl;
			readyPeer->send(buff);
			cout<<"server sent msg"<<endl;
		readyPeer->close();

		vector<TCPSocket*> ::iterator begin = peerVec.begin();
		vector<TCPSocket*> ::iterator end = peerVec.end();
		for (;begin!=end;begin++) {
			if(*begin ==readyPeer){
				peerVec.erase(begin);
				break;
			}

		}
		//delete peerVec;
	}


}

void MultipleTCPSocketListenerTest::readAndWriteFromPeer(TCPSocket* peer){

}
MultipleTCPSocketListenerTest::MultipleTCPSocketListenerTest() {
	this->snClient = 0;

}

MultipleTCPSocketListenerTest::~MultipleTCPSocketListenerTest() {
	// TODO Auto-generated destructor stub
}


*/
