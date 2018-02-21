#include "ShoppingItemService.h"

/*===============PUBLIC==============*/

ShoppingItemService::ShoppingItemService() {}

ShoppingItemService::~ShoppingItemService() {}

void ShoppingItemService::Initialize(string databaseName, MailController mailController)
{
	_shoppingItemDatabase = ShoppingItemDatabase(databaseName);
	_mailController = mailController;
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

void ShoppingItemService::CheckShoppingListToRemind()
{
	vector<ShoppingItem> shoppingItemList = _shoppingItemDatabase.GetList();
	vector<ShoppingItem> reminderList;

	time_t now = time(0);

	for (int index = 0; index < shoppingItemList.size(); index++)
	{
		ShoppingItem shoppingItem = shoppingItemList[index];
		double timeSinceCreation = difftime(now, shoppingItem.GetCreationTime());

		if (timeSinceCreation >= SECONDS_OF_7_DAYS && !shoppingItem.GetSentDay7Reminder()) {
			reminderList.push_back(shoppingItem);
		}
	}

	if (reminderList.size() > 0) {
		stringstream reminderMessage;
		reminderMessage << "You have following shopping items on your list for more then one week:\n";

		for (int reminderIndex = 0; reminderIndex < reminderList.size(); reminderIndex++) {
			ShoppingItem shoppingItem = reminderList[reminderIndex];
			shoppingItem.SetSentDay7Reminder(true);

			reminderMessage
				<< shoppingItem.GetName() << " "
				<< Tools::ConvertIntToStr(shoppingItem.GetQuantity()) << " "
				<< shoppingItem.GetUnit() << "\n";

			_shoppingItemDatabase.Update(shoppingItem);
		}

		_mailController.SendMail(reminderMessage.str());
	}
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
		newShoppingItemData[SHOPPING_ITEM_UNIT_INDEX].c_str(),
		atoi(newShoppingItemData[SHOPPING_ITEM_CREATION_TIME_INDEX].c_str()),
		atoi(newShoppingItemData[SHOPPING_ITEM_SENT_DAY_7_REMINDER_INDEX].c_str()) == 1);
	return _shoppingItemDatabase.Insert(_shoppingItemDatabase.GetList().size(), newShoppingItem);
}

char ShoppingItemService::updateShoppingItem(vector<string> updateShoppingItemData)
{
	ShoppingItem updateShoppingItem(
		updateShoppingItemData[SHOPPING_ITEM_UUID_INDEX].c_str(),
		updateShoppingItemData[SHOPPING_ITEM_NAME_INDEX].c_str(),
		updateShoppingItemData[SHOPPING_ITEM_TYPE_INDEX].c_str(),
		atoi(updateShoppingItemData[SHOPPING_ITEM_QUANTITY_INDEX].c_str()),
		updateShoppingItemData[SHOPPING_ITEM_UNIT_INDEX].c_str(),
		atoi(updateShoppingItemData[SHOPPING_ITEM_CREATION_TIME_INDEX].c_str()),
		atoi(updateShoppingItemData[SHOPPING_ITEM_SENT_DAY_7_REMINDER_INDEX].c_str()) == 1);
	return _shoppingItemDatabase.Update(updateShoppingItem);
}

char ShoppingItemService::deleteShoppingItem(string deleteUuid)
{
	return _shoppingItemDatabase.Delete(deleteUuid);
}
