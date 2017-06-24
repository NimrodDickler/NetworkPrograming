#include "TCPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

using namespace std;
using namespace npl;

TCPSocket::TCPSocket(int connected_sock, struct sockaddr_in serverAddr,
		struct sockaddr_in peerAddr) {
	this->serverAddr = serverAddr;
	this->peerAddr = peerAddr;
	socket_fd = connected_sock;
}

TCPSocket::TCPSocket(int port) {
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = (short) AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons((u_short) port);
	printf("TCP server binding...\n");
	if (bind(socket_fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr))
			< 0) {
		perror("Error naming channel");
	}
}

TCPSocket::TCPSocket(const string& peerIp, int port) {
	cout << "openning new client socket" << endl;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &peerAddr, sizeof(peerAddr)); /* They say you must do this    */
	peerAddr.sin_family = (short) AF_INET;
	peerAddr.sin_addr.s_addr = inet_addr(peerIp.data());
	peerAddr.sin_port = htons((u_short) port);
	if (connect(socket_fd, (struct sockaddr *) &peerAddr, sizeof(peerAddr))
			< 0) {
		perror("Error establishing communications");
		::close(socket_fd);
	}
}

TCPSocket* TCPSocket::listenAndAccept() {
	int rc = listen(socket_fd, 1);
	if (rc < 0) {
		return NULL;
	}
	socklen_t len = sizeof(peerAddr);
	bzero((char *) &peerAddr, sizeof(peerAddr));
	int connect_sock = accept(socket_fd, (struct sockaddr *) &peerAddr, &len);
	return new TCPSocket(connect_sock, serverAddr, peerAddr);
}

int TCPSocket::recv(char* buffer, int length) {
	return read(socket_fd, buffer, length);
}

int TCPSocket::send(char* msg, int size) {
	return write(socket_fd, msg, size);
}

void TCPSocket::close() {
	cout << "closing socket" << endl;
	shutdown(socket_fd, SHUT_RDWR);
	::close(socket_fd);
}

string TCPSocket::fromAddr() {
	return inet_ntoa(peerAddr.sin_addr);
}