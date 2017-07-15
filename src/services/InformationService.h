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
#include <syslog.h>

#include "../common/dto/InformationDto.h"
#include "../common/utils/Tools.h"
#include "../controller/FileController.h"
#include "xml/XmlService.h"

#define GET "GET"
#define REST "REST"
#define WEBSITE "WEBSITE"
#define INFORMATION_DATA_SIZE 5

#ifndef INFORMATIONSERVICE_H
#define INFORMATIONSERVICE_H

class InformationService
{
  private:
	std::string _informationFile;
	InformationDto _informationList;

	FileController _fileController;
	XmlService _xmlService;

	void loadInformations();

	std::string getRestString();
	std::string getString();

  public:
	InformationService();
	~InformationService();

	void Initialize(FileController);
	std::string PerformAction(std::string, std::vector<std::string>);
	void ReloadInformationList();
};

#endif
