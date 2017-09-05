/*
 * DIspatcher.h
 *
 *  Created on: May 19, 2013
 *      Author: user
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_
#include "MThread.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"


class TCPMessengerServer;


class Dispatcher:public MThread
{
	public:
		TCPMessengerServer* server;
		MultipleTCPSocketsListener* MTL;
		bool dispatcherActive;

		void run();
		Dispatcher(TCPMessengerServer* server);
		virtual ~Dispatcher();

	private:
		void printConnectedUsers(TCPSocket* user);
		void openSession(TCPSocket* user);
		void requestToOpenSession(TCPSocket* user);
		void closeSession(TCPSocket* user);
//		void createRoom(TCPSocket* user);
//		void leaveRoom(TCPSocket* user);
//		void joinRoom(TCPSocket* user);
//		void printRoomList(TCPSocket* user);
//		void printUsersInRoom(TCPSocket* user);
		void printRegisteredUsers(TCPSocket* user);
		void printScoreBoard(TCPSocket * user);
		void updateScoreBoard(TCPSocket * user);
		void returnRandomActiveUser(TCPSocket* user);
		void disconnect(TCPSocket* user);
};

#endif /* DISPATCHER_H_ */
