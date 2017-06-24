/*
 * MultipleTCPSocketListener.h
 *
 *  Created on: Mar 14, 2016
 *      Author: user
 */

#ifndef MULTIPLETCPSOCKETLISTENER_H_
#define MULTIPLETCPSOCKETLISTENER_H_

#include "TCPSocket.h"
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>
#define max_clients 30

using namespace std;

namespace npl {

class MultipleTCPSocketListener {

	vector<TCPSocket*> sockVec;
protected:

public:
	MultipleTCPSocketListener();
	/*
	 * add socket to listen
	 */
	void add(TCPSocket* sock);


	void add(vector<TCPSocket*> sockVec);

	/*
	 * listen to
	 */
	TCPSocket* listen(int timeout=0);

	virtual ~MultipleTCPSocketListener();
};

}

#endif /* MULTIPLETCPSOCKETLISTENER_H_ */
