/*
 * Room.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: user
 */

#include "Room.h"

Room::Room(string roomName,string hostIpPort,string roomHostName)
{
	name = roomName;
	hostName = roomHostName;
	hostIp_Port = hostIpPort;
	AddUserToRoom(this->hostIp_Port);
	cout<<"The Room [" << roomName << "] Has been Created"<<endl;
}


void Room::AddUserToRoom(string user)
{
	users.push_back(user);
}

void Room::RemoveUserFromRoom(string user)
{
	for(unsigned int i = 0 ; i<users.size();i++)
	{
		if(users.at(i)==user)
		{
			users.erase(users.begin()+i);
		}
	}
}

int Room::countUsers()
{
	return users.size();
}

Room::~Room()
{

}

