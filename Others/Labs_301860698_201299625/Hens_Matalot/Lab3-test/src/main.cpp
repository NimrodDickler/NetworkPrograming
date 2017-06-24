/*
 * main.cpp
 *
 *  Created on: Mar 13, 2016
 *      Author: user
 */

#include <iostream>
#include <string.h>
#include "UdpSocketTest.h"
#include "TCPSocketTest.h"
#include "MultipleTCPSocketListenerTest.h"
#include "File.h"
using namespace std;
using namespace npl;

int main() {
	string path = "hello";
	char* path1 = new char[path.length()+1];
	strcpy(path1,path.c_str());
	File* file = new File(path1);
	string buff = "Bilabial";
	file->write(buff);
	puts("write to the file:");
	puts(buff.c_str());
	char* buff1 = new char[buff.length()+1];
	puts("read from file...\n");
	file->read(buff1,buff.length()+1);
	file->close();

	bool passFlag = true;
		UdpSocketTest udpTest;
		if(!udpTest.test()){
			passFlag = false;
			cerr<<endl<<"UDP test failed"<<endl;
	}

	TCPSocketTest tcpTest;
	if (!tcpTest.test()) {
		passFlag = false;
		cerr << endl << "TCP test failed" << endl;
	}

	if (passFlag) {
		cerr << endl << "*** TEST PASS ***" << endl;
	} else {
		cerr << endl << "*** TEST FAIL ***" << endl;
	}
	/*MultipleTCPSocketListenerTest multTCP;
	if (!multTCP.Test()) {
		passFlag = false;
		cerr << endl << "TCP test failed" << endl;
	}*/

	/*if (passFlag) {
		cerr << endl << "*** TEST PASS ***" << endl;
	} else {
		cerr << endl << "*** TEST FAIL ***" << endl;
	}*/
}

