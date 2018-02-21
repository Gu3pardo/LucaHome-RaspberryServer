#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"
#include "SuggestedShoppingItem.h"

using namespace std;

#ifndef SHOPPING_ITEM_H
#define SHOPPING_ITEM_H

class ShoppingItem : public SuggestedShoppingItem
{
private:
	time_t _creationTime;
	bool _sentDay7Reminder;

public:
	ShoppingItem();
	ShoppingItem(string, string, string, int, string, time_t, bool);
	~ShoppingItem();

	void SetCreationTime(time_t);
	time_t GetCreationTime();

	void SetSentDay7Reminder(bool);
	bool GetSentDay7Reminder();

	string JsonString();
	string ToString();
};

#endif
