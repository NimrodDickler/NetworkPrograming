/*
 * TCPSocket.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#include "TCPSocket.h"
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

	bzero(&from, sizeof(from));
	from.sin_family = AF_INET;
	from.sin_port = htons(port);

	if (bind(socket_fd, (struct sockaddr *) &from, sizeof(from)) < 0) {
		perror("Error naming channel");
		clean_up(2, &socket_fd);
	}
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

	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(ip.c_str());
	dest.sin_port = htons(port);

	if (connect(socket_fd, (struct sockaddr *) &dest, sizeof(dest)) < 0) {
		perror("Error establishing communications");
		::close(socket_fd);
		exit(1);
	}

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
/*
 * receive stream from source.
 */
int TCPSocket::recv(char* buffer, int length) {
	socklen_t fsize = sizeof(from);
	ssize_t res = recvfrom(socket_fd, buffer, length, 0,(struct sockaddr *)&from,&fsize);
	if(res<0){
		perror("Recive: error");
		clean_up(2,&socket_fd);
	}


	return res;
}
/*
 * send stream from source.
 */
int TCPSocket::send(const string& msg) {

	int n = sendto(socket_fd, msg.c_str(), msg.length(), 0,(struct sockaddr*) &dest, sizeof(dest));
	if (n < 0) {
		perror("SendTo: error");
		clean_up(2,&socket_fd);
	}

	return 0;

}
/*
 * The method stop send or receive files and close the socket.
 */
void TCPSocket:: close(){
	cout<<"closing socket"<<endl;
		shutdown(socket_fd,SHUT_RDWR);
		::close(socket_fd);
}
/*
 * The method return the IP of the source
 */
string TCPSocket::fromAddr(){

	return inet_ntoa(from.sin_addr);

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


/*
 * The method exit safely
 */
void TCPSocket::clean_up(int cond, int *sock) {
	printf("Exiting now.\n");

	::close(*sock);
	exit(cond);
}
