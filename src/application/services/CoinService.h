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

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/databases/CoinDatabase.h"
#include "../../domain/classes/Coin.h"

using namespace std;

#ifndef COIN_SERVICE_H
#define COIN_SERVICE_H

class CoinService
{
private:
	CoinDatabase _coinDatabase;

	string getAllJsonString();
	string getUserJsonString(string);

	char addCoin(vector<string>);
	char updateCoin(vector<string>);
	char deleteCoin(vector<string>);

public:
	CoinService();
	~CoinService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
