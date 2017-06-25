
#ifndef BROKER_H_
#define BROKER_H_
#include <iostream>
#include "Dispatcher.h"

class Broker : public MThread
{
private:
	MultipleTCPSocketsListener socketListener;
	Dispatcher * dispatcher;

public:
	Broker(Dispatcher * dis, TCPSocket * peerOne, TCPSocket * peerTwo);
	void sendMessage(TCPSocket * sender);
	virtual void run();
	void close(bool closeConn, TCPSocket * closeSocket);
	virtual ~Broker();
};

#endif /* BROKER_H_ */
