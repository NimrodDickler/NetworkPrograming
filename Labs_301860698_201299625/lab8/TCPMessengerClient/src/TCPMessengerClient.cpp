/*
 * TCPMessengerClient.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: user
 */

#include "TCPMessengerClient.h"

using namespace npl;


TCPMessengerClient::TCPMessengerClient(){
	this->sock = NULL;
	this->stopRun = false;

}



void TCPMessengerClient::connect(const string& ip) {
if (this->stopRun==false)
{
	sock = new TCPSocket(ip, MSNGR_PORT);
	this->start();
	cout << "connecting to server" << ip << endl << flush;
}else
	cout<<"server already connected!"<<endl<<flush;
}

void TCPMessengerClient::openSession(const string& ipAndPort) {
	cout << "openSession with peer: " << ipAndPort << endl << flush;
	sendToServer(OPEN_SESSION_WITH_PEER, ipAndPort, sock);
}
void TCPMessengerClient::send(const string msg) {
	cout << "sending msg to peer: " << msg << endl << flush;
	sendToServer(SEND_MSG_TO_PEER, msg, sock);

}

void TCPMessengerClient::closeSession() {
	cout << "closeSession with server" << endl << flush;
	sendToServer(CLOSE_SESSION_WITH_PEER, "", sock);
}

void TCPMessengerClient::disconnect() {
	cout << "disconnect from server" << endl << flush;
	stopRun = false;
	sendToServer(EXIT, "", sock);
}

void TCPMessengerClient::sendToServer(int command, const string& data,TCPSocket* sock) {

	char com[4];
	*((int*) com) = htonl(command);
	/*char com[4];
	com = command;*/
	sock->send(com, 4);
	//sock->write(com,4);
	if (data.length() > 0) {
		char len[4];
		*((int*) len) = htonl(data.length());
		//sock->write(len ,4);
		sock->send(len, 4);
		char temp[data.length()];
		strcpy(temp, data.c_str());
		sock->send(temp,data.length());
//		sock->write(data.c_str(),data.length());
	}
}
void TCPMessengerClient::readFromServer(int& command, string& data,TCPSocket* sock) {
	int com;
	sock->recv((char*) &com, 4);
	command = ntohl(com);
	switch (command) {
	case SEND_MSG_TO_PEER:
		cout << "SEND_MSG_TO_PEER" << endl;
		char buff[1024];
			int len;
			sock->recv((char*) &len, 4);
			len = ntohl(len);
			sock->recv(buff, len);
			buff[len] = '\0';
			data = buff;
			cout<< data << endl;
			break;
	case OPEN_SESSION_WITH_PEER:
		char buff1[1500];
		int len1;
		sock->recv((char*) &len1, 4);
		len = ntohl(len1);
		sock->recv(buff1, len);
		cout << len << endl;
		buff1[len] = '\0';
		data = buff1;
		break;
	default:
		break;
	}
}
void TCPMessengerClient::run(){
	int command ;
	string data ;
	stopRun = true;
	//sleep(1);
	while(stopRun){
		this->readFromServer(command,data,sock);
	}
cout<< "stop receiving data"<<endl;

}

TCPMessengerClient::~TCPMessengerClient() {
	// TODO Auto-generated destructor stub
}

