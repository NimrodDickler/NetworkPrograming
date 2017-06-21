/*
 * TCPSocket.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>

using namespace std;

namespace npl {

class TCPSocket {
	struct sockaddr_in serverAddr;
	struct sockaddr_in peerAddr;
	int socket_fd;

private:
	TCPSocket(int connected_sock, struct sockaddr_in serverAddr,
			struct sockaddr_in peerAddr);

public:
	TCPSocket(int port);

	TCPSocket(const string& peerIp, int port);

	TCPSocket* listenAndAccept();

	int recv(char* buffer, int length);

	int send(char* msg, int size);

	void close();

	string fromAddr();
};
}

#endif
