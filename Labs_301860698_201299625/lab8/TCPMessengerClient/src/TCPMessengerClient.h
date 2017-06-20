/*
 * TCPMessengerClient.h
 *
 *  Created on: Apr 21, 2016
 *      Author: user
 */

#ifndef TCPMESSENGERCLIENT_H_
#define TCPMESSENGERCLIENT_H_
#include <iostream>
#include <string.h>
#include <pthread.h>
#include "MThread.h"
#include "TCPSocket.h"
#include <unistd.h>
#include"TCPMessengerProtocol.h"

using namespace std;

namespace npl {

class TCPMessengerClient :public MThread{
	TCPSocket* sock;
	bool stopRun ;
public:
	TCPMessengerClient();
	void connect(const string& ip);
	void openSession(const string& ipAndPort);
	void send(const string msg);
	void closeSession();
	void disconnect();

	void sendToServer(int command, const string& data,TCPSocket* sock);
	void readFromServer(int& command, string& data,TCPSocket* sock);
	void run();

	virtual ~TCPMessengerClient();
};

} /* namespace npl */

#endif /* TCPMESSENGERCLIENT_H_ */
