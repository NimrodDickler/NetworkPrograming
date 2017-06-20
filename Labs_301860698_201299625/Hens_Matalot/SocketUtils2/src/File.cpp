/*
 * File.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: user
 */

#include "File.h"

using namespace npl;

File::File(char* path) {
	// TODO Auto-generated constructor stub

	file.open(path, fstream::in | fstream::out | fstream::app);

}

int File::read(char* buffer, int length) {

	if (file.is_open())
	  {
		length = file.tellg();
		buffer = new char [length];
		file.seekg (0, ios::beg);
		file.read(buffer ,length);
		while (!file.eof()) {
			file >> buffer;
		    cout<<buffer;
		 }

	  }
	puts("\n");

	return 0;
}

int File::write(const string& msg) {
	char* buff = new char[msg.length()+1];
	strcpy(buff,msg.c_str());
	long size = msg.size();
	file.write(buff, size);
    return 0;
}

void File::close() {
	file.close();
}

File::~File() {
	// TODO Auto-generated destructor stub
}

