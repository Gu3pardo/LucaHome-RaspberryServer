#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/controller/MailController.h"
#include "../../dataaccess/databases/ShoppingItemDatabase.h"
#include "../../domain/classes/ShoppingItem.h"

using namespace std;

#ifndef SHOPPING_ITEM_SERVICE_H
#define SHOPPING_ITEM_SERVICE_H

class ShoppingItemService
{
private:
	ShoppingItemDatabase _shoppingItemDatabase;

	string getJsonString();

	char addShoppingItem(vector<string>);
	char updateShoppingItem(vector<string>);
	char deleteShoppingItem(string);

public:
	ShoppingItemService();
	~ShoppingItemService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	void CheckShoppingListToRemind();
};

#endif
