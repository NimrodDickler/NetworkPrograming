
#ifndef DISPATCHER_H_
#define DISPATCHER_H_
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"
#include "MThread.h"
#include <iostream>
#include <map>
#define SIZE 1024


class Dispatcher : public MThread
{
private:
	map <string, TCPSocket *> * peersMap;
public:
	MultipleTCPSocketsListener * peersMgr;
	Dispatcher();
	bool addPeer(TCPSocket * peer);
	bool removePeer(TCPSocket * peer);
	void listenToMessages();
	void startSession(TCPSocket * sessionPeer);
	void openConnection(vector<TCPSocket*> Peers,TCPSocket * exitSocket=NULL);
	virtual void run();
	virtual ~Dispatcher();
};

#endif
