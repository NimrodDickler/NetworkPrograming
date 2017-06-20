/*
 * FileInterface.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#include "FileInterface.h"


using namespace npl;




FileInterface:: ~FileInterface(){

}

int FileInterface::read(char* buffer, int length){
	return ::read(socket_fd,buffer,length);
}
int FileInterface::write(const char* buffer, int length){
	return ::write(socket_fd,buffer,length);
}

