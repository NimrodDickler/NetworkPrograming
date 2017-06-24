//============================================================================
// Name        : UDPMessenger
// Author      : Eliav Menachi
// Version     :
// Copyright   : Your copyright notice
// Description : UDP Messenger application
//============================================================================

#include "UDPMessenger.h"


using namespace npl;

void UDPMessenger::run() {
	// receiver thread...
	while (runing) {
		char buffer[1024];
		int n = udpSocket->recv(buffer, sizeof(buffer));
		if(n < 0){
			break;
		}
		buffer[n] = '\0';
		cout<<endl<<"the msg--->"<< buffer<<endl;
	}
	cout << "closing receiver thread" << endl;

}

UDPMessenger::UDPMessenger() {
	// init the messenger
	udpSocket = new UDPSocket(MSNGR_PORT);
	runing = true;
	this->start();
}

void UDPMessenger::sendTo(const string& msg, const string& ip) {
	udpSocket->sendTo(msg, ip, MSNGR_PORT);
}

void UDPMessenger::reply(const string& msg) {
	udpSocket->reply(msg);
}

void UDPMessenger::close() {
	runing = false;
	udpSocket->close();
	waitForThread();
	delete udpSocket;
	udpSocket = NULL;
}


