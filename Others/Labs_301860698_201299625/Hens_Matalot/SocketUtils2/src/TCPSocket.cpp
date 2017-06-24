/*
 * TCPSocket.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#include "TCPSocket.h"
using namespace npl;
/*TCP Server constructor.
 * The constructor resets the struct and binding.
*/
TCPSocket::TCPSocket(int port) {

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	isClient = false;
	if (socket_fd < 0) {
		perror("Error opening channel");
		clean_up(1, &socket_fd);

	}
	bind(port);
}
/*TCP client constructor.
 * The constructor resets the struct and connect to server.
*/
TCPSocket::TCPSocket(const string &ip, int port) {
	printf("Client is alive and establishing socket connection.\n");
	isClient = true;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("Error opening channel");
		::close(socket_fd);
		exit(1);
	}

	connect(ip,port);

}
/*
 * private constructor of the server.
 * construct new object of TCPSocket for handling a new client
 */
TCPSocket::TCPSocket(struct sockaddr_in from,int connectSock,bool isClient){
	bzero(&this->from,sizeof(from));
	this->from = from;
	this->socket_fd = connectSock;
	this->isClient = isClient;
}
/*
 * The method listen to the socket and wait for connection from any client.
 * accept the connection make new socket and make new object with the private c'tor.
 */
TCPSocket* TCPSocket::listenAndAccept() {

	if (!isClient) {
		struct sockaddr_in peer;
		int connectSock;
		listen(socket_fd, 1);
	    //printf("Server is alive and waiting for socket connection from client.\n");
		socklen_t len = sizeof(peer);

		connectSock = accept(socket_fd, (struct sockaddr *) &peer, &len);

		return new TCPSocket(peer, connectSock,0);
	} else
		printf("Server function please create server");
	return NULL;
}




int TCPSocket::reply(const string& msg){
	int n = sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr*)&from,sizeof(from));
	if(n < 0){
		perror("Reply: error");
	}
	return n;
}


TCPSocket::~TCPSocket() {

}


int TCPSocket::get_fd(){
	return this->socket_fd;
}

struct sockaddr_in TCPSocket::get_from(){
	return from;
}



