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

#include "../common/dto/CoinDto.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#define GET "GET"
#define ALL "ALL"
#define FOR_USER "FOR_USER"
#define ADD "ADD"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define COIN_DATA_SIZE 8
#define ID_INDEX 4
#define NAME_INDEX 5
#define TYPE_INDEX 6
#define AMOUNT_INDEX 7

#ifndef COINSERVICE_H
#define COINSERVICE_H

class CoinService
{
private:
	std::string _coinFile;
	std::vector<CoinDto> _coinList;

	FileController _fileController;
	XmlService _xmlService;

	void loadCoins();
	void saveCoins(ChangeService, std::string);

	std::string getRestStringAll();
	std::string getRestStringUser(std::string);

	bool addCoin(std::vector<std::string>, ChangeService, std::string);
	bool updateCoin(std::vector<std::string>, ChangeService, std::string);
	bool deleteCoin(int, ChangeService, std::string);

public:
	CoinService();
	~CoinService();

	void Initialize(FileController, std::string);
	void ReloadData();
	std::string PerformAction(std::string, std::vector<std::string>, ChangeService, std::string);
};

#endif
