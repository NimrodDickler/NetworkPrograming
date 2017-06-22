
#include <iostream>
#include "TCPMessengerServer.h"
using namespace std;

void printInstructions(){
	cout<<"To list all opened peers type: lp"<<endl;
	cout<<"To exit type: x"<<endl;
}

int main(){
	cout<<"Welcome to TCP messenger Server"<<endl;
	printInstructions();
	TCPMessengerServer msngrServer;
	bool loop = true;
	while(loop){
		string msg;
		string command;
		cin >> command;
		if(command == "lp"){
			msngrServer.listPeers();
		}else if(command == "x"){
			loop = false;
		}else{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}
	cout<<"messenger was closed"<<endl;
	msngrServer.close();
	return 0;
}
