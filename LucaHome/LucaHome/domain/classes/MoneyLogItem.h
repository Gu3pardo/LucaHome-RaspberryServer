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
	int _day;
	int _month;
	int _year;
	string _user;

public:
	MoneyLogItem();
	MoneyLogItem(string, string, string, string, double, string, int, int, int, string);
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

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetUser(string);
	string GetUser();

	string JsonString();
	string ToString();
};

#endif
