#include "SuggestedMealService.h"

/*===============PUBLIC==============*/

SuggestedMealService::SuggestedMealService() {}

SuggestedMealService::~SuggestedMealService() {}

void SuggestedMealService::Initialize(string databaseName)
{
	_suggestedMealDatabase = SuggestedMealDatabase(databaseName);
}

string SuggestedMealService::PerformAction(vector<string> data)
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
		if (data.size() == SUGGESTED_MEAL_DATA_SIZE)
		{
			char error = addSuggestedMeal(data);
			if (!error)
			{
				return SUGGESTED_MEAL_ADD_SUCCESS;
			}
			return SUGGESTED_MEAL_ERROR_ADD;
		}
		return SUGGESTED_MEAL_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == SUGGESTED_MEAL_DATA_SIZE)
		{
			char error = updateSuggestedMeal(data);
			if (!error)
			{
				return SUGGESTED_MEAL_UPDATE_SUCCESS;
			}
			return SUGGESTED_MEAL_ERROR_UPDATE;
		}
		return SUGGESTED_MEAL_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteSuggestedMeal(actionParameter);
		if (!error)
		{
			return SUGGESTED_MEAL_DELETE_SUCCESS;
		}
		return SUGGESTED_MEAL_ERROR_DELETE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void SuggestedMealService::Dispose()
{
	_suggestedMealDatabase.Dispose();
}

/*==============PRIVATE==============*/

string SuggestedMealService::getJsonString()
{
	vector<SuggestedMeal> suggestedMealList = _suggestedMealDatabase.GetList();

	stringstream data;
	for (int index = 0; index < suggestedMealList.size(); index++)
	{
		data << suggestedMealList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"SuggestedMeal\","
		<< "\"Action\":\"Get\","
		<< "\"Error\":0,"
		<< "\"Success\":true,"
		<< "\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char SuggestedMealService::addSuggestedMeal(vector<string> newSuggestedMealData)
{
	vector<string> shoppingItemUuidList = Tools::Explode(",", newSuggestedMealData[SUGGESTED_MEAL_SHOPPING_UUID_LIST_INDEX].c_str());
	SuggestedMeal newSuggestedMeal(
		newSuggestedMealData[SUGGESTED_MEAL_UUID_INDEX].c_str(),
		newSuggestedMealData[SUGGESTED_MEAL_TITLE_INDEX].c_str(),
		newSuggestedMealData[SUGGESTED_MEAL_DESCRIPTION_INDEX].c_str(),
		atoi(newSuggestedMealData[SUGGESTED_MEAL_RATING_INDEX].c_str()),
		atoi(newSuggestedMealData[SUGGESTED_MEAL_USE_COUNTER_INDEX].c_str()),
		shoppingItemUuidList);
	return _suggestedMealDatabase.Insert(newSuggestedMeal);
}

char SuggestedMealService::updateSuggestedMeal(vector<string> updateSuggestedMealData)
{
	vector<string> shoppingItemUuidList = Tools::Explode(",", updateSuggestedMealData[SUGGESTED_MEAL_SHOPPING_UUID_LIST_INDEX].c_str());
	SuggestedMeal updateSuggestedMeal(
		updateSuggestedMealData[SUGGESTED_MEAL_UUID_INDEX].c_str(),
		updateSuggestedMealData[SUGGESTED_MEAL_TITLE_INDEX].c_str(),
		updateSuggestedMealData[SUGGESTED_MEAL_DESCRIPTION_INDEX].c_str(),
		atoi(updateSuggestedMealData[SUGGESTED_MEAL_RATING_INDEX].c_str()),
		atoi(updateSuggestedMealData[SUGGESTED_MEAL_USE_COUNTER_INDEX].c_str()),
		shoppingItemUuidList);
	return _suggestedMealDatabase.Update(updateSuggestedMeal);
}

char SuggestedMealService::deleteSuggestedMeal(string deleteUuid)
{
	return _suggestedMealDatabase.Delete(deleteUuid);
}
