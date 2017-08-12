/*
 * MultipleTCPSocketsListener.h
 *
 *  Created on: May 28, 2017
 *      Author: user
 */

#ifndef SRC_MULTIPLETCPSOCKETSLISTENER_H_
#define SRC_MULTIPLETCPSOCKETSLISTENER_H_


#include <iostream>
#include <stdio.h>
#include <vector>
#include "TCPSocket.h"

using namespace std;
namespace networkingLab
{

class MultipleTCPSocketsListener
{
private:
	 vector<TCPSocket*> mSockets_list;
public:
	MultipleTCPSocketsListener();
	virtual ~MultipleTCPSocketsListener();
public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Set the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket();
	/**
	 * find a socket from the list
	 */
	TCPSocket* pullOut(const string & ip,size_t port);
	TCPSocket* pullOut(TCPSocket * socket);

};

} /* namespace networkingLab */

#endif /* SRC_MULTIPLETCPSOCKETSLISTENER_H_ */







