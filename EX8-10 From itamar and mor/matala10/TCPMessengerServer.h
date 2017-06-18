
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
	/**
	 * Construct a TCP server socket
	 */
	TCPMessengerServer();

	/**
	 * the messenger server main loop- this loop waits for incoming clients connection,
	 * once a connection is established the new connection is added to the openedPeers
	 * on which the dispatcher handle further communication
	 */
	void run();

	/**
	 * print out the list of connected clients (for debug)
	 */
	void listPeers();

	/**
	 * close the server
	 */
	void close();
};

