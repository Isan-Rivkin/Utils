/*
 * TCPSocket.h
 *
 *  Created on: Apr 30, 2017
 *      Author: user
 */

#ifndef SRC_TCPSOCKET_H_
#define SRC_TCPSOCKET_H_

#include <strings.h>
#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include <inttypes.h>
#include <netdb.h>

#include <arpa/inet.h>
#include "Socket.h"

using namespace std;
namespace networkingLab
{
	class TCPSocket : public networkingLab::Socket
	{

	protected:
		string mPeerIP;
		bool isClient;
		in_port_t mPeerPort;

	public:
		/**
		 * ctor to create a TCP socket.
		 */
		TCPSocket(size_t pPort);
		/**
		 * Ctor to create client TCP socket and connect it to the remote peer in given ip+port
		 */
		TCPSocket(const std::string & pPeerIP, size_t pPort);
	private:
		/**
		 *3rd ctor for the client handler, filedescriptor->socket_fd, port ip and shit of both peers
		 */
		TCPSocket(int socket_fd, sockaddr_in * pLocal, sockaddr_in * pRemote);
		/**
		 * perform listen and accept on server socket,
		 * this function returns a new TCPSocket object to acommunicate over the incoming session.
		 */
	public:
		/**
		 * listen - server related (backlog)
		 */
		void listen();
		/**
		 * read from a socket into the given buffer up to the buffer up to the length, return num of bytes read.
		 */
	//	int recv(char* pBuffer, size_t pLength);
		/*
		 * send the given buffer to the socket
		 */
//		int send(const char* pMsg, size_t pLength);
		/*
		 * close socket and free resources
		 */
		void close();
		/*
		 * return the adress of the connected peer.
		 */
		string fromAffr();
	//	int getSocketFileDescriptor();
		/**
		 * perform listen and accept on server socket,
		 * this function returns a new TCPSocket object to acommunicate over the incoming session.
		 */
		virtual TCPSocket* accept();
		/**
		 * Get peers port
		 */
		in_port_t getPeerPort();
	};

}

#endif /* SRC_TCPSOCKET_H_ */
