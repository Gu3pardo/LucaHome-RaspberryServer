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
#include "../../dataaccess/databases/MealDatabase.h"
#include "../../domain/classes/Meal.h"

using namespace std;

#ifndef MEAL_SERVICE_H
#define MEAL_SERVICE_H

class MealService
{
private:
	MealDatabase _mealDatabase;

	string getJsonString();

	char addMeal(vector<string>);
	char updateMeal(vector<string>);
	char deleteMeal(string);

public:
	MealService();
	~MealService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
