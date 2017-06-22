//============================================================================
// Name        : TCPMessengerServer
// Author      : Eliav Menachi
// Version     :
// Copyright   :
// Description : TCP messenger server console
//============================================================================

#include <iostream>
#include "TCPMessengerServer.h"
#include "TCPMessengerProtocol.h"
using namespace std;

void printCommandList()
{
	cout<<"Server commands:"<<endl;
	cout<<"* List all users \t\t lu"<<endl;
	cout<<"* List all connected users \t lcu"<<endl;
	cout<<"* List all sessions \t\t ls"<<endl;
	cout<<"* List all rooms \t\t lr"<<endl;
	cout<<"* List all users in this room \t lru <room name>"<<endl;
	cout<<"* Exit \t\t\t\t x"<<endl;
}

int main()
{
	cout<<"*** Messenger Server ***"<<endl;
	cout<<"========================="<<endl;
	printCommandList();
	TCPMessengerServer server;

	bool loop = true;
	while(loop)
	{
		string msg;
		string command;
		cin >> command;

		if(command == "lcu")
		{
			server.listPeers();
		}

		//Print all rooms
		else if(command == "lr")
		{
			if(server.Rooms.size()>0)
			{
				for(unsigned int i = 0 ; i<server.Rooms.size();i++)
				cout<<i+1<<"."<<server.Rooms.at(i)->name<<endl;
			}
			else
			{
				cout<<"There are no open rooms"<<endl;
			}
		}

		//list of users in a specific room
		else if(command == "lru")
		{
			string roomname;
			cin>>roomname;
			server.printUserinRoom(roomname);
		}

		else if(command == "lu")
		{
			server.printAllUsers();
		}

		else if(command == "ls")
		{
			server.ListSessions();
		}
		else if(command == "x")
		{
			for(unsigned int i =0 ; i<server.openPeerVect.size();i++)
			{
				server.SendCommandToTCP(SERVER_DISCONNECT,server.openPeerVect.at(i));
			}
			system("sleep 1");
			loop = false;
		}

		else
		{
			cout<<"Wrong input"<<endl;
		}
	}

	server.close();
	cout<<"Server was closed"<<endl;
	return 0;
}
