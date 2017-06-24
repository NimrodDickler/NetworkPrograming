/*
 * TCPSocket.h
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Socket.h"
using namespace std;

namespace npl{
class TCPSocket:public Socket {


	bool isClient;

public:

	TCPSocket(int port);
	TCPSocket(const string &ip,int port);
	TCPSocket* listenAndAccept();
	int reply(const string& msg);
	int get_fd();
	virtual ~TCPSocket();
	struct sockaddr_in get_from();
private:
	TCPSocket(struct sockaddr_in from,int connectSock,bool isClient);

};
}
#endif /* TCPSOCKET_H_ */

