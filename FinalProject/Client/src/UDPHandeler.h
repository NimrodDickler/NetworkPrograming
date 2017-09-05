/*
 * RecieveMsgUDP.h
 *
 *  Created on: Jun 5, 2013
 *      Author: user
 */

#ifndef UDPHANDELER_H_
#define UDPHANDELER_H_
#include "UDPSocket.h"
#include "MThread.h"
#include <string.h>
#include <vector>
#include <stdlib.h>

class UDPHandeler:public MThread {

public:
	UDPSocket* clientUDPSock;
	string myUserName;
	string destIp;
	string destPort;
	string roomName;
	string myMove;
	string winner;
	vector<string> listOfUsersInRoom;
	bool UDPserverConnected;

	void sendToPeer(string msg);
	void sendGameMoveToPeer(string move);
	void resetGameStatus();
	string winnerStatus();
	UDPHandeler(string myUserName,string myIpandPort);
	void setDestmessage(string dest);
	void sendToRoom(string msg);
	void PrintUsersInRoom();
	virtual ~UDPHandeler();
	void run();

};

#endif /* UDPHANDELER_H */
