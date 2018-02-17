#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef SUGGESTED_MEAL_H
#define SUGGESTED_MEAL_H

class SuggestedMeal
{
private:
	string _uuid;
	string _title;
	string _description;
	int _rating;
	int _useCounter;
	vector<string> _shoppingItemUuidList{};

	string getShoppingItemUuidJson();

public:
	SuggestedMeal();
	SuggestedMeal(string, string, string, int, int, vector<string>);
	~SuggestedMeal();

	void SetUuid(string);
	string GetUuid();

	void SetTitle(string);
	string GetTitle();

	void SetDescription(string);
	string GetDescription();

	void SetRating(int);
	int GetRating();

	void SetUseCount(int);
	int GetUseCount();

	void SetShoppingItemUuidList(vector<string>);
	string GetShoppingItemUuidDbString();

	string JsonString();
	string ToString();
};

#endif
