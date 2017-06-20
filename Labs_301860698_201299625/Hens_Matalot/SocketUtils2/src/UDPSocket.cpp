/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#include "UDPSocket.h"

using namespace npl;


UDPSocket::UDPSocket() {
socket_fd = socket(AF_INET,SOCK_DGRAM,0);
}

UDPSocket::UDPSocket(int port) {
	// TODO Auto-generated constructor stub
	/**
		 * int socket(int domain, int type, int protocol);
		 * creates a UDP socket
		 * AF_INET - IPv4 Internet protocols
		 * SOCK_DGRAM - UDP
		 * 0 - default protocol type fo UDP
		 */
		socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
		bind(port);
}

UDPSocket::~UDPSocket() {
	// TODO Auto-generated destructor stub
}

int UDPSocket::sendTo(const string& msg,const string& ip,int port){
	struct sockaddr_in s_in;
			bzero ((char *) &s_in, sizeof (s_in));

			s_in.sin_family = (short)AF_INET;
			s_in.sin_addr.s_addr = inet_addr(ip.c_str());
			s_in.sin_port = htons(port);

			int n = sendto(socket_fd , msg.c_str() , msg.length() , 0 , (struct sockaddr*)&s_in , sizeof(s_in));
			if(n<0){
				perror("SendTo: error");
			}
			return n;
}

int UDPSocket::reply(const string& msg){
	//socklen_t fsize = sizeof(from);
		int n = sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr*)&from,sizeof(from));
		if(n < 0){
			perror("Reply: error");
		}
		return n;
}


int UDPSocket::read(char* buffer, int length){
	printf("UDP server receive ...\n");
	//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
	//					struct sockaddr *src_addr, socklen_t *addrlen);
	//bzero ((char *) &from, sizeof (from));
	socklen_t fsize = sizeof(from);
	ssize_t res = recvfrom(socket_fd, buffer, length, 0,(struct sockaddr *)&from,&fsize);
	if(res<0){
		perror("Recive: error");
	}
	return res;

}

int UDPSocket::write(const string& msg){
	return -1;
}

