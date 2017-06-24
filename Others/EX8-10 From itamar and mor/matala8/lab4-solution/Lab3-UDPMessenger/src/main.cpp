/*
 * main.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "UDPMessenger.h"
using namespace npl;

void printInstructions(){
	cout<<"To send a message type: s <ip> <message>"<<endl;
	cout<<"To reply to a message type: r <message>"<<endl;
	cout<<"To exit type: x"<<endl;
}

int main(){

	cout<<"Welcome to UDP messenger"<<endl;
	printInstructions();
	UDPMessenger* messenger = new UDPMessenger();
	while(true){
		string msg;
		string command;
		cin >> command;
		if(command == "s"){
			string ip;
			cin >> ip;
			getline(std::cin,msg);
			if(msg.size()>0 && msg[0] == ' ') msg.erase(0,1);
			messenger->sendTo(msg,ip);
		}else if(command == "r"){
			getline(std::cin,msg);
			if(msg.size()>0 && msg[0] == ' ') msg.erase(0,1);
			messenger->reply(msg);
		}else if(command == "x"){
			break;
		}else{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}
	messenger->close();
	delete messenger;
	cout<<"messenger was closed"<<endl;
	return 0;
}


#endif /* MAIN_CPP_ */
