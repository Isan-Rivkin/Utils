/*
 * GeneralMultipleTCPListener.h
 *
 *  Created on: Jun 23, 2017
 *      Author: user
 */

#ifndef SRC_GENERALMULTIPLETCPLISTENER_H_
#define SRC_GENERALMULTIPLETCPLISTENER_H_


#include <iostream>
#include <stdio.h>
#include <vector>
#include "Socket.h"
using namespace std;

namespace networkingLab {

class GeneralMultipleTCPListener
{
private:
	vector<Socket*> mSockets_list;
public:
	GeneralMultipleTCPListener();
	virtual ~GeneralMultipleTCPListener();
	void addSocket(Socket* socket);
	void addSockets(vector<Socket*> socketVec);
	Socket* listenToSocket();

};

} /* namespace networkingLab */

#endif /* SRC_GENERALMULTIPLETCPLISTENER_H_ */
