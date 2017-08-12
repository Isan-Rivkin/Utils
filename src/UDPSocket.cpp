/*
 * UDPSocket.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: user
 */

#include "UDPSocket.h"
#include <iostream>
using namespace std;

namespace networkingLab
{

UDPSocket::~UDPSocket()
{
	// TODO Auto-generated destructor stub
}

/**
 * 	-  initialize a UDP socket and binds it on
 * 	the given port. if no port is specified a default
 * 	port 9999 is set. This UDP socket can be used both
 * 	for server socket and client socket
 *
 */
UDPSocket::UDPSocket(int port):Socket(udp)
{	last_port =0;
	client_socket =0;
	bind(port);
//	if(port < 0 && port >= 10000)
//	{
//		std::cout<<"invalid port rage [1,9999]"<<std::endl;
//		return;
//	}
//	this->myPort = port;
//	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
//	if(socket_fd < 0)
//	{
//		std::cout<<"Could not allocate a socket."<<std::endl;
//		return;
//	}
//	bzero((char*)&mLocal,sizeof(mLocal));
//	mLocal.sin_family = (short)AF_INET;
//	mLocal.sin_addr.s_addr = htonl(INADDR_ANY);
//	mLocal.sin_port=htons(this->myPort);
//	if(bind(socket_fd,(struct sockaddr*)&mLocal,sizeof(mLocal))<0)
//	{
//		perror("Error - socket might be in use");
//	}
}

/**
 * 	- reads an incoming message from the UDP socket. the message is
 * 	copied into the given buffer up to the specified length.
 */
int UDPSocket::recv(char* buffer, int length)
{
//	socklen_t fsize = sizeof(mLocal);
//	int n=recvfrom(socket_fd,buffer,length, 0,(struct sockaddr *)&mLocal,&fsize);
//	if(n<0)
//	{
//		perror("recv(): Error reciving data");
//	}
	int n = this->read(buffer, length);
	return n;

}

/**
 * 	- sends the given message as a UDP message
 * 	to the given address specified by IP and port.
 *
 */
int UDPSocket::sendTo(string msg, string ip, int port)
{
	this->last_ip = ip;
	this->last_port=port;
	this->connect(ip, port);
	int n=this->write(msg);
	return n;
}
/**
 * 	- reply to an incoming message,
 * 	this method will send the given message as a UDP
 * 	message to the peer from which the last message was received.
 *
 */
int UDPSocket::reply(string msg)
{
	return sendTo(msg, last_ip, last_port);
}
/**
 * - close the UDP socket.
 */
void UDPSocket::close()
{
	shutdown(socket_fd, SHUT_RDWR);
	shutdown(client_socket,SHUT_RDWR);
}

/**
 * - return the sender IP of the last received message.
 */
string UDPSocket::fromAddr()
{
	return last_ip;
}

} /* namespace networkingLab */
