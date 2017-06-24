/*
 * Socket.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#include "Socket.h"

using namespace npl;

int Socket::bind(int port) {

	if (port != 9999) {
		struct sockaddr_in s_in;

		// clear the s_in struct
		bzero((char *) &s_in, sizeof(s_in));

		//sets the sin address
		//in case a port is given, bind the socket on the specified address
		s_in.sin_family = (short) AF_INET;
		s_in.sin_addr.s_addr = htonl(INADDR_ANY);
		s_in.sin_port = htons(port);
		int rc = ::bind(socket_fd, (struct sockaddr*) &s_in, sizeof(s_in)) < 0;
		if (rc < 0) {
			printf("Error naming channel");

		}
		return rc;
	}
	return 0;

}

int Socket::connect(const string& ip, int port) {
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(ip.c_str());
	dest.sin_port = htons(port);
	int rc = ::connect(socket_fd, (struct sockaddr *) &dest, sizeof(dest));
	if (rc < 0) {
		perror("Error establishing communications");
		::close(socket_fd);
		exit(1);
	}
	return rc;
}

void Socket::close() {
	shutdown(socket_fd, SHUT_RDWR);
	::close(socket_fd);
}


/*
 * The method return the IP of the source
 */
string Socket::fromAddr() {

	return inet_ntoa(from.sin_addr);

}

/*
 * The method exit safely
 */
void Socket::clean_up(int cond, int *sock) {
	printf("Exiting now.\n");

	::close(*sock);
	exit(cond);
}

Socket::Socket() {

}

Socket::~Socket() {
	// TODO Auto-generated destructor stub
}

