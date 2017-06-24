
#include <iostream>
#include "TCPMessengerServer.h"
using namespace std;

void printInstructions(){
	cout<<"-----------------------"<<endl;
	cout<<"lp - list peers"<<endl;
	cout<<"x - shutdown server"<<endl;
	cout<<"-----------------------"<<endl;
}

int main(){
	cout<<"Welcome to TCP messenger Server P1"<<endl;
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
	msngrServer.close();
	cout<<"messenger was closed"<<endl;
	return 0;
}
