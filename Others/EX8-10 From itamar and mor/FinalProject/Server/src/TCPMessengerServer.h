//============================================================================
// Name        : TCP Messenger Server
// Author      : Eliav Menachi
// Version     :
// Copyright   :
// Description : TCP Messenger application
//============================================================================
#include <strings.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"
#include "Dispatcher.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hash_map>
#include <string>
#include <unordered_map>
#include <iostream>
#include <functional>



using namespace std;

class TCPMessengerServer:public MThread{

public:
	int posInVec;
	Dispatcher* dispatcher;
	TCPSocket* serverSock;
	bool isServerOn;
	typedef vector<TCPSocket*> tOpenPeerVect;
	tOpenPeerVect  openPeerVect;
	vector<string> ipTOclientName;
	vector<string> session1;
	vector<string> session2;


	TCPMessengerServer();
	void run();
	void listPeers();
	void PrintOpenPeerVector();
	int Register(string userNamePlusPassword);
	int RegisterWithHash(string userNamePlusPassword);
	int Login(string userName, string password);
	int RecieveCommandFromTCP(TCPSocket * tmpTCP);
	char * RecieveMessageFromTCP(TCPSocket * tmpTCP);
	void SendCommandToTCP(int protocol,TCPSocket * tmpTCP);
	void SendMsgToTCP(string msg, TCPSocket* tmpTCP);
	void insertToOpenVector(TCPSocket* temp_soc);
	int findVector(string address);
	void ClientListConnedtedUsers(TCPSocket * tmpTCP);
	string nameToIp(string name);
	string ipToName(string ip);
	void ListSessions();
//	int findInRooms(string roomName);
//	void printUserinRoom(string name);
//	string UsersInRoomToString(string roomName);
//	void SendMsgToAllUsersInRoom(int msgType,string roomName, string userName);
	vector<string> GetUserNamesFromData();
	vector<string> GetScoreBoardFromData();
	void writeToScoreBoard(string winner);
	void printAllUsers();
	void close();


	friend class Dispatcher;
};

