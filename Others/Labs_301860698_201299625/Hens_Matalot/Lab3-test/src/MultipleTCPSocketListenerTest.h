/*

 * MultipleTCPSocketListenerTest.h
 *
 *  Created on: Mar 14, 2016
 *      Author: user


#ifndef MULTIPLETCPSOCKETLISTENERTEST_H_
#define MULTIPLETCPSOCKETLISTENERTEST_H_
#include "TCPSocketTest.h"
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "TCPSocket.h"
#include <vector>
#include "MultipleTCPSocketListener.h"
using namespace std;
namespace npl {

#define Test_Size 10
class MultipleTCPSocketListenerTest: public MThread {
protected:
	int snClient;
public:
	bool Test();
	void run();
	MultipleTCPSocketListenerTest();
	virtual ~MultipleTCPSocketListenerTest();

private:
	void readAndWriteFromPeer(TCPSocket* peer);
};

}  namespace npl

#endif  MULTIPLETCPSOCKETLISTENERTEST_H_
*/
