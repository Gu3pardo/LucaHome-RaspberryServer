#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef BIRTHDAY_H
#define BIRTHDAY_H

class Birthday
{
private:
	string _uuid;
	string _name;
	int _day;
	int _month;
	int _year;
	string _group;
	bool _remindMe;
	bool _sentMail;

public:
	Birthday();
	Birthday(string, string, int, int, int, string, bool, bool);
	~Birthday();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	int GetAge();
	bool HasBirthday();

	void SetGroup(string);
	string GetGroup();

	void SetRemindMe(bool);
	bool GetRemindMe();

	void SetSentMail(bool);
	bool GetSentMail();

	string JsonString();
	string ToString();
};

#endif
