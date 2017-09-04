
#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <iostream>
#include <string.h>
#include "TCPMessengerClient.h"

using namespace std;

void printCommandList()
{
	cout<<"Management commands:"<<endl;
	cout<<"* Register new user \t\t\t register <server ip> <username> <password>"<<endl;
	cout<<"* Login existed user \t\t\t login <server ip> <username> <password>"<<endl;
	cout<<"* Show your current state \t\t l"<<endl;
	cout<<"* Disconnect from server \t\t d"<<endl;
	cout<<"* Show Menu \t\t\t\t m"<<endl;
	cout<<"* Exit \t\t\t\t\t x"<<endl;
	cout<<""<<endl;
	cout<<"Chat commands:" << endl;
	cout<<"* Print users list \t\t\t lu"<<endl;
	cout<<"* Print connected users list \t\t lcu"<<endl;
	cout<<"* Print rooms list \t\t\t lr"<<endl;
	cout<<"* Print all users in the room \t\t lru <room name>"<<endl;
	cout<<"* Open a session with user \t\t o <username>"<<endl;
	cout<<"* Create a new room \t\t\t cr <room name>"<<endl;
	cout<<"* Enter a chat room \t\t\t or <room name>"<<endl;
	cout<<"* Send message in your session \t\t s <message>"<<endl;
	cout<<"* Close opened session/exit room \t cs"<<endl;
}

int main()
{
	bool serverActive = true;

	cout<<"*** Client Messenger ***"<<endl;
	cout<<"========================"<<endl;
//	cout<<""<<en/dl;
	printCommandList();
	TCPMessengerClient* client = new TCPMessengerClient();

	while(true)
	{
		string msg;
		string command;
		cin >> command;

		//Connect to server (127.0.0.1 for localhost)
		if(command == "login")
		{
			string ip;
			string user;
			string pass;
			cin >> ip;
			cin >> user;
			cin >> pass;
			client->connect(ip, user, pass,0);
		}

		//Register to remote server
		else if(command == "register")
		{
			string userName;
			string password;
			string ip;
			cin>>ip;
			cin>>userName;
			cin>>password;
			client->connect(ip,userName,password,1);
		}

		// open a session with the user
		else if(command == "o")
		{
			string username;
			cin >> username;
			client->open("user",username);
		}

		//enter a chat room
		else if(command == "or")
		{
			string roomName;
			cin >> roomName;
			client->open("room",roomName);
		}

		//Send message in a room or session
		else if(command == "s")
		{
			getline(std::cin,msg);

			if ((client->state != IN_SESSION) && (client->state != IN_ROOM))
			{
				cout << "You are not connected to any room or session" << endl;
			}
			else
			{
				client->send(msg);
			}
		}

		//Leave a room or a session
		else if(command == "cs")
		{
			if(client->state == IN_SESSION)
			{
				client->closeActiveSession();
			}
			else if(client->state == IN_ROOM)
			{
				client->LeaveCurrentRoom();
			}
			else
			{
				cout<<"You are not connected to any room or session"<<endl;
			}
		}

		//Create a room
		else if(command == "cr")
		{
			string inputRoomName;
			cin>>inputRoomName;

			if (client->state == IN_SESSION || client->state == IN_ROOM)
			{
				cout << "Please close all sessions or rooms before creating a new one" << endl;
			}
			else if(client->state == NOT_CONNECTED)
			{
				cout << "You are not connected to any server" << endl;
			}
			else
			{
				client->CreateNewRoom(inputRoomName);
			}
		}

		//Print all users in a room
		else if(command == "lru")
		{
			string roomName;
			cin>>roomName;
			client->PrintAllUsersInRoomToServer(roomName);
		}

		//Print all registered users
		else if(command == "lu")
		{
			client->PrintAllUsers();
		}

		//Print all available rooms
		else if(command == "lr")
		{
			client->PrintAllRooms();
		}

		//Print all login users
		else if(command == "lcu")
		{
			client->PrintConnectedUsers();
		}

		//Show user status
		else if(command == "l")
		{
			client->printMyCurrentStatus();
		}

		//Disconnect from server
		else if(command == "d")
		{
			client->disconnect();
			serverActive=false;
		}

		//Exit client
		else if(command == "x")
		{
			client->disconnect();
			break;
		}

		//Print menu again
		else if(command == "m")
		{
			printCommandList();
		}

		else
		{
			cout << "Wrong input" << endl;
		}
	}

	if(serverActive == false)
	{
		client->disconnect();
	}

	delete client;
	cout << "Bye Bye :)" << endl;
	return 0;

}


#endif
