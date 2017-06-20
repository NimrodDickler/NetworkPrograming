/*
 * TCPP2PMessenger.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#include "TCPP2PMessenger.h"

using namespace npl;

TCPP2PMessenger::TCPP2PMessenger(int port) {

	cout << "TCPP2PMessenger :" << port << endl;
	server = new P2PServer(port);
	client = NULL;


}

TCPP2PMessenger::~TCPP2PMessenger() {
	// TODO Auto-generated destructor stub
}

void TCPP2PMessenger::open(const string&ip, int port) {
	cout << "TCPPTPMessenger: open" <<" "<< ip << ":" << port << endl;
	client = new P2PClient(ip,port);
	client->open(ip,port);



}

void TCPP2PMessenger::send(const string&msg) {
	cout << "tcpp2pmessenger:send" << msg << endl;
	client->send(msg);
}

void TCPP2PMessenger::reply(const string&msg) {
	cout << "tcpp2pmessenger:reply" << msg << endl;
	client->runing = true;
	client->start();
	server->reply(msg);
}

bool TCPP2PMessenger::isActivePeerSession() {
	return 0;
}

bool TCPP2PMessenger::isActiveClientSession() {
	return 0;
}

void TCPP2PMessenger::close() {
	cout << "tcpp2pmessenger:close" << endl;
	client->close();
	server->close();
}

