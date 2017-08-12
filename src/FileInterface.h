/*
 * FileInterface.h
 *
 *  Created on: Jun 2, 2017
 *      Author: user
 */

#ifndef SRC_FILEINTERFACE_H_
#define SRC_FILEINTERFACE_H_

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

namespace networkingLab
{

	class FileInterface
	{
	public:

		FileInterface()
		{

		}
		virtual ~FileInterface(){}
		virtual void close()=0;
		virtual int read(char* buffer, size_t length)=0;
		virtual int write(const std::string& msg)=0;
		virtual int append(const std::string& msg){return 0;}
	};


}




#endif /* SRC_FILEINTERFACE_H_ */
