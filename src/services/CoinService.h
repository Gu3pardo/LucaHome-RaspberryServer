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

#include "../common/dto/CoinDto.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef COINSERVICE_H
#define COINSERVICE_H

class CoinService
{
private:
	std::string _coinFile;
	std::vector<CoinDto> _coinList;

	FileController _fileController;
	XmlService _xmlService;

	void saveCoins(ChangeService, std::string);

	std::string getJsonStringAll();
	std::string getJsonStringUser(std::string);

	bool addCoin(std::vector<std::string>, ChangeService, std::string);
	bool updateCoin(std::vector<std::string>, ChangeService, std::string);
	bool deleteCoin(int, ChangeService, std::string);

public:
	CoinService();
	~CoinService();

	void Initialize(FileController, std::string);
	void LoadData();
	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);
};

#endif
