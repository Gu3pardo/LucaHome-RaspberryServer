#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef MONEY_METER_DATA_DTO_H
#define MONEY_METER_DATA_DTO_H

class MoneyMeterDataDto
{
private:
	int _id;
	int _typeId;
	std::string _bank;
	std::string _plan;
	double _amount;
	std::string _unit;
	int _day;
	int _month;
	int _year;
	std::string _user;

public:
	MoneyMeterDataDto();
	MoneyMeterDataDto(int, int, std::string, std::string, double, std::string, int, int, int, std::string);
	~MoneyMeterDataDto();

	void SetId(int);
	int GetId();

	void SetTypeId(int);
	int GetTypeId();

	void SetBank(std::string);
	std::string GetBank();

	void SetPlan(std::string);
	std::string GetPlan();

	void SetAmount(double);
	double GetAmount();

	void SetUnit(std::string);
	std::string GetUnit();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetUser(std::string);
	std::string GetUser();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
