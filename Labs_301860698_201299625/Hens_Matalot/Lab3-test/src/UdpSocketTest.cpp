//============================================================================
// Name        : Lab1UDPSocket
// Author      : Eliav Menachi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "UdpSocketTest.h"

using namespace npl;


UdpSocketTest::UdpSocketTest(){

}
/*
 * The method test the UDP connection return true if succeed and otherwise false
 */
bool UdpSocketTest::test(){
	cout << "UDP Socket test" << endl;

	UDPSocket* sSocket = new UDPSocket(3346);
	UDPSocket* cSocket = new UDPSocket();
	string message = "Test 1234567890";
	cSocket->sendTo(message, "127.0.0.1", 3346);

	char buffer[100];
	memset((void*) buffer, 0, 100);
	int rc = sSocket->read(buffer, 100);
	cout << "send msg:" << message << endl;
	cout << "recv msg:" << buffer << endl;
	if (rc != (int) message.length()) {
		perror("FAIL1: receive different message length");
		return false;
	}
	if (message != buffer) {
		perror("FAIL2: receive different message");
		return false;
	}
	message = "Test Reply 129012901290";
	sSocket->reply(message);
	memset((void*) buffer, 0, 100);
	rc = cSocket->read(buffer, 100);
	cout << "send msg:" << message << endl;
	cout << "recv msg:" << buffer << endl;
	if (rc != (int) message.length()) {
		perror("FAIL1: receive different message length");
	}
	if (message != buffer) {
		perror("FAIL2: receive different message");
	}
	sSocket->close();
	cSocket->close();
	delete sSocket;
	delete cSocket;
	return true;
}




UdpSocketTest::~UdpSocketTest() {
	// TODO Auto-generated destructor stub
}

