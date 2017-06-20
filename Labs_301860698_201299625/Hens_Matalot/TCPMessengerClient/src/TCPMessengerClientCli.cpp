#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "TCPMessengerClient.h"
#include "TCPMessengerProtocol.h"
#include<iostream>
#include<string.h>
using namespace std;
using namespace npl;

void printInstructions() {
	cout << "To send a message type: s <ip> <message>" << endl;
	cout << "To reply to a message type: r <message>" << endl;
	cout << "To exit type: x" << endl;
}

int main() {

	cout << "Welcome to TCP Client messenger" << endl;
	TCPMessengerClient* client = new TCPMessengerClient();
	//printInstructions();
	while (true) {
		string msg;
		msg.clear();
		string command;
		command.clear();
		cin >> command;

		if (command == "c") {
			string ip;
			cin >> ip;
			getline(std::cin, msg);
			if (msg.size() > 0 && msg[0] == ' ')
				msg.erase(0, 1);
			client->connect(ip);
		} else if (command == "o") {
			string ipAndPort;
			cin >> ipAndPort;
			client->openSession(ipAndPort);
		} else if (command == "s") {
			getline(std::cin, msg);
			if (msg.size() > 0 && msg[0] == ' ')
				client->send(msg);
		} else if (command == "cs") {
				client->closeSession();
		} else if (command == "d") {
				client->disconnect();
		} else if (command == "x") {
			break;
		} else {
			cout << "wrong input" << endl;
			printInstructions();
		}
	}
	//client->close();
	//delete client;
	cout << "messenger was closed" << endl;
	return 0;
}

#endif /* MAIN_CPP_ */
