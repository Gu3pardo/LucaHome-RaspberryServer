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

#include "../../common/dto/ChangeDto.h"
#include "../../common/Constants.h"
#include "../../controller/FileController.h"
#include "../xml/XmlService.h"

#ifndef CHANGESERVICE_H
#define CHANGESERVICE_H

class ChangeService
{
  private:
	std::string _changeFile;
	std::vector<ChangeDto> _changeList;

	FileController _fileController;
	XmlService _xmlService;

	std::string getJsonString();
	std::string getPhpString();

  public:
	ChangeService();
	~ChangeService();

	void Initialize(FileController, std::string);
	void UpdateChange(std::string, std::string);
	void LoadData();

	std::string PerformAction(std::vector<std::string>);
};

#endif
