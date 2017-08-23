/*
 * Socket.h
 *
 *  Created on: May 22, 2017
 *      Author: user
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_
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
#include "FileInterface.h"

#define DEFAULT_PORT 6565

namespace networkingLab
{

enum StreamType {tcp,udp,tcp_client,tcp_handler};

class Socket : public FileInterface
{
protected:
	typedef sockaddr_in Descriptor;
	Descriptor mLocal;
	Descriptor mRemote;

	int myPort;
	int socket_fd;
	int mCommunicationSockTCP;
	StreamType sType;

public:
	virtual void close();
	virtual int read(char* buffer, size_t length);
	virtual int write(const char* pMsg, size_t pLength);
	virtual int write(const std::string& msg);
	virtual int bind(size_t port);
	// also use in udp + use for tcp client
	virtual bool connect(std::string& ip,size_t port);
	Socket(StreamType type);
	virtual ~Socket();
	/**
	 * yom shlishi eli meteor 9.30 our offices.
	 * if wants to join.
	 */
	// temp ctor - for tcp client and handler
	Socket(int port,Descriptor mLocal );
	int getSocketFileDescriptor();
	sockaddr_in getRemoteDescriptor();
	sockaddr_in getLocalDescriptor();
};
}

#endif /* SRC_SOCKET_H_ */
