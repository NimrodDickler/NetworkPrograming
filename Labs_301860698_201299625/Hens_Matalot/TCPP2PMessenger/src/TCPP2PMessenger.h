/*
 * TCPP2PMessenger.h
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#ifndef TCPP2PMESSENGER_H_
#define TCPP2PMESSENGER_H_

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "MThread.h"
#include <TCPSocket.h>
#include <unistd.h>
#include "P2PServer.h"
#include "P2PClient.h"
using namespace std;

namespace npl{
class TCPP2PMessenger{
	P2PServer* server;
	P2PClient* client;

public:
	TCPP2PMessenger(int port);

	virtual ~TCPP2PMessenger();
	void open(const string&ip,int port);
	void send(const string&msg);
	void reply(const string&msg);
	bool isActiveClientSession();
	bool isActivePeerSession();
	void close();
};
}
#endif /* TCPP2PMESSENGER_H_ */
