#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef CHANGE_H
#define CHANGE_H

class Change
{
private:
	string _uuid;
	string _type;
	string _userName;
	int _hour;
	int _minute;
	int _day;
	int _month;
	int _year;

public:
	Change();
	Change(string, string, string, int, int, int, int, int);
	~Change();

	void SetUuid(string);
	string GetUuid();

	void SetType(string);
	string GetType();

	void SetUserName(string);
	string GetUserName();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	string JsonString();
	string ToString();
};

#endif
