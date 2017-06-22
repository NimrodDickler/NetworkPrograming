
#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "TCPSocket.h"
#include <errno.h>
#include <string.h>

using namespace std;


class MultipleTCPSocketsListener
{


public:
//	MultipleTCPSocketsListener();

	vector<TCPSocket*> socketVector;
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	bool addSocket(TCPSocket* socket);

	/*
	 * Set the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	void removeSocket(TCPSocket * sock);
	TCPSocket* listenToSocket();
	void RemoveAndCloseSocket(TCPSocket* socket);
};


#endif 
