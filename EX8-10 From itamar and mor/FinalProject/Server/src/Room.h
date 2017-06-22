/*
 * Room.h
 *
 *  Created on: Jun 5, 2013
 *      Author: user
 */

#ifndef ROOM_H_
#define ROOM_H_
#include <string.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Room
{
	public:
		string hostIp_Port;
		string hostName;
		vector<string> users;
		string name;

		Room(string roomName,string hostIp_Port,string hostName);
		virtual ~Room();
		void AddUserToRoom(string user);
		void RemoveUserFromRoom(string user);
		int countUsers();
		//void send

};

#endif /* ROOM_H_ */
