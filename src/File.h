/*
 * File.h
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#ifndef SRC_FILE_H_
#define SRC_FILE_H_


#include "FileInterface.h"
#include <strings.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


namespace networkingLab
{

class File : public networkingLab::FileInterface
{
private:
	std::string path;
	std::string fileContent;
	int fd;

public:
	File(const std::string & path);
	virtual ~File();

public:

	virtual void close();
	virtual int read(char* buffer, size_t length);
	virtual int write(const std::string& msg);
	virtual int append(const std::string& msg);

};

} /* namespace networkingLab */

#endif /* SRC_FILE_H_ */
