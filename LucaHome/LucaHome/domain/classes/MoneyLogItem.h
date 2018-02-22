#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef MONEY_LOG_ITEM_H
#define MONEY_LOG_ITEM_H

class MoneyLogItem
{
private:
	string _uuid;
	string _typeUuid;
	string _bank;
	string _plan;
	double _amount;
	string _unit;
	string _userUuid;
	time_t _saveDate;

public:
	MoneyLogItem();
	MoneyLogItem(string, string, string, string, double, string, string, time_t);
	~MoneyLogItem();

	void SetUuid(string);
	string GetUuid();

	void SetTypeUuid(string);
	string GetTypeUuid();

	void SetBank(string);
	string GetBank();

	void SetPlan(string);
	string GetPlan();

	void SetAmount(double);
	double GetAmount();

	void SetUnit(string);
	string GetUnit();

	void SetUserUuid(string);
	string GetUserUuid();

	void SetSaveDate(time_t);
	time_t GetSaveDate();

	string JsonString();
	string ToString();
};

#endif
