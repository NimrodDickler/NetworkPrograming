
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
	vector<TCPSocket*> socketVector;

	TCPSocket* listenToSocket();

	bool addSocket(TCPSocket* socket);

	void addSockets(vector<TCPSocket*> socketVec);

	void removeSocket(TCPSocket * sock);

	void RemoveAndCloseSocket(TCPSocket* socket);
};


#endif 
