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
#include "../../dataaccess/databases/SuggestedMealDatabase.h"
#include "../../domain/classes/SuggestedMeal.h"

using namespace std;

#ifndef SUGGESTED_MEAL_SERVICE_H
#define SUGGESTED_MEAL_SERVICE_H

class SuggestedMealService
{
private:
	SuggestedMealDatabase _suggestedMealDatabase;

	string getJsonString();

	char addSuggestedMeal(vector<string>);
	char updateSuggestedMeal(vector<string>);
	char deleteSuggestedMeal(string);

public:
	SuggestedMealService();
	~SuggestedMealService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
