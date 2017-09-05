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
