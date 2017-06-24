/*
 * P2PServer.h
 *
 *  Created on: Mar 28, 2016
 *      Author: user
 */

#ifndef P2PSERVER_H_
#define P2PSERVER_H_

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "MThread.h"
#include <TCPSocket.h>
#include <unistd.h>

using namespace std;
namespace npl {
class P2PServer:public MThread {
	TCPSocket* server;
	TCPSocket* peer;
	bool runing;
public:
	P2PServer(int port);
	virtual ~P2PServer();
	void reply(const string&msg);
	void close();
	void run();
};
}
#endif /* P2PSERVER_H_ */
