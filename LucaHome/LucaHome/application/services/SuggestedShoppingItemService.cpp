#include "SuggestedShoppingItemService.h"

/*===============PUBLIC==============*/

SuggestedShoppingItemService::SuggestedShoppingItemService() {}

SuggestedShoppingItemService::~SuggestedShoppingItemService() {}

void SuggestedShoppingItemService::Initialize(string databaseName)
{
	_suggestedShoppingItemDatabase = SuggestedShoppingItemDatabase(databaseName);
}

string SuggestedShoppingItemService::PerformAction(vector<string> data)
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
		if (data.size() == SUGGESTED_SHOPPING_ITEM_DATA_SIZE)
		{
			char error = addSuggestedShoppingItem(data);
			if (!error)
			{
				return SUGGESTED_SHOPPING_ITEM_ADD_SUCCESS;
			}
			return SUGGESTED_SHOPPING_ITEM_ERROR_ADD;
		}
		return SUGGESTED_SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == SUGGESTED_SHOPPING_ITEM_DATA_SIZE)
		{
			char error = updateSuggestedShoppingItem(data);
			if (!error)
			{
				return SUGGESTED_SHOPPING_ITEM_UPDATE_SUCCESS;
			}
			return SUGGESTED_SHOPPING_ITEM_ERROR_UPDATE;
		}
		return SUGGESTED_SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteSuggestedShoppingItem(actionParameter);
		if (!error)
		{
			return SUGGESTED_SHOPPING_ITEM_DELETE_SUCCESS;
		}
		return SUGGESTED_SHOPPING_ITEM_ERROR_DELETE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void SuggestedShoppingItemService::Dispose()
{
	_suggestedShoppingItemDatabase.Dispose();
}

/*==============PRIVATE==============*/

string SuggestedShoppingItemService::getJsonString()
{
	vector<SuggestedShoppingItem> suggestedShoppingItemList = _suggestedShoppingItemDatabase.GetList();

	stringstream data;
	for (int index = 0; index < suggestedShoppingItemList.size(); index++)
	{
		data << suggestedShoppingItemList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"SuggestedShoppingItem\","
		<< "\"Action\":\"Get\","
		<< "\"Error\":0,"
		<< "\"Success\":true,"
		<< "\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char SuggestedShoppingItemService::addSuggestedShoppingItem(vector<string> newSuggestedShoppingItemData)
{
	SuggestedShoppingItem newSuggestedShoppingItem(
		newSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_UUID_INDEX].c_str(),
		newSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_NAME_INDEX].c_str(),
		newSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_TYPE_INDEX].c_str(),
		atoi(newSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_QUANTITY_INDEX].c_str()),
		newSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_UNIT_INDEX].c_str());
	return _suggestedShoppingItemDatabase.Insert(newSuggestedShoppingItem);
}

char SuggestedShoppingItemService::updateSuggestedShoppingItem(vector<string> updateSuggestedShoppingItemData)
{
	SuggestedShoppingItem updateSuggestedShoppingItem(
		updateSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_UUID_INDEX].c_str(),
		updateSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_NAME_INDEX].c_str(),
		updateSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_TYPE_INDEX].c_str(),
		atoi(updateSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_QUANTITY_INDEX].c_str()),
		updateSuggestedShoppingItemData[SUGGESTED_SHOPPING_ITEM_UNIT_INDEX].c_str());
	return _suggestedShoppingItemDatabase.Update(updateSuggestedShoppingItem);
}

char SuggestedShoppingItemService::deleteSuggestedShoppingItem(string deleteUuid)
{
	return _suggestedShoppingItemDatabase.Delete(deleteUuid);
}
