/*
 * MultipleTCPSocketsListener.h.h
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#ifndef MTCPLISTENERTEST_H_
#define MTCPLISTENERTEST_H_

#include "MThread.h"
#include "MultipleTCPSocketsListener.h"
#include <iostream>
#include <string.h>

using namespace std;
namespace npl {

class MTCPListenerTest :public MThread{
public:
	bool test();
	void run();

private:
	bool clientSendAndRecv(TCPSocket* client);
	bool serverRecvAndSend(TCPSocket* peer);

};

} /* namespace npl */

#endif /* MTCPLISTENERTEST_H_ */
