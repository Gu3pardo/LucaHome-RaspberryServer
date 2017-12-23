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

#include "../common/dto/MeterDataDto.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef METERDATASERVICE_H
#define METERDATASERVICE_H

class MeterDataService
{
private:
	std::string _meterDataFile;
	std::vector<MeterDataDto> _meterDataList;

	FileController _fileController;
	XmlService _xmlService;

	void saveMeterData(ChangeService, std::string);

	std::string getJsonString();
	std::string getPhpString();

	bool addMeterData(std::vector<std::string>, ChangeService, std::string);
	bool updateMeterData(std::vector<std::string>, ChangeService, std::string);
	bool deleteMeterData(int, ChangeService, std::string);

public:
	MeterDataService();
	~MeterDataService();

	void Initialize(FileController, std::string);
	void LoadData();
	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);
};

#endif
