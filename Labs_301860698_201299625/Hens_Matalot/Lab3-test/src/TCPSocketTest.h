/*
 * TCPSocketTest.h
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#ifndef TCPSOCKETTEST_H_
#define TCPSOCKETTEST_H_


#include "MThread.h"
#include "TCPSocket.h"
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

namespace npl{

class TCPSocketTest: public MThread {
public:
	bool test();
	void run();
};

}
#endif /* TCPSOCKETTEST_H_ */
