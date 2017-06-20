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

using namespace std;
class TCPSocket {

	struct sockaddr_in from ,dest;
	bool isClient;

protected:
	int socket_fd;

public:
	TCPSocket(int port);
	TCPSocket(const string &ip,int port);
	TCPSocket* listenAndAccept();
    void clean_up(int cond, int *sock);
	int recv(char* buffer, int length);
	int send(const string& msg);
	void close();
	string fromAddr();
	int reply(const string& msg);
	int get_fd();

	virtual ~TCPSocket();
	struct sockaddr_in get_from();
private:
	TCPSocket(struct sockaddr_in from,int connectSock,bool isClient);

};

#endif /* TCPSOCKET_H_ */
