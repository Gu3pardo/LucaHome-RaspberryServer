#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>

#include <cstdio>

#include "../dto/LogDto.h"
#include "../../controller/FileController.h"
#include "../../services/xml/XmlService.h"
#include "Tools.h"

#ifndef LOGGER_H
#define LOGGER_H

class Logger {
private:
	std::string _logPath;
	std::vector<std::string> _logFiles;
	std::vector<LogDto> _logList;

	FileController _fileController;
	XmlService _xmlService;

	std::vector<std::string> scanFolder();

public:
	Logger();
	~Logger();

	void Initialize(FileController, std::string);
	void AddLog(std::string, std::vector<std::string>, std::string);
};

#endif
