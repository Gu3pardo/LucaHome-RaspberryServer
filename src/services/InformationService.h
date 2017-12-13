#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/dto/InformationDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "xml/XmlService.h"

#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

class InformationService
{
private:
	std::string _informationFile;
	InformationDto _informationList;

	FileController _fileController;
	XmlService _xmlService;

	std::string getJsonString();
	std::string getPhpString();

public:
	InformationService();
	~InformationService();

	void Initialize(FileController, std::string);
	std::string PerformAction(std::vector<std::string>);
	void LoadData();
};

#endif
