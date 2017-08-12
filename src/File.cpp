/*
 * File.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: user
 */

#include "File.h"

namespace networkingLab {


File::File(const std::string& path)
{
	this->path = path;
}

File::~File()
{

}

void File::close()
{
	::close(fd);
}

int File::read(char* buffer, size_t length)
{

	  size_t offset = 0;
	  size_t bytes_read;

	  /* Open the file for reading.  */
	  fd = open (path.c_str(), O_RDONLY);

	  /* Read from the file, one chunk at a time. Continue until read
	     "comes up short", that is, reads less than we asked for.
	     This indicates that we've hit the end of the file.  */
	  do {
	    /* Read the next line's worth of bytes.  */
	    bytes_read = ::read(fd, buffer, length);
	    /* Keep count of our position in the file.  */
	    offset += bytes_read;
	  }
	  while (bytes_read == sizeof (buffer));
	  /* All done.  */
	  return bytes_read;
}
int File::append(const std::string& msg)
{
	 /* Open the file for writing. If it exists, append to it;
		     otherwise, create a new file.  */
		 fd= ::open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
		  /* Write the timestamp to the file.  */
		 ::write(fd, msg.c_str(), msg.length());
		 return 1;
}
int File::write(const std::string& msg)
{
	  /* Open the file for writing. If it exists, append to it;
	     otherwise, create a new file.  */
	  fd= ::open(path.c_str(), O_WRONLY | O_CREAT , 0666);
	  /* Write the timestamp to the file.  */
	 ::write(fd, msg.c_str(), msg.length());
	 return 1;
}

} /* namespace networkingLab */
