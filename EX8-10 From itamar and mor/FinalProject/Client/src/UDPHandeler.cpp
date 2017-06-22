/*
 * RecieveMsgUDP.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: user
 */

#include "UDPHandeler.h"


void UDPHandeler::sendToRoom(string msg)
{
	for(unsigned int i=0;i<this->listOfUsersInRoom.size();i++)
	{
		string tempdest = listOfUsersInRoom.at(i);
		setDestmessage(tempdest);
		sendToPeer(msg);
	}
}

UDPHandeler::UDPHandeler(string username,string IPandPort)
{
	myUserName = username;
	char* port = strdup(IPandPort.c_str());
	string tempPort = strtok(port,":");
	tempPort = strtok(NULL,":");
	clientUDPSock = new UDPSocket(atoi(tempPort.c_str()));
	UDPserverConnected=true;
}

void UDPHandeler::setDestmessage(string dest)
{
	char* port = strdup(dest.c_str());
	destIp = strtok(port,":");
	destPort = strtok(NULL,":");
}

void UDPHandeler::sendToPeer(string msg)
{
	 string finalmsg = ">["+myUserName+"]"+" " + msg;
	 clientUDPSock->sendTo(finalmsg,destIp,atoi(destPort.c_str()));
}

void UDPHandeler::run()
{
	char buffer [100];

	while(UDPserverConnected)
	{
		//Print user message
		clientUDPSock->recv(buffer,sizeof(buffer));
		cout << buffer << endl;
		bzero((char *) &buffer, sizeof(buffer));  /* They say you must do this    */
	}
	clientUDPSock->cclose();
}

UDPHandeler::~UDPHandeler()
{

}
