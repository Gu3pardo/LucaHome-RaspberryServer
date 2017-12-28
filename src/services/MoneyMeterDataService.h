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

#include "../common/dto/MoneyMeterDataDto.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "AuthentificationService.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef MONEYMETERDATASERVICE_H
#define MONEYMETERDATASERVICE_H

class MoneyMeterDataService
{
private:
	std::string _moneyMeterDataFile;
	std::vector<MoneyMeterDataDto> _moneyMeterDataList;

	FileController _fileController;
	XmlService _xmlService;

	void saveMoneyMeterData(ChangeService, std::string);

	std::string getJsonString();
	std::string getJsonStringUser(std::string);

	bool addMoneyMeterData(std::vector<std::string>, ChangeService, std::string);
	bool updateMoneyMeterData(std::vector<std::string>, ChangeService, std::string);
	bool deleteMoneyMeterData(int, ChangeService, std::string);

public:
	MoneyMeterDataService();
	~MoneyMeterDataService();

	void Initialize(FileController, std::string);
	void LoadData();
	std::string PerformAction(std::vector<std::string>, AuthentificationService, ChangeService, std::string);
};

#endif
