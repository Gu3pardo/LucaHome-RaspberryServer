#include "WirelessScheduleService.h"

/*===============PUBLIC==============*/

WirelessScheduleService::WirelessScheduleService() {}

WirelessScheduleService::~WirelessScheduleService() {}

void WirelessScheduleService::Initialize(string databaseName)
{
	_wirelessScheduleDatabase = WirelessScheduleDatabase(databaseName);
}

string WirelessScheduleService::PerformAction(vector<string> data)
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
		if (data.size() == WIRELESS_SCHEDULE_DATA_SIZE)
		{
			char error = addWirelessSchedule(data);
			if (!error)
			{
				return WIRELESS_SCHEDULE_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SCHEDULE_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == WIRELESS_SCHEDULE_DATA_SIZE)
		{
			char error = updateWirelessSchedule(data);
			if (!error)
			{
				return WIRELESS_SCHEDULE_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SCHEDULE_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteWirelessSchedule(actionParameter);
		if (!error)
		{
			return WIRELESS_SCHEDULE_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	else if (action == SET)
	{
		if (data.size() == WIRELESS_SCHEDULE_SET_DATA_SIZE)
		{
			char error = setWirelessSchedule(data);
			if (!error)
			{
				return WIRELESS_SCHEDULE_SET_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SCHEDULE_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void WirelessScheduleService::Dispose()
{
	_wirelessScheduleDatabase.Dispose();
}

vector<WirelessSchedule> WirelessScheduleService::GetWirelessScheduleList()
{
	return _wirelessScheduleDatabase.GetList();
}
/*==============PRIVATE==============*/

string WirelessScheduleService::getJsonString()
{
	vector<WirelessSchedule> wirelessScheduleList = _wirelessScheduleDatabase.GetList();

	stringstream data;
	for (int index = 0; index < wirelessScheduleList.size(); index++)
	{
		data << wirelessScheduleList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char WirelessScheduleService::addWirelessSchedule(vector<string> newWirelessScheduleData)
{
	WirelessSchedule newWirelessSchedule(
		newWirelessScheduleData[WIRELESS_SCHEDULE_UUID_INDEX].c_str(),
		newWirelessScheduleData[WIRELESS_SCHEDULE_NAME_INDEX].c_str(),
		atoi(newWirelessScheduleData[WIRELESS_SCHEDULE_WEEKDAY_INDEX].c_str()),
		atoi(newWirelessScheduleData[WIRELESS_SCHEDULE_HOUR_INDEX].c_str()),
		atoi(newWirelessScheduleData[WIRELESS_SCHEDULE_MINUTE_INDEX].c_str()),
		atoi(newWirelessScheduleData[WIRELESS_SCHEDULE_IS_ACTIVE_INDEX].c_str()) == 1,
		newWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SOCKET_UUID_INDEX].c_str(),
		atoi(newWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SOCKET_ACTION_INDEX].c_str()) == 1,
		newWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SWITCH_UUID_INDEX].c_str());
	return _wirelessScheduleDatabase.Insert(_wirelessScheduleDatabase.GetList().size(), newWirelessSchedule);
}

char WirelessScheduleService::updateWirelessSchedule(vector<string> updateWirelessScheduleData)
{
	WirelessSchedule updateWirelessSchedule(
		updateWirelessScheduleData[WIRELESS_SCHEDULE_UUID_INDEX].c_str(),
		updateWirelessScheduleData[WIRELESS_SCHEDULE_NAME_INDEX].c_str(),
		atoi(updateWirelessScheduleData[WIRELESS_SCHEDULE_WEEKDAY_INDEX].c_str()),
		atoi(updateWirelessScheduleData[WIRELESS_SCHEDULE_HOUR_INDEX].c_str()),
		atoi(updateWirelessScheduleData[WIRELESS_SCHEDULE_MINUTE_INDEX].c_str()),
		atoi(updateWirelessScheduleData[WIRELESS_SCHEDULE_IS_ACTIVE_INDEX].c_str()) == 1,
		updateWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SOCKET_UUID_INDEX].c_str(),
		atoi(updateWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SOCKET_ACTION_INDEX].c_str()) == 1,
		updateWirelessScheduleData[WIRELESS_SCHEDULE_WIRELESS_SWITCH_UUID_INDEX].c_str());
	return _wirelessScheduleDatabase.Update(updateWirelessSchedule);
}

char WirelessScheduleService::deleteWirelessSchedule(string deleteUuid)
{
	return _wirelessScheduleDatabase.Delete(deleteUuid);
}

char WirelessScheduleService::setWirelessSchedule(vector<string> setWirelessScheduleData)
{
	string uuid = setWirelessScheduleData[WIRELESS_SCHEDULE_UUID_INDEX].c_str();
	bool newState = atoi(setWirelessScheduleData[WIRELESS_SCHEDULE_SET_STATE_INDEX].c_str());
	return _wirelessScheduleDatabase.UpdateState(uuid, newState);
}
