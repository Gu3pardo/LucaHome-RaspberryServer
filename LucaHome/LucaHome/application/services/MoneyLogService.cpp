#include "MoneyLogService.h"

/*===============PUBLIC==============*/

MoneyLogService::MoneyLogService() {}

MoneyLogService::~MoneyLogService() {}

void MoneyLogService::Initialize(string databaseName)
{
	_moneyLogItemDatabase = MoneyLogItemDatabase(databaseName);
}

string MoneyLogService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			return getAllJsonString();
		}
		else if (actionParameter == FOR_USER)
		{
			return getUserJsonString(data[MONEY_LOG_ITEM_GET_USER_UUID_INDEX].c_str());
		}
		return COMMAND_ERROR_NO_ACTION;
	}

	else if (action == ADD)
	{
		if (data.size() == MONEY_LOG_ITEM_DATA_SIZE)
		{
			char error = addMoneyLogItem(data);
			if (!error)
			{
				return MONEY_LOG_ITEM_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MONEY_LOG_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MONEY_LOG_ITEM_DATA_SIZE)
		{
			char error = updateMoneyLogItem(data);
			if (!error)
			{
				return MONEY_LOG_ITEM_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return MONEY_LOG_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteMoneyLogItem(actionParameter);
		if (!error)
		{
			return MONEY_LOG_ITEM_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MoneyLogService::Dispose()
{
	_moneyLogItemDatabase.Dispose();
}

/*==============PRIVATE==============*/

string MoneyLogService::getAllJsonString()
{
	vector<MoneyLogItem> moneyLogItemList = _moneyLogItemDatabase.GetList();

	stringstream data;
	for (int index = 0; index < moneyLogItemList.size(); index++)
	{
		data << moneyLogItemList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

string MoneyLogService::getUserJsonString(string userUuid)
{
	vector<MoneyLogItem> moneyLogItemList = _moneyLogItemDatabase.GetUserList(userUuid);

	stringstream data;
	for (int index = 0; index < moneyLogItemList.size(); index++)
	{
		data << moneyLogItemList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char MoneyLogService::addMoneyLogItem(vector<string> newMoneyLogItemData)
{
	MoneyLogItem newMoneyLogItem(
		newMoneyLogItemData[MONEY_LOG_ITEM_UUID_INDEX].c_str(),
		newMoneyLogItemData[MONEY_LOG_ITEM_TYPE_UUID_INDEX].c_str(),
		newMoneyLogItemData[MONEY_LOG_ITEM_BANK_INDEX].c_str(),
		newMoneyLogItemData[MONEY_LOG_ITEM_PLAN_INDEX].c_str(),
		Tools::ConvertStrToDouble(newMoneyLogItemData[MONEY_LOG_ITEM_AMOUNT_INDEX].c_str()) == 1,
		newMoneyLogItemData[MONEY_LOG_ITEM_UNIT_INDEX].c_str(),
		newMoneyLogItemData[MONEY_LOG_ITEM_USER_UUID_INDEX].c_str(),
		atoi(newMoneyLogItemData[METER_LOG_ITEM_SAVE_DATE_INDEX].c_str()));
	return _moneyLogItemDatabase.Insert(_moneyLogItemDatabase.GetList().size(), newMoneyLogItem);
}

char MoneyLogService::updateMoneyLogItem(vector<string> updateMoneyLogItemData)
{
	MoneyLogItem updateMoneyLogItem(
		updateMoneyLogItemData[MONEY_LOG_ITEM_UUID_INDEX].c_str(),
		updateMoneyLogItemData[MONEY_LOG_ITEM_TYPE_UUID_INDEX].c_str(),
		updateMoneyLogItemData[MONEY_LOG_ITEM_BANK_INDEX].c_str(),
		updateMoneyLogItemData[MONEY_LOG_ITEM_PLAN_INDEX].c_str(),
		Tools::ConvertStrToDouble(updateMoneyLogItemData[MONEY_LOG_ITEM_AMOUNT_INDEX].c_str()) == 1,
		updateMoneyLogItemData[MONEY_LOG_ITEM_UNIT_INDEX].c_str(),
		updateMoneyLogItemData[MONEY_LOG_ITEM_USER_UUID_INDEX].c_str(),
		atoi(newMoneyLogItemData[METER_LOG_ITEM_SAVE_DATE_INDEX].c_str()));
	return _moneyLogItemDatabase.Update(updateMoneyLogItem);
}

char MoneyLogService::deleteMoneyLogItem(string deleteUuid)
{
	return _moneyLogItemDatabase.Delete(deleteUuid);
}
