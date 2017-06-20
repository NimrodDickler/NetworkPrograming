/*
 * P2PClient.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: user
 */

#include "P2PClient.h"
using namespace npl;
P2PClient::P2PClient(const string&ip, int port) {
	done = true;
	runing = false;
	client = new TCPSocket(ip, port);

}

void P2PClient::run() {
	while (done) {
		while (runing) {
			char buffer[1024];
			//sleep(2);
			int n = client->recv(buffer, sizeof(buffer));
			if (n < 0) {
				break;
			}
			buffer[n] = '\0';
			cout << endl << "P2PClient receive msg--->" << buffer << endl;

		}
	}
	cout << "closing receiver thread" << endl;
}

bool P2PClient::open(const string&ip, int port) {
	if (client == NULL) {
		return false;
	}
	return true;
}

void P2PClient::send(const string&msg) {
	client->send(msg);
}

void P2PClient::close() {
	done = false;
	client->close();
}
P2PClient::~P2PClient() {
	// TODO Auto-generated destructor stub
}
