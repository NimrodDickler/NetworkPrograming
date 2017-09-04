/*
 * RecieveMsgUDP.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: user
 */

#include "UDPHandeler.h"

void UDPHandeler::sendToRoom(string msg) {
	for (unsigned int i = 0; i < this->listOfUsersInRoom.size(); i++) {
		string tempdest = listOfUsersInRoom.at(i);
		setDestmessage(tempdest);
		sendToPeer(msg);
	}
}

UDPHandeler::UDPHandeler(string username, string IPandPort) {
	myUserName = username;
	char* port = strdup(IPandPort.c_str());
	string tempPort = strtok(port, ":");
	tempPort = strtok(NULL, ":");
	myMove = "";
	clientUDPSock = new UDPSocket(atoi(tempPort.c_str()));
	UDPserverConnected = true;
}

void UDPHandeler::setDestmessage(string dest) {
	char* port = strdup(dest.c_str());
	destIp = strtok(port, ":");
	destPort = strtok(NULL, ":");
}

void UDPHandeler::sendToPeer(string msg) {
	string finalmsg = ">[" + myUserName + "]" + " " + msg;
	clientUDPSock->sendTo(finalmsg, destIp, atoi(destPort.c_str()));
}

void UDPHandeler::sendGameMoveToPeer(string msg) {
	if (myMove != "") {
		cout
				<< "ERROR: you cannot send move if the other player didnt reply yet"
				<< endl;
	} else {
		if (msg == "winner" || msg == "loser" || msg == "draw") {
			clientUDPSock->sendTo(msg, destIp, atoi(destPort.c_str()));
		} else {
			if (msg != "game_move") {
				winner == "pending";
				myMove = msg;
				clientUDPSock->sendTo(msg, destIp, atoi(destPort.c_str()));
			} else {
				clientUDPSock->sendTo(msg, destIp, atoi(destPort.c_str()));
			}
		}

	}

}

string UDPHandeler::winnerStatus() {
	if (winner == "yes" || winner == "no" || winner == "draw") {
		return winner;
	} else {
		return "pending";
	}
}

void UDPHandeler::resetGameStatus() {
	winner = "";
}

void UDPHandeler::run() {
	char buffer[100];
	string msg;
	while (UDPserverConnected) {
		//Print user message
		clientUDPSock->recv(buffer, sizeof(buffer));
		msg = buffer;
		if (msg != "game_move") {
			cout << buffer << endl;
			bzero((char *) &buffer, sizeof(buffer)); /* They say you must do this    */
		} else {
			bzero((char *) &buffer, sizeof(buffer));
			clientUDPSock->recv(buffer, sizeof(buffer));
			msg = buffer;
			if (msg == "winner") {
				myMove = "";
				winner = "yes";
			} else if (msg == "loser") {
				myMove = "";
				winner = "no";
			} else if (msg == "draw") {
				myMove = "";
				winner = "draw";
			} else if (myMove != "") {
				if (myMove == "1" && msg == "3") {
					winner = "yes";
				} else if (myMove == "2" && msg == "1") {
					winner = "yes";
				} else if (myMove == "3" && msg == "2") {
					winner = "yes";
				} else if (myMove == "1" && msg == "2") {
					winner = "no";
				} else if (myMove == "3" && msg == "1") {
					winner = "no";
				} else if (myMove == "2" && msg == "3") {
					winner = "no";
				} else if (myMove == "1" && msg == "1") {
					winner = "draw";
				} else if (myMove == "2" && msg == "2") {
					winner = "draw";
				} else if (myMove == "2" && msg == "2") {
					winner = "draw";
				}

				if (winner == "draw") {
					myMove = "";
					sendGameMoveToPeer("game_move");
					sendGameMoveToPeer("draw");
				} else if (winner == "no") {
					myMove = "";
					sendGameMoveToPeer("game_move");
					sendGameMoveToPeer("winner");
				} else {
					myMove = "";
					sendGameMoveToPeer("game_move");
					sendGameMoveToPeer("loser");

				}
				bzero((char *) &buffer, sizeof(buffer));
			}

		}
	}
	clientUDPSock->cclose();
}

UDPHandeler::~UDPHandeler() {

}
