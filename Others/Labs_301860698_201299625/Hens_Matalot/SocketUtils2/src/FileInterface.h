/*
 * FileInterface.h
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#ifndef FILEINTERFACE_H_
#define FILEINTERFACE_H_


#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


using namespace std;


namespace npl {

class FileInterface {
protected:
	int socket_fd;
public:
	virtual void close()=0;
	virtual int read(char* buffer, int length);
	virtual int write(const char* buffer, int length);

	virtual ~FileInterface();
};
}  // namespace name
#endif /* FILEINTERFACE_H_ */
