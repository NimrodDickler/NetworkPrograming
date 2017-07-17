/*
 * TCPMessengerProtocol.h
 *
 *  Created on: Feb 13, 2013
 *      Author: efi
 */

#ifndef TCPMESSENGERPROTOCOL_H_
#define TCPMESSENGERPROTOCOL_H_

/**
 * TCP Messenger protocol:
 * all messages are of the format [Command 4 byte int]
 * and optionally data follows in the format [Data length 4 byte int][ Data ]
 */

#define PORT 						5050
#define DONT_SEND_COMMAND           0
#define CLOSE_SESSION_WITH_PEER 	1
#define OPEN_SESSION_WITH_PEER 		2
#define REQUEST_TO_OPEN_SESSION		3
#define EXIT				        4
#define SEND_MSG_TO_PEER			5
#define SESSION_REFUSED				6
#define SESSION_ESTABLISHED			7
#define USER_LOGIN_REQUEST      	8
#define LOGIN_RESPONSE_ERROR        9
#define LOGIN_RESPONSE_APPROVE      10
#define SEND_SERVER_USERNAME        11
#define APPROVE_SESSION_REQUEST		12
#define REJECT_SESSION_REQUEST		13
#define PENDING						14
#define RETURN_RANDOM_ACTIVE_USER	15
#define PRINT_DATA_FROM_SERVER		22
#define CREATE_NEW_USER  			23
#define NEW_USER_APPROVED			24
#define NEW_USER_DENIED				25
#define DISCONNECT                  26
#define SERVER_DISCONNECT			27
#define NOT_CONNECTED               28
#define AVAILABLE                   29
#define IN_SESSION                  30
#define REG_USERS 					32
#define CONNECTED_USERS				33


#define SESSION_REFUSED_MSG "Connection to peer refused, peer might be busy or disconnected, try again later"



#endif /* TCPMESSENGERPROTOCOL_H_ */
