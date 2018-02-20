#include "WirelessTimerService.h"

/*===============PUBLIC==============*/

WirelessTimerService::WirelessTimerService() {}

WirelessTimerService::~WirelessTimerService() {}

void WirelessTimerService::Initialize(string databaseName)
{
	_wirelessTimerDatabase = WirelessTimerDatabase(databaseName);
}

string WirelessTimerService::PerformAction(vector<string> data)
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
		if (data.size() == WIRELESS_TIMER_DATA_SIZE)
		{
			char error = addWirelessTimer(data);
			if (!error)
			{
				return WIRELESS_TIMER_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_TIMER_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == WIRELESS_TIMER_DATA_SIZE)
		{
			char error = updateWirelessTimer(data);
			if (!error)
			{
				return WIRELESS_TIMER_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_TIMER_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteWirelessTimer(actionParameter);
		if (!error)
		{
			return WIRELESS_TIMER_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void WirelessTimerService::Dispose()
{
	_wirelessTimerDatabase.Dispose();
}

vector<WirelessTimer> WirelessTimerService::GetWirelessTimerList()
{
	return _wirelessTimerDatabase.GetList();
}
/*==============PRIVATE==============*/

string WirelessTimerService::getJsonString()
{
	vector<WirelessTimer> wirelessTimerList = _wirelessTimerDatabase.GetList();

	stringstream data;
	for (int index = 0; index < wirelessTimerList.size(); index++)
	{
		data << wirelessTimerList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char WirelessTimerService::addWirelessTimer(vector<string> newWirelessTimerData)
{
	WirelessTimer newWirelessTimer(
		newWirelessTimerData[WIRELESS_TIMER_UUID_INDEX].c_str(),
		newWirelessTimerData[WIRELESS_TIMER_NAME_INDEX].c_str(),
		atoi(newWirelessTimerData[WIRELESS_TIMER_WEEKDAY_INDEX].c_str()),
		atoi(newWirelessTimerData[WIRELESS_TIMER_HOUR_INDEX].c_str()),
		atoi(newWirelessTimerData[WIRELESS_TIMER_MINUTE_INDEX].c_str()),
		newWirelessTimerData[WIRELESS_TIMER_GPIO_UUID_INDEX].c_str(),
		atoi(newWirelessTimerData[WIRELESS_TIMER_GPIO_ACTION_INDEX].c_str()) == 1,
		newWirelessTimerData[WIRELESS_TIMER_WIRELESS_SOCKET_UUID_INDEX].c_str(),
		atoi(newWirelessTimerData[WIRELESS_TIMER_WIRELESS_SOCKET_ACTION_INDEX].c_str()) == 1,
		newWirelessTimerData[WIRELESS_TIMER_WIRELESS_SWITCH_UUID_INDEX].c_str());
	return _wirelessTimerDatabase.Insert(_wirelessTimerDatabase.GetList().size(), newWirelessTimer);
}

char WirelessTimerService::updateWirelessTimer(vector<string> updateWirelessTimerData)
{
	WirelessTimer updateWirelessTimer(
		updateWirelessTimerData[WIRELESS_TIMER_UUID_INDEX].c_str(),
		updateWirelessTimerData[WIRELESS_TIMER_NAME_INDEX].c_str(),
		atoi(updateWirelessTimerData[WIRELESS_TIMER_WEEKDAY_INDEX].c_str()),
		atoi(updateWirelessTimerData[WIRELESS_TIMER_HOUR_INDEX].c_str()),
		atoi(updateWirelessTimerData[WIRELESS_TIMER_MINUTE_INDEX].c_str()),
		updateWirelessTimerData[WIRELESS_TIMER_GPIO_UUID_INDEX].c_str(),
		atoi(updateWirelessTimerData[WIRELESS_TIMER_GPIO_ACTION_INDEX].c_str()) == 1,
		updateWirelessTimerData[WIRELESS_TIMER_WIRELESS_SOCKET_UUID_INDEX].c_str(),
		atoi(updateWirelessTimerData[WIRELESS_TIMER_WIRELESS_SOCKET_ACTION_INDEX].c_str()) == 1,
		updateWirelessTimerData[WIRELESS_TIMER_WIRELESS_SWITCH_UUID_INDEX].c_str());
	return _wirelessTimerDatabase.Update(updateWirelessTimer);
}

char WirelessTimerService::deleteWirelessTimer(string deleteUuid)
{
	return _wirelessTimerDatabase.Delete(deleteUuid);
}
