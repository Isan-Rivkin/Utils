/*
 * Socket.cpp

 *
 *  Created on: Jun 2, 2017
 *      Author: user
 */

#include "Socket.h"
namespace networkingLab
{

void clean_up(int cond, int *sock)
{ printf("Exiting now.\n");
  ::close(*sock);
  exit(cond);
}

//get the type of the sockstream/dgram to define the protocol
	//there was a bug in bind method eliav used ::bind() and it worked...
//	Socket(int type)
//	{
//		socket_fd = socket(AF_INET,SOCK_DGRAM,0);
//
//	}
Socket::Socket(StreamType type)
{
	socket_fd = 0;
	sType = type;
	myPort = DEFAULT_PORT;

	switch(type)
	{
	case tcp:
	{
		socket_fd = socket(AF_INET,SOCK_STREAM,0);
		break;
	}
	case tcp_client:
		{
			socket_fd = socket(AF_INET,SOCK_STREAM,0);
			break;
		}
	case udp:
	{
		socket_fd = socket(AF_INET,SOCK_DGRAM,0);
		break;
	}
	default:
		break;
	}
	if(socket_fd < 0)
	{
		perror("Cannot Initiate Socket Connection type");
		clean_up(1,&socket_fd);
	}

}
void Socket::close()
{

}

int Socket::read(char* buffer, size_t length)
{	int n=0;
	if(sType == tcp)
	{

		n = ::read(mCommunicationSockTCP, buffer, length);
		//std::cout<<"READED NOT CLIENT : " << buffer <<std::endl;
	}
	else if(sType == tcp_client)
	{
	//	std::cout<<"READED CLIENT : " << buffer <<std::endl;

		n =::read(socket_fd, buffer, length);
	}
	else
	{
		socklen_t fSize = sizeof(mLocal);
		 n = ::recvfrom(socket_fd, buffer,length, 0,(struct sockaddr*)&mLocal,&fSize);
	}

	if(n<0)
	{
		perror("Socket class: Error recieving data");
	}
	return n;
}
int Socket::write(const std::string& msg)
{
	return this->write(msg.c_str(),msg.length());
}
int Socket::write(const char* pMsg, size_t pLength)
{
	int n=0;
	std::string msg = std::string(pMsg,pLength);

	if(sType == tcp || sType == tcp_client)
	{
		n = ::write(socket_fd, msg.data(), msg.length());
	}
	else
	{
		n = ::sendto(socket_fd,msg.data(),msg.length(),0,(struct sockaddr*)&mRemote,sizeof(mRemote));
	}
	if(n<0)
	{
		perror("Error: Socket class: write error N<0");
	}
	return n;
}

int Socket::bind(size_t port)
{
	myPort = port;
	bzero(&mLocal,sizeof(mLocal));
	mLocal.sin_family = AF_INET;
	mLocal.sin_port = htons(myPort);
	mLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	if(::bind(socket_fd,(struct sockaddr *)&mLocal,sizeof(mLocal))<0)
	{
		perror("Error binding.");
		//clean_up(1,&socket_fd);
		return 0;
	}
	return 1;
}
// seperate in dup sendTo using this connect method
bool Socket::connect(std::string& ip, size_t port)
{
	if(this->sType != udp)
	{
		myPort = port;

		bzero(&mLocal, sizeof(mLocal));
		mLocal.sin_family = AF_INET;
		mLocal.sin_addr.s_addr = inet_addr(ip.c_str());
	    mLocal.sin_port = htons(myPort);

	    if(::connect(socket_fd, (struct sockaddr *)&mLocal, sizeof(mLocal)) < 0)
	    {
	    	perror ("Error establishing communications unable to connect");
	    	exit(1);
	    }
	}
	else
	{
		bzero((char*)&mRemote,sizeof(mRemote));
		mRemote.sin_family=(short)AF_INET;
		mRemote.sin_port= htons(port);
		//assign ip address from type string to a given struct
		inet_pton(AF_INET, ip.c_str(), &(mRemote.sin_addr));
	}
	return true;
}
Socket::~Socket()
{

}
int Socket::getSocketFileDescriptor()
{
	return this->socket_fd;
}
sockaddr_in Socket::getRemoteDescriptor()
{
	return mRemote;
}

sockaddr_in Socket::getLocalDescriptor()
{
	return mLocal;
}

}


