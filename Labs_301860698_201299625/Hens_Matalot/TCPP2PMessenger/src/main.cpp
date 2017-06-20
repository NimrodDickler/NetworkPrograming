//============================================================================
// Name        : TCPP2PMessenger.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPP2PMessenger.h"
using namespace std;
using namespace npl;

void printInstructions() {
	cout << "To send a message type: s <ip> <message>" << endl;
	cout << "To reply to a message type: r <message>" << endl;
	cout << "To exit type: x" << endl;
}

int main(int argc, char** argv) {

	cout << "Welcome to UDP messenger" << endl;
	printInstructions();
	if (argc == 2) {
		cout << "port is:" << argv[1] << endl;
	} else {
		cout << "please provide port number" << endl;
	}
	int port = 9999;

	TCPP2PMessenger* messenger = new TCPP2PMessenger(port);

	while (true) {
		string msg;
		string command;
		cin >> command;
		if (command == "o") {
			string ip;
			cin >> ip;
			int sport;
			cin >> sport;
			messenger->open(ip, sport);
			cin >> command;
		}
		if (command == "s") {
			getline(std::cin, msg);
			messenger->send(msg);
		} else if (command == "r") {
			getline(std::cin, msg);
			messenger->reply(msg);
		} else if (command == "x") {
			break;
		} else {
			cout << "wrong input" << endl;
			printInstructions();
		}
	}
	messenger->close();
	delete messenger;
	cout << "messenger was closed" << endl;
	return 0;
}

