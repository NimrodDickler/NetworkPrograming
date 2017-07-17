/*
 * DIspatcher.cpp
 *
 *  Created on: May 19, 2013
 *      Author: user
 */

#include "Dispatcher.h"
#include "TCPMessengerServer.h"
#include "TCPMessengerProtocol.h"


Dispatcher::Dispatcher(TCPMessengerServer* mServer)
{
	server = mServer;
	dispatcherActive = true;
	MTL = NULL;
}

void Dispatcher::run()
{
	while(dispatcherActive)
	{
		string buffer;

		if(MTL != NULL)
		{
			delete MTL;
		}

		MTL = new MultipleTCPSocketsListener();
		MTL->addSockets(server->openPeerVect);
		TCPSocket* user = MTL->listenToSocket(2);
		if(user == NULL)
		{
			continue;
		}

		switch(server->RecieveCommandFromTCP(user))
		{
			case OPEN_SESSION_WITH_PEER:
			{
				openSession(user);
				break;
			}
			case REQUEST_TO_OPEN_SESSION:
			{
				requestToOpenSession(user);
				break;
			}

			//Get the room name and add the user to that room
			/*case JOIN_ROOM:
			{
				joinRoom(user);
				break;
			}*/

			case CLOSE_SESSION_WITH_PEER:
			{
				closeSession(user);
				break;
			}

			//Create room and save the owner
//			case CREATE_NEW_ROOM:
//			{
//				createRoom(user);
//				break;
//			}

			//Remove user from room
//			case LEAVE_ROOM:
//			{
//				leaveRoom(user);
//				break;
//			}

			//Print all connected users
			case CONNECTED_USERS:
			{
				printConnectedUsers(user);
				break;
			}

			case RETURN_RANDOM_ACTIVE_USER:
			{
				returnRandomActiveUser(user);
				break;
			}

//			case USERS_IN_ROOM:
//			{
//				printUsersInRoom(user);
//				break;
//			}

			//Print available rooms
//			case EXISTED_ROOMS:
//			{
//				printRoomList(user);
//				break;
//			}

			case REG_USERS:
			{
				printRegisteredUsers(user);
				break;
			}

			case DISCONNECT:
			{
				disconnect(user);
				break;
			}
		}
	}
}



void Dispatcher::printConnectedUsers(TCPSocket * user)
{
	string stringOfUsersName;
	string tempNameFromIp;
	int numberOfUsers = server->openPeerVect.size();

	for(unsigned int i=0; i<server->openPeerVect.size(); i++)
	{
		tempNameFromIp = server->ipToName(server->openPeerVect.at(i)->destIpAndPort());
		stringOfUsersName.append(tempNameFromIp);
		if(i != server->openPeerVect.size()-1)
		{
			stringOfUsersName.append(" ");
		}
	}
	if(numberOfUsers > 0)
	{
		server->SendCommandToTCP(PRINT_DATA_FROM_SERVER,user);
		server->SendCommandToTCP(numberOfUsers,user);
		server->SendMsgToTCP(stringOfUsersName,user);
	}
}

void Dispatcher::returnRandomActiveUser(TCPSocket * user)
{
	string tempNameFromIp;
	int numberOfUsers = server->openPeerVect.size();
	TCPSocket* randomUser;

	randomUser = server->openPeerVect.at(rand() % (numberOfUsers));
	while (randomUser == user){
		randomUser = server->openPeerVect.at(rand() % (numberOfUsers));
	}
	tempNameFromIp = server->ipToName(randomUser->destIpAndPort());
	cout << "tempNameFromIp: " << tempNameFromIp << endl;
	if(numberOfUsers > 1)
	{
		server->SendCommandToTCP(RETURN_RANDOM_ACTIVE_USER,user);
		server->SendMsgToTCP(tempNameFromIp,user);
	}
}

void Dispatcher::openSession(TCPSocket* user)
{
	string requested_username = server->RecieveMessageFromTCP(user);
	string requested_userIP = server->nameToIp(requested_username);

	//Checks if the requested user is connected
	if(strcmp(requested_userIP.c_str(),"Client not found") != 0)
	{
		int indexOfrequestedPeer = server->findVector(requested_userIP);

		TCPSocket* tempTCPPeerToConnect = server->openPeerVect.at(indexOfrequestedPeer);
		server->SendCommandToTCP(OPEN_SESSION_WITH_PEER,tempTCPPeerToConnect);

		switch(server->RecieveCommandFromTCP(tempTCPPeerToConnect))
		{
			case AVAILABLE:
			{
				server->SendCommandToTCP(SESSION_ESTABLISHED,user);
				server->SendMsgToTCP(requested_username+" "+requested_userIP,user);
				string MTLTCPname = server->ipToName(user->destIpAndPort());
				server->SendCommandToTCP(SESSION_ESTABLISHED,tempTCPPeerToConnect);
				server->SendMsgToTCP(MTLTCPname+" "+user->destIpAndPort(),tempTCPPeerToConnect);
				server->session1.push_back(user->destIpAndPort());
				server->session2.push_back(tempTCPPeerToConnect->destIpAndPort());
				cout << "User is available" << endl;
				break;
			}
			default:
			{
				server->SendCommandToTCP(SESSION_REFUSED,user);
				break;
			}
		}
	}
	//If not, print error message
	else
	{
		server->SendCommandToTCP(SESSION_REFUSED,user);
	}
}


void Dispatcher::requestToOpenSession(TCPSocket* user)
{
	string requested_username = server->RecieveMessageFromTCP(user);
	string requested_userIP = server->nameToIp(requested_username);
	string MTLTCPname = server->ipToName(user->destIpAndPort());

	//Checks if the requested user is connected
	if(strcmp(requested_userIP.c_str(),"Client not found") != 0)
	{
		int indexOfrequestedPeer = server->findVector(requested_userIP);

		TCPSocket* tempTCPPeerToConnect = server->openPeerVect.at(indexOfrequestedPeer);
		server->SendCommandToTCP(REQUEST_TO_OPEN_SESSION,tempTCPPeerToConnect);
		server->SendMsgToTCP(MTLTCPname+" "+user->destIpAndPort(),tempTCPPeerToConnect);

		switch(server->RecieveCommandFromTCP(tempTCPPeerToConnect))
		{
			case APPROVE_SESSION_REQUEST:
			{
				server->SendCommandToTCP(OPEN_SESSION_WITH_PEER,tempTCPPeerToConnect);

				switch(server->RecieveCommandFromTCP(tempTCPPeerToConnect))
				{
					case AVAILABLE:
					{
						server->SendCommandToTCP(SESSION_ESTABLISHED,user);
						server->SendMsgToTCP(requested_username+" "+requested_userIP,user);
						server->SendCommandToTCP(SESSION_ESTABLISHED,tempTCPPeerToConnect);
						server->SendMsgToTCP(MTLTCPname+" "+user->destIpAndPort(),tempTCPPeerToConnect);
						server->session1.push_back(user->destIpAndPort());
						server->session2.push_back(tempTCPPeerToConnect->destIpAndPort());
						cout << "User is available" << endl;
						break;
					}
					default:
					{
						server->SendCommandToTCP(SESSION_REFUSED,user);
						break;
					}
				}
				break;
			}
			default:
			{
				server->SendCommandToTCP(REJECT_SESSION_REQUEST,user);
				break;
			}
		}
	}
	//If not, print error message
	else
	{
		server->SendCommandToTCP(SESSION_REFUSED,user);
	}
}

void Dispatcher::closeSession(TCPSocket* user)
{
	unsigned int i;
	string closeRequestPeer = user->destIpAndPort();
	int indexInOpenVect;
	for(i=0; i<server->session1.size();i++)
	{
		if(server->session1.at(i) == closeRequestPeer)
		{
			indexInOpenVect = server->findVector(server->session2.at(i));
			break;
		}
		if(server->session2.at(i) == closeRequestPeer)
		{
			indexInOpenVect = server->findVector(server->session1.at(i));
			break;
		}
	}
	server->session1.erase(server->session1.begin()+i);
	server->session2.erase(server->session2.begin()+i);
	server->SendCommandToTCP(CLOSE_SESSION_WITH_PEER,server->openPeerVect.at(indexInOpenVect));
}
//
//void Dispatcher::printRoomList(TCPSocket* user)
//{
//	int numOfRoom = server->Rooms.size();
//	string stringOfRooms;
//	for(unsigned int i=0;i<server->Rooms.size();i++)
//	{
//		stringOfRooms.append(server->Rooms.at(i)->name);
//		if(i!=server->Rooms.size()-1)
//		{
//			stringOfRooms.append(" ");
//		}
//	}
//	if(numOfRoom > 0)
//	{
//		server->SendCommandToTCP(PRINT_DATA_FROM_SERVER,user);
//		server->SendCommandToTCP(numOfRoom,user);
//		server->SendMsgToTCP(stringOfRooms,user);
//	}
//	else
//	{
//		//36 means NO_ROOMS (define not working)
//		server->SendCommandToTCP(NO_ROOMS, user);
//	}
//}
//
//void Dispatcher::printUsersInRoom(TCPSocket* user)
//{
//	string roomNameFromClient = server->RecieveMessageFromTCP(user);
//	int roomIndex=server->findInRooms(roomNameFromClient);
//
//	if(roomIndex != -1)
//	{
//		string stringOfUsersName;
//		string tempNameFromIp;
//		for(unsigned int i=0;i< server->Rooms.at(roomIndex)->users.size();i++)
//		{
//			tempNameFromIp=server->ipToName(server->Rooms.at(roomIndex)->users.at(i));
//			stringOfUsersName.append(tempNameFromIp);
//			if(i != server->Rooms.at(roomIndex)->users.size()-1)
//			stringOfUsersName.append(" ");
//		}
//
//		int numOfUsersInRoom = server->Rooms.at(roomIndex)->users.size();
//
//		server->SendCommandToTCP(PRINT_DATA_FROM_SERVER,user);
//		server->SendCommandToTCP(numOfUsersInRoom,user);
//		server->SendMsgToTCP(stringOfUsersName,user);
//	}
//	else
//	{
//		server->SendCommandToTCP(NO_SUCH_ROOM,user);
//	}
//}

void Dispatcher::printRegisteredUsers(TCPSocket* user)
{
	vector<string> tempVect = server->GetUserNamesFromData();
	int numOfUsers = tempVect.size();
	string users;
	for(int i = 0; i <numOfUsers;i++)
	{
		users.append(tempVect.at(i));
		if(i != numOfUsers-1)
		users.append(" ");
	}
	server->SendCommandToTCP(PRINT_DATA_FROM_SERVER,user);
	server->SendCommandToTCP(numOfUsers,user);
	server->SendMsgToTCP(users,user);
}

void Dispatcher::disconnect(TCPSocket* user)
{
	int indexUser = server->findVector(user->destIpAndPort());
	server->openPeerVect.erase(server->openPeerVect.begin()+indexUser);
}

Dispatcher::~Dispatcher()
{

}
