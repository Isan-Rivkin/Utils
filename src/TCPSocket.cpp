/*
 * TCPSocket.cpp
 *
 *  Created on: Apr 30, 2017
 *      Author: user
 */

#include "TCPSocket.h"

namespace networkingLab
{
//void clean_up(int cond, int *sock)
//{ printf("Exiting now.\n");
//  close(*sock);
//  exit(cond);
//}
	/**
	 * ctor to create a TCP socket. - server
	 */
	TCPSocket::TCPSocket(size_t pPort):Socket(tcp),isClient(false)
	{

		mCommunicationSockTCP =0;
		bind(pPort);

	}
	/**
	 * Ctor to create client TCP socket and connect it to the remote peer in given ip+port
	 */
	TCPSocket::TCPSocket(const std::string& pPeerIP, size_t pPort):Socket(tcp_client),isClient(true)
	{

		mCommunicationSockTCP=0;
		mPeerIP = pPeerIP;
		this->connect(mPeerIP, pPort);
	}
	/**
	 *3rd ctor for the client handler, filedescriptor->socket_fd, port ip and shit of both peers
	 */
	TCPSocket::TCPSocket(int socket_imOn, sockaddr_in * pLocal, sockaddr_in * pRemote):Socket(tcp),isClient(false)
	{
		mPeerIP = pRemote->sin_addr.s_addr;
		socket_fd =0;
		myPort = pLocal->sin_port;
		this->mCommunicationSockTCP =socket_imOn;
		this->socket_fd=socket_imOn;
		this->mLocal = *pLocal;
		this->mRemote = *pRemote;
	}
	/**
	 * perform listen and accept on server socket,
	 * this function returns a new TCPSocket object to communicate over the incoming session.
	 */
	TCPSocket* TCPSocket::accept()
	{
		socklen_t len = sizeof(mRemote);
		mCommunicationSockTCP = ::accept(socket_fd,(struct sockaddr *)&mRemote,&len);
		if(mCommunicationSockTCP<0)
		{
			perror("failed to accept connection");
			exit(1);
		}
		mPeerIP = mRemote.sin_addr.s_addr;
		mPeerPort = mRemote.sin_port;
		TCPSocket * connection_socket = new TCPSocket(mCommunicationSockTCP,&mLocal, &mRemote);
		return connection_socket;
	}

	/*
	 * close socket and free resources
	 */
	void TCPSocket::close()
	{
		::close(this->socket_fd);
	}
	/*
	 * return the adress of the connected peer.
	 */
	string TCPSocket::fromAffr()
	{
		return mPeerIP;
	}


//	int TCPSocket::getSocketFileDescriptor()
//	{
//		return this->socket_fd;
//	}

	void networkingLab::TCPSocket::listen()
	{
		::listen(socket_fd, 500);
	}
	/**
	 * Get peers port
	 */
	in_port_t networkingLab::TCPSocket::getPeerPort()
	{
		return mPeerPort;
	}
}

