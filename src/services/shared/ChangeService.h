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

#include "../../controller/FileController.h"
#include "../xml/XmlService.h"

#define CHANGE_DATA_SIZE 5
#define GET "GET"
#define REST "REST"
#define WEBSITE "WEBSITE"

#ifndef CHANGESERVICE_H
#define CHANGESERVICE_H

class ChangeService
{
  private:
	std::string _changeFile;
	std::vector<ChangeDto> _changeList;

	FileController _fileController;
	XmlService _xmlService;

	std::string getRestString();
	std::string getString();

  public:
	ChangeService();
	~ChangeService();

	void Initialize(FileController);
	void UpdateChange(std::string, std::string);
	void ReloadData();

	std::string PerformAction(std::string, std::vector<std::string>);
};

#endif
