#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/databases/MoneyLogItemDatabase.h"
#include "../../domain/classes/MoneyLogItem.h"

using namespace std;

#ifndef MONEY_LOG_SERVICE_H
#define MONEY_LOG_SERVICE_H

class MoneyLogService
{
private:
	MoneyLogItemDatabase _moneyLogItemDatabase;

	string getJsonString();

	char addMoneyLogItem(vector<string>);
	char updateMoneyLogItem(vector<string>);
	char deleteMoneyLogItem(string);

public:
	MoneyLogService();
	~MoneyLogService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
