
#include "TCPMessengerClient.h"
#include "TCPMessengerProtocol.h"
#include "UDPSocket.h"
#include <string.h>


TCPMessengerClient::TCPMessengerClient()
{
	roomName = "none";
	userName = "none";
	state = NOT_CONNECTED;
	UDPmanager = NULL;
	clientSock = NULL;
	peerConnected = NULL;
	serverConnected = NULL;
}

bool TCPMessengerClient::connect(string ip, string user, string pass, int registration)
{
	if(state == NOT_CONNECTED)
	{
		string msg = user+" "+pass;
		clientSock = new TCPSocket(ip,PORT);
		this->start();
		serverConnected = true;

		//Login to server
		if(registration == 0)
		{
			this->TCPtoServerMessage(msg,USER_LOGIN_REQUEST);
			userName = user;
		}

		//Register = create a new user
		if(registration == 1)
		{
			this->TCPtoServerMessage(msg,CREATE_NEW_USER);
		}
		return true;
	}

	else
	{
		cout << "Connection already opened" << endl;
		return false;
	}
}

//Checks if client is connected to server
bool TCPMessengerClient::isConnected()
{
	return serverConnected;
}

//Disconnect from the server
void TCPMessengerClient::disconnect()
{
	if(state != NOT_CONNECTED)
	{
//		if(state == IN_ROOM)
//		{
//			LeaveCurrentRoom();
//		}
		if(state == IN_SESSION)
		{
			closeActiveSession();
		}
		TCPtoServerCommandProtocol(DISCONNECT);
//		system("sleep 1");
		serverConnected = false;
		UDPmanager->UDPserverConnected = false;
		clientSock->cclose();
		state = NOT_CONNECTED;
	}

	else
	{
		cout << "You are not connected to server" << endl;
	}
}

//Open a session with the given peer address (ip:port)
void TCPMessengerClient::open(string typeOfSession,string name)
{
	if(isConnected())
	{
	  if(state == AVAILABLE)
	  {
		  if(strcmp(typeOfSession.c_str(),"user") == 0)
		  {
			  TCPtoServerMessage(name,REQUEST_TO_OPEN_SESSION);
		  }
	  }
	  else
	  {
		  cout << "Session is already opened" << endl;
	  }
	}
	else
	{
		cout << "You are not connected to a server" << endl;
	}
}


void TCPMessengerClient::run()
{
	char* buffer = new char[1024];

	while(serverConnected)
	{
		int command;
		clientSock->recv((char*)&command,4);
		bzero(buffer,1024);
		command = ntohl(command);

		switch(command)
		{
			case SESSION_ESTABLISHED: //<- strtok is used once on the string with the argument
			{
				int msgLen;
				clientSock->recv((char*)&msgLen,4);
				msgLen = ntohl(msgLen);
				clientSock->recv(buffer, msgLen);
				cout<<"connected to "<<buffer<<endl;
				string peerNameToConnect = strtok(buffer, " ");
				string peerAddress = strtok(NULL, " ");
				UDPmanager->setDestmessage(peerAddress);
				inSessionWith = peerNameToConnect;
				peerConnected = true;
				state = IN_SESSION;
				break;
			}
			case SESSION_REFUSED:
			{
				cout << "Could not open session" << endl;
				break;
			}
			case REJECT_SESSION_REQUEST:
			{
				cout << "Could not open session, session was rejected" << endl;
				break;
			}
			case REQUEST_TO_OPEN_SESSION:
			{
				int msgLen;
				string answer;
				clientSock->recv((char*)&msgLen,4);
				msgLen = ntohl(msgLen);
				clientSock->recv(buffer, msgLen);
				cout<<"you have new game request from "<<buffer<<endl;
				cout<<"Enter yes to approve or no to reject: "<<endl;
				state = PENDING;
				break;
			}
			case OPEN_SESSION_WITH_PEER:
			{
				TCPtoServerCommandProtocol(state);
				break;
			}
			case LOGIN_RESPONSE_ERROR:
			{
				cout << "Login error" << endl;
				userName = "none";
				break;
			}
			case LOGIN_RESPONSE_APPROVE:
			{
				int msgLen;
				clientSock->recv((char*)&msgLen,4);
				msgLen = ntohl(msgLen);
				clientSock->recv(buffer, msgLen);
				UDPmanager = new UDPHandeler(userName,buffer);
				UDPmanager->start();
				state = AVAILABLE;
				cout << "Connected to server as " << userName << endl;
				break;
			}
			case SEND_SERVER_USERNAME:
			{
				cout << "Connected to server as " << userName << endl;
				break;
			}
			case CLOSE_SESSION_WITH_PEER:
			{
				cout << "Your session is disconnected" << endl;
				state = AVAILABLE;
				peerConnected = false;
				inSessionWith = "none";
				break;
			}
			case PRINT_DATA_FROM_SERVER:
			{
				int numOfIter;
				clientSock->recv((char*)&numOfIter,4);
				numOfIter = ntohl(numOfIter);
				int msgLen;
				clientSock->recv((char*)&msgLen,4);
				msgLen = ntohl(msgLen);
				clientSock->recv(buffer, msgLen);
				PrintData(buffer,numOfIter);
				break;
			}
			case RETURN_RANDOM_ACTIVE_USER:
			{
				int msgLen;
				clientSock->recv((char*)&msgLen,4);
				msgLen = ntohl(msgLen);
				clientSock->recv(buffer, msgLen);
				cout << "Trying to connect to random user: " << buffer << endl;
				open("user", buffer);
				break;
			}
			case NEW_USER_APPROVED:
			{
				cout << "Registration succeed"<< endl;
				break;
			}
			case NEW_USER_DENIED:
			{
				cout << "This username is already exist" << endl;
				break;
			}
			case SERVER_DISCONNECT:
			{
				cout << "Server is closed" << endl;
				if(state == IN_SESSION)
				{
					closeActiveSession();
				}
				serverConnected = false;
				UDPmanager->UDPserverConnected = false;
				clientSock->cclose();
				state = NOT_CONNECTED;
				break;
			}
		}
	}
}

void TCPMessengerClient::PrintData(string data, int numOfIter)
{
	char* tempCahrFromData = strdup(data.c_str());
	int i;
    string dataString = strtok(tempCahrFromData," ");
	for(i=0; i<numOfIter-1; i++)
	{
		cout << i+1 << "." << dataString << endl;
		dataString=strtok(NULL," ");
	}
	cout << i+1 << "." << dataString << endl;
	free(tempCahrFromData);
}


bool TCPMessengerClient::closeActiveSession()
{
	if(isConnected())
	{
		if(state == IN_SESSION)
		{
			this->TCPtoServerCommandProtocol(CLOSE_SESSION_WITH_PEER);
			state = AVAILABLE;
			peerConnected = false;
			inSessionWith = "none";
			cout << "You have been disconnected from your current session" << endl;
			return true;
		}
		else
		{
			cout << "You are not connected to any session" << endl;
		}
	}
	return false;
}

//Send the given message to the connected peer
bool TCPMessengerClient::send(string msg)
{
	if(state == IN_SESSION)
	{
		UDPmanager->sendToPeer(msg);
		return true;
	}
//	if(state == IN_ROOM)
//	{
//		UDPmanager->sendToRoom(msg);
//		return true;
//	}
	return false;
}

void TCPMessengerClient::TCPtoServerCommandProtocol(int protocol)
{
	int command = htonl(protocol);
	clientSock->send((char*)&command,4);
}

void TCPMessengerClient::TCPtoServerMessage(string msg,int protocol)
{
	if(protocol != DONT_SEND_COMMAND)
	{
	   TCPtoServerCommandProtocol(protocol);
	}
	int msglen = htonl(msg.length());
	clientSock->send((char*)&msglen,4);
	clientSock->send(msg.c_str(),(msg.length()));
}

void TCPMessengerClient::printMyCurrentStatus()
{
	if(state == AVAILABLE)
	{
		cout << "You are connected to server with user "<< userName << endl;
	}
//	else if(state == IN_ROOM)
//	{
//		cout << "You are in room "<< roomName <<endl;
//	}
	else if(state == IN_SESSION)
	{
		cout << "You are in session with " << inSessionWith << endl;
	}
	else
	{
		cout << "You are not connected to any server!" << endl;
	}
}


//Print all connected users
void TCPMessengerClient::PrintConnectedUsers()
{
	if(state == NOT_CONNECTED)
	{
		cout << "You are not connected to any server!" << endl;
	}
	else
	{
		TCPtoServerCommandProtocol(CONNECTED_USERS);
	}

}

//Print all registered users
void TCPMessengerClient::PrintAllUsers()
{
	if(state == NOT_CONNECTED)
	{
		cout << "You are not connected to any server!" << endl;
	}
	else
	{
		TCPtoServerCommandProtocol(REG_USERS);
	}
}


