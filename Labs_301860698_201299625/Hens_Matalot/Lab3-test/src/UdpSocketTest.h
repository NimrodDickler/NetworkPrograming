/*
 * UdpSocketTest.h
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#ifndef UDPSOCKETTEST_H_
#define UDPSOCKETTEST_H_

#include <iostream>
#include <string.h>
#include "UDPSocket.h"

using namespace std;
namespace npl{

class UdpSocketTest {
public:
	UdpSocketTest();
	virtual ~UdpSocketTest();
	bool test();

};
}
#endif /* UDPSOCKETTEST_H_ */
