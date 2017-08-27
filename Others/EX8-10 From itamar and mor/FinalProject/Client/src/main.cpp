#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <iostream>
#include <string.h>
#include "TCPMessengerClient.h"

using namespace std;

void printCommandList() {
	cout << "Commands:" << endl;
	cout
			<< "* Register new user \t\t\t register <server ip> <username> <password>"
			<< endl;
	cout
			<< "* Login existed user \t\t\t login <server ip> <username> <password>"
			<< endl;
	cout << "* Show your current state \t\t l" << endl;
	cout << "* Print users list \t\t\t lu" << endl;
	cout << "* Print connected users list \t\t lcu" << endl;
	cout << "* Print score list \t\t\t lsb" << endl;
	cout << "* Open a session with user \t\t o <username>" << endl;
	cout << "* Send message in your session \t\t s <message>" << endl;
	cout << "* Close opened session \t\t\t cs" << endl;
	cout << "* Disconnect from server \t\t d" << endl;
	cout << "* Show Menu \t\t\t\t m" << endl;
	cout << "* DEBUG - SEND Score to server \t\t sbwin" << endl;
	cout << "* Exit \t\t\t\t\t x" << endl;
}

int main() {
	bool serverActive = true;

	cout << "*** Client Messenger ***" << endl;
	cout << "========================" << endl;
	cout << "" << endl;
	printCommandList();
	TCPMessengerClient* client = new TCPMessengerClient();

	while (true) {
		string msg;
		string command;
		cin >> command;

		if (command == "login") {
			string ip;
			string user;
			string pass;
			cin >> ip;
			cin >> user;
			cin >> pass;
			client->connect(ip, user, pass, 0);
		}

		//Register to remote server
		else if (command == "register") {
			string userName;
			string password;
			string ip;
			cin >> ip;
			cin >> userName;
			cin >> password;
			client->connect(ip, userName, password, 1);
		}

		// open a session with the user
		else if (command == "o") {
			string username;
			cin >> username;
			client->open("user", username);
		}

		else if (command == "s") {
			getline(std::cin, msg);

			if (client->state != IN_SESSION) {
				cout << "You are not connected to any room or session" << endl;
			} else {
				client->send(msg);
			}
		}

		//Leave a room or a session
		else if (command == "cs") {
			if (client->state == IN_SESSION) {
				client->closeActiveSession();
			} else {
				cout << "You are not connected to any room or session" << endl;
			}
		}

		//Print all registered users
		else if (command == "lu") {
			client->PrintAllUsers();
		}

		//Print scoreboard
		else if (command == "lsb") {
			client->PrintScoreBoard();
		}

		// Only the winning client should send the server the winning user (self)
		// Winning user should send the server the results
		else if (command == "sbwin") {
			cout << "recived command sbwin"<< endl;
			client->sendWinnerToServer();
		}

		//Print all login users
		else if (command == "lcu") {
			client->PrintConnectedUsers();
		}

		//Show user status
		else if (command == "l") {
			client->printMyCurrentStatus();
		}

		//Disconnect from server
		else if (command == "d") {
			client->disconnect();
			serverActive = false;
		}

		//Exit client
		else if (command == "x") {
			client->disconnect();
			break;
		}

		//Print menu again
		else if (command == "m") {
			printCommandList();
		}
		else if (command == "yes") {
			if (client->state == PENDING){
				client->state = AVAILABLE;
				client->TCPtoServerCommandProtocol(APPROVE_SESSION_REQUEST);
			}
			else
				cout << "You don't have any requests to approve" << endl;
		}
		else if (command == "no"){
			if (client->state == PENDING){
				client->state = AVAILABLE;
				client->TCPtoServerCommandProtocol(REJECT_SESSION_REQUEST);
			}
			else
				cout << "You don't have any requests to reject" << endl;
		} else if (command == "random") {
			client->TCPtoServerCommandProtocol(RETURN_RANDOM_ACTIVE_USER);
		}
		else {
			cout << "Wrong input" << endl;
		}
	}

	if (serverActive == false) {
		client->disconnect();
	}

	delete client;
	cout << "Bye" << endl;
	return 0;

}

#endif
