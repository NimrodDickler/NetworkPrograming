/*
 * UDPSocket.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Eliav Menachi
 */

#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace npl;

UDPSocket::UDPSocket(int port){
	/**
	 * int socket(int domain, int type, int protocol);
	 * creates a UDP socket
	 * AF_INET - IPv4 Internet protocols
	 * SOCK_DGRAM - UDP
	 * 0 - default protocol type fo UDP
	 */
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

	// clear the s_in struct

	//sets the sin address

	//in case a port is given, bind the socket on the specified address

}

int UDPSocket::recv(char* buffer, int length){
	printf("UDP server receive ...\n");
	//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
	//					struct sockaddr *src_addr, socklen_t *addrlen);
}

int UDPSocket::sendTo(const string& msg,const string& ip, int port){
	return -1;
}

int UDPSocket::reply(const string& msg){
	return -1;
}

void UDPSocket::close(){
	cout<<"closing socket"<<endl;
	shutdown(socket_fd,SHUT_RDWR);
	::close(socket_fd);
}

string UDPSocket::fromAddr(){
	return inet_ntoa(from.sin_addr);
}



