#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef SUGGESTED_SHOPPING_ITEM_H
#define SUGGESTED_SHOPPING_ITEM_H

class SuggestedShoppingItem
{
protected:
	string _uuid;
	string _name;
	string _type;
	int _quantity;
	string _unit;

public:
	SuggestedShoppingItem();
	SuggestedShoppingItem(string, string, string, int, string);
	~SuggestedShoppingItem();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetType(string);
	string GetType();

	void SetQuantity(int);
	void IncreaseQuantity(int);
	void DecreaseQuantity(int);
	int GetQuantity();

	void SetUnit(string);
	string GetUnit();

	string JsonString();
	string ToString();
};

#endif
