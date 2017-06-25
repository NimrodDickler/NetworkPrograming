

#include "MultipleTCPSocketsListener.h"

using namespace std;


//MultipleTCPSocketsListener::MultipleTCPSocketsListener()
//{
//	this->SocketVector=new vector<TCPSocket*>();
//}

/*
 * Add the given socket to the socket list to be listen on
 */
bool MultipleTCPSocketsListener::addSocket(TCPSocket* socket)
{

	this->socketVector.push_back(socket);
	return true;
}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec)
{
	this->socketVector.clear();
	this->socketVector=socketVec;

}

/*
 * This method checks to see if any of the previous given sockets are ready for reading
 * It returns one of the Sockets that are ready.
 */
TCPSocket* MultipleTCPSocketsListener::listenToSocket()
{
	fd_set SocketSet;
	int check,maxfd=0;
	timeval timeout;
	FD_ZERO(&SocketSet);
	if(this->socketVector.size() == 0)
		return NULL;
	for(unsigned int i=0;i<this->socketVector.size();i++)
	{
		FD_SET(this->socketVector[i]->getSocketFid(),&SocketSet);
		if(this->socketVector[i]->getSocketFid()>maxfd)
			maxfd=this->socketVector[i]->getSocketFid();
	}
	timeout.tv_sec=30;
	timeout.tv_usec=0;
	sleep(0.5);
	check=select(maxfd+1,&SocketSet,NULL,NULL,&timeout);
	if(check==-1)
	{
		perror("Error has occured");
	}
	else
	{
		for(unsigned int i=0;i<this->socketVector.size();i++)
		{
			if(FD_ISSET(this->socketVector[i]->getSocketFid(),&SocketSet))
			{
				FD_CLR(this->socketVector[i]->getSocketFid(),&SocketSet);
				return this->socketVector[i];
			}
		}
	}

	return NULL;
}
void MultipleTCPSocketsListener::removeSocket(TCPSocket * sock)
{
	for(unsigned int i=0;i<socketVector.size();i++)
		if(this->socketVector[i]->getSocketFid() == sock->getSocketFid())
			this->socketVector.erase(this->socketVector.begin()+i);
}
void MultipleTCPSocketsListener::RemoveAndCloseSocket(TCPSocket* socket)
{
	for(unsigned int i=0;i<socketVector.size();i++)
		if(this->socketVector[i]->getSocketFid()==socket->getSocketFid())
		{
			this->socketVector.erase(this->socketVector.begin()+i);
			socket->cclose();
			return;
		}
}

