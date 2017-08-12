/*
 * GeneralMultipleTCPListener.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: user
 */

#include "GeneralMultipleTCPListener.h"

namespace networkingLab {

GeneralMultipleTCPListener::GeneralMultipleTCPListener()
{

}

GeneralMultipleTCPListener::~GeneralMultipleTCPListener()
{
}

void GeneralMultipleTCPListener::addSocket(Socket* socket)
{
	vector<Socket*>::iterator it = mSockets_list.begin();
	it = mSockets_list.begin();
	it = mSockets_list.insert(it, socket);
}

void GeneralMultipleTCPListener::addSockets(vector<Socket*> socketVec)
{
	vector<Socket*>::iterator it, begin, end;
	it = mSockets_list.begin();
	begin = socketVec.begin();
	end = socketVec.end();
	mSockets_list.insert(it,begin,end);
}

Socket* GeneralMultipleTCPListener::listenToSocket()
{
	vector<Socket*>::iterator it_begin = mSockets_list.begin();
	vector<Socket*>::iterator it_end = mSockets_list.end();
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

	//TODO: perform the select
	cout <<" Have " <<mSockets_list.size() << " socks" <<endl;
	int result = select(highestFDNum+1, &fd,NULL,NULL,NULL);
	cout <<" getting nowehere "<<endl;
	//TODO: check the returned value from the select to find the socket that is ready
	if(result)
	{
		it_begin = mSockets_list.begin();
		while(it_begin != it_end)
		{
			Socket* readySocket = *(it_begin);
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

} /* namespace networkingLab */
