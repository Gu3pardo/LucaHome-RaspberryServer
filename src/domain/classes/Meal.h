#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef MEAL_H
#define MEAL_H

class Meal
{
private:
	string _uuid;
	string _title;
	string _description;
	int _weekday;
	int _day;
	int _month;
	int _year;
	vector<string> _shoppingItemUuidList{};

	string getShoppingItemUuidJson();

public:
	Meal();
	Meal(string, string, string, int, int, int, int, vector<string>);
	~Meal();

	void SetUuid(string);
	string GetUuid();

	void SetTitle(string);
	string GetTitle();

	void SetDescription(string);
	string GetDescription();

	void SetWeekday(int);
	int GetWeekday();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetShoppingItemUuidList(vector<string>);
	string GetShoppingItemUuidDbString();

	string JsonString();
	string ToString();
};

#endif
