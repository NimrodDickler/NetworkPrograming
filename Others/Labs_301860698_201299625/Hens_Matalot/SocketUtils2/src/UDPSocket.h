/*
 * UDPSocket.h
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include "Socket.h"
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>

using namespace std;

namespace npl {

class UDPSocket:public Socket{


public:
	/**
	 * Client UDP socket ctor
	 */
	UDPSocket();

	/**
	 * Server UDP socket ctor
	 */
	UDPSocket(int port);
	int sendTo(const string& msg,const string& ip,int port);
	int reply(const string& msg);
	virtual ~UDPSocket();


	//override file interface

	virtual int read(char* buffer, int length);
	virtual int write(const string& msg);
};

} /* namespace npl */

#endif /* UDPSOCKET_H_ */
