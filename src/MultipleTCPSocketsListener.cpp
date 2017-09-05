/*
 * MultipleTCPSocketsListener.cpp
 *
 *  Created on: May 28, 2017
 *      Author: user
 */

#include "MultipleTCPSocketsListener.h"

namespace networkingLab
{

MultipleTCPSocketsListener::MultipleTCPSocketsListener()
{
	// TODO Auto-generated constructor stub

}

MultipleTCPSocketsListener::~MultipleTCPSocketsListener()
{
	// TODO Auto-generated destructor stub
}


/*
 * Add the given socket to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSocket(TCPSocket* socket)
{
	vector<TCPSocket*>::iterator it = mSockets_list.begin();
	it = mSockets_list.begin();
	it = mSockets_list.insert(it, socket);
}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec)
{
	vector<TCPSocket*>::iterator it, begin, end;
	it = mSockets_list.begin();
	begin = socketVec.begin();
	end = socketVec.end();
	mSockets_list.insert(it,begin,end);
}
/**
 * find a socket from the list
 */
TCPSocket* MultipleTCPSocketsListener::pullOut(const string& ip, size_t port)
{
	vector<TCPSocket*>::iterator it,begin,end;
	begin = mSockets_list.begin();
	end = mSockets_list.end();
	int index =0;
	while(begin != end)
	{
		 TCPSocket * s = *(begin);
		 sockaddr_in desc = s->getRemoteDescriptor();
		 size_t tempPort = htons(desc.sin_port);
		 if(tempPort == port)
		 {
			 mSockets_list.erase(begin);
			 return s;
		 }
		begin++;
		index++;
	}
	return NULL;
}
TCPSocket* MultipleTCPSocketsListener::pullOut(TCPSocket* socket)
{
		vector<TCPSocket*>::iterator it,begin,end;
		begin = mSockets_list.begin();
		end = mSockets_list.end();
		bool found = false;
		while(begin != end)
		{
			if(*(begin) == socket)
			{
				TCPSocket * ret = *begin;
				mSockets_list.erase(begin);
				return ret;
			}
			begin++;
		}
		if(!found)
		{
			cout <<" [MiltipleListener:] couldn't find requested socket! " << endl;
		}
	return NULL;
}
/*
 * This method checks to see if any of the previous given sockets are ready for reading
 * It returns one of the Sockets that are ready.
 */
TCPSocket* MultipleTCPSocketsListener::listenToSocket()
{
	vector<TCPSocket*>::iterator it_begin = mSockets_list.begin();
	vector<TCPSocket*>::iterator it_end = mSockets_list.end();
	//TODO: create local set for the select function (fd_set)
	fd_set fd;
	FD_ZERO(&fd);
	int highestFDNum;

	//TODO: fill the set with file descriptors from the socket list using (FD_SET macro)
	while(it_begin != it_end)
	{
		if(highestFDNum < (*it_begin)->getSocketFileDescriptor())
		{
			highestFDNum = (*it_begin)->getSocketFileDescriptor();
		}
		FD_SET((*it_begin)->getSocketFileDescriptor(),&fd);
		it_begin++;
	}
	int result = select(highestFDNum+1, &fd,NULL,NULL,NULL);
	if(result)
	{
		it_begin = mSockets_list.begin();
		while(it_begin != it_end)
		{
			TCPSocket* readySocket = *(it_begin);
			if(FD_ISSET(readySocket->getSocketFileDescriptor(), &fd))
			{
				return readySocket;
			}
			it_begin++;
		}
	}
	//TODO: if select return a valid socket return the matching TCPSocket object otherwise return NULL
	return NULL;
}

TCPSocket* MultipleTCPSocketsListener::find(string ip, size_t port)
{
	vector<TCPSocket*>::iterator it,begin,end;
	begin = mSockets_list.begin();
	end = mSockets_list.end();
	int index =0;
	while(begin != end)
	{
		 TCPSocket * s = *(begin);
		 sockaddr_in desc = s->getRemoteDescriptor();
		 size_t tempPort = htons(desc.sin_port);
		 if(tempPort == port)
		 {
			 return s;
		 }
		begin++;
		index++;
	}
	return NULL;
}

TCPSocket* MultipleTCPSocketsListener::find(TCPSocket* socket)
{
	vector<TCPSocket*>::iterator it,begin,end;
			begin = mSockets_list.begin();
			end = mSockets_list.end();
			bool found = false;
			while(begin != end)
			{
				if(*(begin) == socket)
				{
					TCPSocket * ret = *begin;
					return ret;
				}
			}
			if(!found)
			{
				cout <<" [MiltipleListener:] couldn't find requested socket! " << endl;
			}
		return NULL;
}

vector<TCPSocket*> MultipleTCPSocketsListener::getAll()
{
	return mSockets_list;
}

} /* namespace networkingLab */

