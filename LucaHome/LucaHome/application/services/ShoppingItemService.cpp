#include "ShoppingItemService.h"

/*===============PUBLIC==============*/

ShoppingItemService::ShoppingItemService() {}

ShoppingItemService::~ShoppingItemService() {}

void ShoppingItemService::Initialize(string databaseName)
{
	_shoppingItemDatabase = ShoppingItemDatabase(databaseName);
}

string ShoppingItemService::PerformAction(vector<string> data)
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
		if (data.size() == SHOPPING_ITEM_DATA_SIZE)
		{
			char error = addShoppingItem(data);
			if (!error)
			{
				return SHOPPING_ITEM_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == SHOPPING_ITEM_DATA_SIZE)
		{
			char error = updateShoppingItem(data);
			if (!error)
			{
				return SHOPPING_ITEM_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteShoppingItem(actionParameter);
		if (!error)
		{
			return SHOPPING_ITEM_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void ShoppingItemService::Dispose()
{
	_shoppingItemDatabase.Dispose();
}

/*==============PRIVATE==============*/

string ShoppingItemService::getJsonString()
{
	vector<ShoppingItem> shoppingItemList = _shoppingItemDatabase.GetList();

	stringstream data;
	for (int index = 0; index < shoppingItemList.size(); index++)
	{
		data << shoppingItemList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char ShoppingItemService::addShoppingItem(vector<string> newShoppingItemData)
{
	ShoppingItem newShoppingItem(
		newShoppingItemData[SHOPPING_ITEM_UUID_INDEX].c_str(),
		newShoppingItemData[SHOPPING_ITEM_NAME_INDEX].c_str(),
		newShoppingItemData[SHOPPING_ITEM_TYPE_INDEX].c_str(),
		atoi(newShoppingItemData[SHOPPING_ITEM_QUANTITY_INDEX].c_str()),
		newShoppingItemData[SHOPPING_ITEM_UNIT_INDEX].c_str());
	return _shoppingItemDatabase.Insert(_shoppingItemDatabase.GetList().size(), newShoppingItem);
}

char ShoppingItemService::updateShoppingItem(vector<string> updateShoppingItemData)
{
	ShoppingItem updateShoppingItem(
		updateShoppingItemData[SHOPPING_ITEM_UUID_INDEX].c_str(),
		updateShoppingItemData[SHOPPING_ITEM_NAME_INDEX].c_str(),
		updateShoppingItemData[SHOPPING_ITEM_TYPE_INDEX].c_str(),
		atoi(updateShoppingItemData[SHOPPING_ITEM_QUANTITY_INDEX].c_str()),
		updateShoppingItemData[SHOPPING_ITEM_UNIT_INDEX].c_str());
	return _shoppingItemDatabase.Update(updateShoppingItem);
}

char ShoppingItemService::deleteShoppingItem(string deleteUuid)
{
	return _shoppingItemDatabase.Delete(deleteUuid);
}
