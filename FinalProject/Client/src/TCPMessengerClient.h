#include <strings.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include "UDPHandeler.h"
#include "TCPMessengerProtocol.h"

using namespace std;

/**
 * The TCP Messenger client class
 */
class TCPMessengerClient: public MThread
{
	TCPSocket* clientSock;

	public:

		bool serverConnected;
		bool peerConnected;
		UDPHandeler* UDPmanager;
		string inSessionWith;
		string userName;
		int state;
		void run();

		TCPMessengerClient();

		/**
		 * connect to the given server ip (the port is defined in the protocol header file)
		 */
		bool connect(string ip,string user,string pass,int registration);

		void sendPeerAdrrToServer(string userName, string password);//will send the peer's address

		void TCPtoServerMessage(string msg,int protocol);

		/**
		 * return true if connected to the server
		 */
		bool isConnected();

		/**
		 * disconnect from messenger server
		 */
		void disconnect();

		/**
		 * open session with the given peer address (ip:port)
		 */
		void open(string typeOfSession,string name);

		/**
		 * close active session
		 */
		bool closeActiveSession();

		/**
		 * send the given message to the connected peer
		 */
		bool send(string msg);
		bool sendGmaeMove(string msg);
		string getGameStatus();
		void resetGameStatus();
		void TCPtoServerCommandProtocol(int protocol);
		void printMyCurrentStatus();
		void sendWinnerToServer();
		void PrintData(string data, int numOfIter);
		void PrintConnectedUsers();
		void PrintAllUsers();
		void PrintScoreBoard();

};

