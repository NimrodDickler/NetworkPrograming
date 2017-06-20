/*
 * P2PClient.h
 *
 *  Created on: Mar 28, 2016
 *      Author: user
 */

#ifndef P2PCLIENT_H_
#define P2PCLIENT_H_

#include <iostream>
#include <string.h>
#include <pthread.h>
#include "MThread.h"
#include <TCPSocket.h>
#include <unistd.h>


using namespace std;
namespace npl{
class P2PClient:public MThread {
	TCPSocket* client;

	bool done;
public:
	bool runing;
	P2PClient(const string&ip,int port);
	virtual ~P2PClient();
	bool open(const string&ip,int port);
	void send(const string&msg);
	void run();
	void close();
};
}
#endif /* P2PCLIENT_H_ */
