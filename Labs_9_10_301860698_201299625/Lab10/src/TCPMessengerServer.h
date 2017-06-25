
#include <strings.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"
#include "Dispatcher.h"

using namespace std;

class TCPMessengerServer : public MThread
{
private:
	bool isRunning;
	TCPSocket * tcpSocket;
	Dispatcher * dispatcher;

public:
	TCPMessengerServer();

	void run();

	void listPeers();

	void close();
};

