#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "TCPMessengerClient.h"
#include "TCPMessengerProtocol.h"
#include<iostream>
#include<string.h>
using namespace std;
using namespace npl;

void printInstructions() {
	cout << "To open connect to server type: c <server ip>" << endl;
	cout << "To open session type with peer: o <peer ip>" << endl;
	cout << "Opening session will close any previously active sessions" << endl;
	cout << "After the session is opened, to send message type: s <message>"
			<< endl;
	cout << "To close opened session type: cs" << endl;
	cout << "To disconnect from server type: d" << endl;
	cout << "To exit type: x" << endl;
}

int main() {

	cout << "Welcome to TCP Client messenger" << endl;
	TCPMessengerClient* client = new TCPMessengerClient();
	printInstructions();
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
			cout << ipAndPort << endl;
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
