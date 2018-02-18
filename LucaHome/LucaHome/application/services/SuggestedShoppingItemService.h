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
#include "../../dataaccess/databases/SuggestedShoppingItemDatabase.h"
#include "../../domain/classes/SuggestedShoppingItem.h"

using namespace std;

#ifndef SUGGESTED_SHOPPING_ITEM_SERVICE_H
#define SUGGESTED_SHOPPING_ITEM_SERVICE_H

class SuggestedShoppingItemService
{
private:
	SuggestedShoppingItemDatabase _suggestedShoppingItemDatabase;

	string getJsonString();

	char addSuggestedShoppingItem(vector<string>);
	char updateSuggestedShoppingItem(vector<string>);
	char deleteSuggestedShoppingItem(string);

public:
	SuggestedShoppingItemService();
	~SuggestedShoppingItemService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
