#include "MealService.h"

/*===============PUBLIC==============*/

MealService::MealService() {}

MealService::~MealService() {}

void MealService::Initialize(string databaseName)
{
	_mealDatabase = MealDatabase(databaseName);
}

string MealService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	else if (action == ADD)
	{
		if (data.size() == MEAL_DATA_SIZE)
		{
			char error = addMeal(data);
			if (!error)
			{
				return MEAL_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Meal\",\"Error\":135,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return MEAL_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MEAL_DATA_SIZE)
		{
			char error = updateMeal(data);
			if (!error)
			{
				return MEAL_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Meal\",\"Error\":135,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return MEAL_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteMeal(actionParameter);
		if (!error)
		{
			return MEAL_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "{\"Category\":\"Meal\",\"Error\":135,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MealService::Dispose()
{
	_mealDatabase.Dispose();
}

/*==============PRIVATE==============*/

string MealService::getJsonString()
{
	vector<Meal> mealList = _mealDatabase.GetList();

	stringstream data;
	for (int index = 0; index < mealList.size(); index++)
	{
		data << mealList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"Meal\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char MealService::addMeal(vector<string> newMealData)
{
	vector<string> shoppingItemUuidList = Tools::Explode(",,", newMealData[MEAL_SHOPPING_UUID_LIST_INDEX].c_str());
	Meal newMeal(
		newMealData[MEAL_UUID_INDEX].c_str(),
		newMealData[MEAL_TITLE_INDEX].c_str(),
		newMealData[MEAL_DESCRIPTION_INDEX].c_str(),
		atoi(newMealData[MEAL_WEEKDAY_INDEX].c_str()),
		atoi(newMealData[MEAL_DAY_INDEX].c_str()),
		atoi(newMealData[MEAL_MONTH_INDEX].c_str()),
		atoi(newMealData[MEAL_YEAR_INDEX].c_str()),
		shoppingItemUuidList);
	return _mealDatabase.Insert(newMeal);
}

char MealService::updateMeal(vector<string> updateMealData)
{
	vector<string> shoppingItemUuidList = Tools::Explode(",,", updateMealData[MEAL_SHOPPING_UUID_LIST_INDEX].c_str());
	Meal updateMeal(
		updateMealData[MEAL_UUID_INDEX].c_str(),
		updateMealData[MEAL_TITLE_INDEX].c_str(),
		updateMealData[MEAL_DESCRIPTION_INDEX].c_str(),
		atoi(updateMealData[MEAL_WEEKDAY_INDEX].c_str()),
		atoi(updateMealData[MEAL_DAY_INDEX].c_str()),
		atoi(updateMealData[MEAL_MONTH_INDEX].c_str()),
		atoi(updateMealData[MEAL_YEAR_INDEX].c_str()),
		shoppingItemUuidList);
	return _mealDatabase.Update(updateMeal);
}

char MealService::deleteMeal(string deleteUuid)
{
	return _mealDatabase.Delete(deleteUuid);
}
