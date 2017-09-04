
#include "TCPMessengerServer.h"
#include "TCPMessengerProtocol.h"


TCPMessengerServer::TCPMessengerServer()
{
	//Open the server socket
	posInVec=0;
	serverSock = new TCPSocket(PORT);
	dispatcher = new Dispatcher(this);
	isServerOn = true;
	start();
}

void TCPMessengerServer::run()
{
	//Start the dispatcher
    dispatcher->start();

	while(true)
	{
		//Wait for incoming clients
		TCPSocket* tmpTCP=serverSock->listenAndAccept();
		int command = RecieveCommandFromTCP(tmpTCP);

		if(command == USER_LOGIN_REQUEST)
		{
			int msgLen;
			char* buffer = new char[1024];
			bzero(buffer,1024);
			//get size
			tmpTCP->recv((char *)&msgLen,4);
			//get message
			msgLen = ntohl(msgLen);
			tmpTCP->recv(buffer,msgLen);

			/*PRASE THE MSG TO USER AND PASS*/
			string userName = strtok(buffer," ");
			string password = strtok(NULL," ");

			int tempAuthentication = this->Login(userName,password);

			/*CHECK FOR VALID LOGIN INPUT*/
			if(tempAuthentication==0) //<-- 0 means good auth.
			{
				bool isAlreadyConnected=false;
				string tempName;
				for(int i = 0 ; i< (int)this->openPeerVect.size();i++)
				{
					tempName = this->ipToName(this->openPeerVect.at(i)->destIpAndPort());
					if(userName==tempName)
					{
						isAlreadyConnected=true;
						break;
					}

				}

				if(!isAlreadyConnected)
				{
					cout<< "User: " << userName << " Is Connected to server" << endl;

					/*INSERT TO OPEN VECTOR*/
					insertToOpenVector(tmpTCP);
					string tempIptoName=userName+" "+tmpTCP->destIpAndPort();
					ipTOclientName.push_back(tempIptoName);
					SendCommandToTCP(LOGIN_RESPONSE_APPROVE,tmpTCP);
					SendMsgToTCP(tmpTCP->destIpAndPort(),tmpTCP); //define the udp handler settings
				}
				else
				{
					SendCommandToTCP(LOGIN_RESPONSE_ERROR,tmpTCP);
				}
			}
			else if(tempAuthentication == 1)
			{
				cout << "The user name: " << userName << " does not exist"<<endl;
				SendCommandToTCP(LOGIN_RESPONSE_ERROR,tmpTCP);
			}
			else
			{
				cout << "The password: " << password << "is not correct for the user: "<<userName<<endl;
				SendCommandToTCP(LOGIN_RESPONSE_ERROR,tmpTCP);
			}

		}
		if(command == CREATE_NEW_USER)
		{
			string newUser = this->RecieveMessageFromTCP(tmpTCP);
			int registrationStatus = this->Register(newUser);
			if(registrationStatus==1)
			{
				this->SendCommandToTCP(NEW_USER_APPROVED,tmpTCP);
				cout << newUser << " has been Registerd" << endl;

			}
			else
			{
				SendCommandToTCP(NEW_USER_DENIED,tmpTCP);
			}
		}
	}

}

int TCPMessengerServer::Login(string userName, string password)
{
	ifstream uin;
	ifstream pin;
	uin.open("users.txt");
	pin.open("passwords.txt");
	string userNameBuffer[256];
	string passwordBuffer[256];
	int location;
	int numOfUsers=0;
	int numOfPasswords=0;

	size_t password_hash = std::hash<std::string>()(password);
	string srt_password_hash = std::to_string(password_hash);

	if (uin.is_open())
	{
		while (!uin.eof())
		{
			uin >> userNameBuffer[numOfUsers];
			numOfUsers++;
		}
	}

	if (pin.is_open())
	{
		while (!pin.eof())
		{
			pin >> passwordBuffer[numOfPasswords];
			numOfPasswords++;
		}
	}

	for(location=0;location<numOfUsers;location++)
	{
		if (strcmp(userName.c_str(), userNameBuffer[location].c_str()) ==0)
		{
			break;
		}
	}

	//Invalid username
	if(location==numOfUsers)
	{
		uin.close();
		pin.close();
		return 1;
	}

	if (strcmp(srt_password_hash.c_str(), passwordBuffer[location].c_str()) ==0)
	{
		//Valid password
		uin.close();
		pin.close();
		return 0;
	}
	/*if (password_hash == passwordBuffer[location])
		{
			//Valid password
			uin.close();
			pin.close();
			return 0;
		}*/
	else
	{
		//Invalid password
		uin.close();
		pin.close();
		return 2;
	}
}

void TCPMessengerServer::PrintOpenPeerVector()
{
	for(unsigned int i=0;i< openPeerVect.size();i++)
	{
		cout<<"PrintOpenPeerVector peer : "<<i<<" "<<openPeerVect.at(i)->destIpAndPort()<<endl;
	}
}

void TCPMessengerServer::listPeers()
{
	if(openPeerVect.size()==0)
	{
		cout<<"no peers connected"<<endl;
	}
	else
	{
		if(openPeerVect.size()!=0)
		{
			for(unsigned int i = 0;i<openPeerVect.size();i++)
			{
				if(openPeerVect.at(i)!=NULL)
				{
					string tmp = openPeerVect.at(i)->destIpAndPort();
					cout << "Connected: " << tmp << endl;
				}
			}
		}
	}
}

void TCPMessengerServer::printAllUsers()
{
	vector<string> tempVect = this->GetUserNamesFromData();
	int numOfUsers = tempVect.size();
	for(int i=0 ; i< numOfUsers ; i++)
	{
		cout << i+1 << ". " << tempVect.at(i) << endl;
	}
}

void TCPMessengerServer::insertToOpenVector(TCPSocket* temp_soc)
{
	string key = temp_soc->destIpAndPort();
	openPeerVect.push_back(temp_soc);
}

void TCPMessengerServer::SendCommandToTCP(int protocol,TCPSocket * tmpTCP)
{
	protocol = htonl(protocol);
	tmpTCP->send((char*)&protocol,4);
}

int TCPMessengerServer::findVector(string address)
{
	unsigned int i;
	bool found=false;
	for(i=0;i<openPeerVect.size();i++)
	{
		string tmp = openPeerVect.at(i)->destIpAndPort();

		if(tmp==address)
		{
			found=true;
			break;
		}
	}

	if(found)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

int TCPMessengerServer::RecieveCommandFromTCP(TCPSocket * tmpTCP)
{
	int command;
	tmpTCP->recv((char*)&command,4);
	command=htonl(command);
	return command;
}

char * TCPMessengerServer::RecieveMessageFromTCP(TCPSocket * tmpTCP)
{
	int msgLen;
	char* buffer = new char[1024];
	bzero(buffer,1024);
	tmpTCP->recv((char *)&msgLen,4);
	msgLen = ntohl(msgLen);
	tmpTCP->recv(buffer,msgLen);

	return buffer;
}

string TCPMessengerServer::nameToIp(string userName)
{
	for(unsigned int i=0; i<ipTOclientName.size();i++)
	{
		char* tempCharStar = strdup(ipTOclientName[i].c_str());
		string tmpUser = strtok(tempCharStar," ");
		string tmpIp = strtok(NULL, " ");
		free(tempCharStar);
		if(strcmp(tmpUser.c_str(),userName.c_str())==0)
		{
			return tmpIp;
		}
	}
	return "Client not found";
}

void  TCPMessengerServer::ListSessions()
{
	for(unsigned int i = 0;i<this->session1.size();i++)
	{
		cout<<this->ipToName(session1.at(i))<<" with "<<this->ipToName(session2.at(i))<<endl;
	}
}
void TCPMessengerServer::SendMsgToTCP(string msg, TCPSocket* tmpTCP)
{
	int msglen=htonl(msg.length());
	tmpTCP->send((char*)&msglen,4);
	tmpTCP->send(msg.c_str(),msg.length());
}

string TCPMessengerServer::ipToName(string ip)
{
	for(unsigned int i=0; i<ipTOclientName.size();i++)
	{
		char* tempCharStar = strdup(ipTOclientName[i].c_str());

		string tmpUser = strtok(tempCharStar," ");
		string tmpIp = strtok(NULL, " ");

		free(tempCharStar);
		if(strcmp(tmpIp.c_str(),ip.c_str())==0)
		{
			return tmpUser;
		}
	}
	return NULL;
}

void TCPMessengerServer::close()
{
	serverSock->cclose();
	openPeerVect.clear();
	dispatcher->dispatcherActive = false;
	isServerOn = false;
	delete dispatcher->MTL;
}

int TCPMessengerServer::Register(string userNamePlusPassword)
{
	char* tempUserAndPass = strdup(userNamePlusPassword.c_str());
	string username = strtok(tempUserAndPass," ");
	string password = strtok(NULL, " ");
	size_t password_hash = std::hash<std::string>()(password);

	cout << username << endl;
	cout << password << endl;
	cout << password_hash <<endl;

	ifstream pin;

	pin.open("users.txt");
	string userNameBuffer[256];
	int location;
	int numOfUsers=0;

	if (pin.is_open())
	{
		while (!pin.eof())
		{
			pin >> userNameBuffer[numOfUsers];
			numOfUsers++;
		 }
	}

	for(location=0; location<numOfUsers; location++)
	{
		if (strcmp(username.c_str(), userNameBuffer[location].c_str()) ==0)
		{
			pin.close();
			return 0;
		}
	}
	pin.close();

	ofstream pin2;
	pin2.open("users.txt",ofstream::app);

	pin2<<username<<endl;
	pin2.close();
	pin2.open("passwords.txt",ofstream::app);
	//pin2<<password<<endl;
	pin2<<password_hash<<endl;


	pin2.close();
	free(tempUserAndPass);
	return 1;
}


int TCPMessengerServer::RegisterWithHash(string userNamePlusPassword)
{
	char* tempUserAndPass = strdup(userNamePlusPassword.c_str());
	string username = strtok(tempUserAndPass," ");
	string password = strtok(NULL, " ");
	ifstream pin;

	pin.open("users.txt");
	string userNameBuffer[256];
	int location;
	int numOfUsers=0;

	if (pin.is_open())
	{
		while (!pin.eof())
		{
			pin >> userNameBuffer[numOfUsers];
			numOfUsers++;
		 }
	}

	for(location=0; location<numOfUsers; location++)
	{
		if (strcmp(username.c_str(), userNameBuffer[location].c_str()) ==0)
		{
			pin.close();
			return 0;
		}
	}
	pin.close();

	ofstream pin2;
	pin2.open("users.txt",ofstream::app);

	pin2<<username<<endl;
	pin2.close();
	pin2.open("passwords.txt",ofstream::app);
	pin2<<password<<endl;


	pin2.close();
	free(tempUserAndPass);
	return 1;
}

vector<string> TCPMessengerServer::GetUserNamesFromData()
{
	ifstream uin;
	uin.open("users.txt");
	vector<string> userNameBuffer;
	string temp;

	if (uin.is_open())
	{
		while (uin >> temp)
		{
			userNameBuffer.push_back(temp);
		}
	}

	uin.close();
	return userNameBuffer;
}
void TCPMessengerServer::writeToScoreBoard(string winner)
{
	ofstream sbin;
	sbin.open("scoreboard.txt",ofstream::app);
	sbin<<endl<<winner<<endl;
	sbin.close();
}

vector<string> TCPMessengerServer::GetScoreBoardFromData()
{
	ifstream uin;
	uin.open("users.txt");
	map<string,int> scoreBoard;
	multimap<int, string,greater<int>> flipedScoreBoard;
	vector<string> scoreBuffer;
	string temp, user, score;
	string sep = ":";

	if (uin.is_open())
	{
		while (uin >> temp)
		{
			scoreBoard[temp] = 0;
		}
	}

	uin.close();

	ifstream sin;
	sin.open("scoreboard.txt");

	string tempScore;

	if (sin.is_open())
	{
		while (sin >> tempScore)
		{
			++scoreBoard[tempScore];
		}
	}

	sin.close();


	map<string,int>::iterator i = scoreBoard.begin();
	while(i != scoreBoard.end()){
		flipedScoreBoard.insert(std::pair<int,string>(i->second,i->first));
		i++;
	}

	multimap<int,string>::iterator it = flipedScoreBoard.begin();
	while(it != flipedScoreBoard.end()){
		user = it->second;
		score = std::to_string(it-> first);
		scoreBuffer.push_back(user + sep + score);
		it++;
	}

	return scoreBuffer;
}
