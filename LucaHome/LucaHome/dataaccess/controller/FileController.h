#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

class FileController
{
public:
	FileController();
	~FileController();

	std::string ReadFile(std::string path);
	std::vector<std::string> ReadFileList(std::string path);
	bool SaveFile(std::string path, std::string content);
};

#endif
