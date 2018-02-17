#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef SHOPPING_ITEM_H
#define SHOPPING_ITEM_H

class ShoppingItem
{
private:
	string _uuid;
	string _name;
	string _type;
	int _quantity;
	string _unit;

public:
	ShoppingItem();
	ShoppingItem(string, string, string, int, string);
	~ShoppingItem();

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
