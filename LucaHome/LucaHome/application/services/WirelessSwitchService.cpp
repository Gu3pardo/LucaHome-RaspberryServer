#include "WirelessSwitchService.h"

/*===============PUBLIC==============*/

WirelessSwitchService::WirelessSwitchService() {}

WirelessSwitchService::~WirelessSwitchService() {}

void WirelessSwitchService::Initialize(string databaseName)
{
	_wirelessSwitchDatabase = WirelessSwitchDatabase(databaseName);
}

string WirelessSwitchService::PerformAction(vector<string> data)
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
		if (data.size() == WIRELESS_SWITCH_DATA_SIZE)
		{
			char error = addWirelessSwitch(data);
			if (!error)
			{
				return WIRELESS_SWITCH_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SWITCH_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == WIRELESS_SWITCH_DATA_SIZE)
		{
			char error = updateWirelessSwitch(data);
			if (!error)
			{
				return WIRELESS_SWITCH_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SWITCH_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteWirelessSwitch(actionParameter);
		if (!error)
		{
			return WIRELESS_SWITCH_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	else if (action == TOGGLE)
	{
		if (data.size() == WIRELESS_SWITCH_TOGGLE_DATA_SIZE)
		{
			char error = toggleWirelessSwitch(data);
			if (!error)
			{
				return WIRELESS_SWITCH_TOGGLE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SWITCH_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void WirelessSwitchService::Dispose()
{
	_wirelessSwitchDatabase.Dispose();
}

vector<WirelessSwitch> WirelessSwitchService::GetWirelessSwitchList()
{
	return _wirelessSwitchDatabase.GetList();
}
/*==============PRIVATE==============*/

string WirelessSwitchService::getJsonString()
{
	vector<WirelessSwitch> wirelessSwitchList = _wirelessSwitchDatabase.GetList();

	stringstream data;
	for (int index = 0; index < wirelessSwitchList.size(); index++)
	{
		data << wirelessSwitchList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char WirelessSwitchService::addWirelessSwitch(vector<string> newWirelessSwitchData)
{
	WirelessSwitch newWirelessSwitch(
		newWirelessSwitchData[WIRELESS_SWITCH_UUID_INDEX].c_str(),
		newWirelessSwitchData[WIRELESS_SWITCH_ROOM_UUID_INDEX].c_str(),
		newWirelessSwitchData[WIRELESS_SWITCH_NAME_INDEX].c_str(),
		atoi(newWirelessSwitchData[WIRELESS_SWITCH_REMOTE_ID_INDEX].c_str()),
		Tools::ConvertStrToUnsignedChar(newWirelessSwitchData[WIRELESS_SWITCH_KEY_CODE_INDEX].c_str()),
		atoi(newWirelessSwitchData[WIRELESS_SWITCH_ACTION_INDEX].c_str()) == 1);
	return _wirelessSwitchDatabase.Insert(newWirelessSwitch);
}

char WirelessSwitchService::updateWirelessSwitch(vector<string> updateWirelessSwitchData)
{
	WirelessSwitch updateWirelessSwitch(
		updateWirelessSwitchData[WIRELESS_SWITCH_UUID_INDEX].c_str(),
		updateWirelessSwitchData[WIRELESS_SWITCH_ROOM_UUID_INDEX].c_str(),
		updateWirelessSwitchData[WIRELESS_SWITCH_NAME_INDEX].c_str(),
		atoi(updateWirelessSwitchData[WIRELESS_SWITCH_REMOTE_ID_INDEX].c_str()),
		Tools::ConvertStrToUnsignedChar(updateWirelessSwitchData[WIRELESS_SWITCH_KEY_CODE_INDEX].c_str()),
		atoi(updateWirelessSwitchData[WIRELESS_SWITCH_ACTION_INDEX].c_str()) == 1);
	return _wirelessSwitchDatabase.Update(updateWirelessSwitch);
}

char WirelessSwitchService::deleteWirelessSwitch(string deleteUuid)
{
	return _wirelessSwitchDatabase.Delete(deleteUuid);
}

char WirelessSwitchService::toggleWirelessSwitch(vector<string> toggleWirelessSwitchData)
{
	string uuid = toggleWirelessSwitchData[WIRELESS_SWITCH_UUID_INDEX].c_str();

	WirelessSwitch wirelessSwitch = _wirelessSwitchDatabase.GetByUuid(uuid);
	if (wirelessSwitch.GetKeyCode() == 0) {
		return -1;
	}

	bool sendSuccess = PiControl::SendButton(wirelessSwitch.GetRemoteId(), wirelessSwitch.GetKeyCode(), DATA_GPIO, !wirelessSwitch.GetAction());
	if (!sendSuccess) {
		return -2;
	}

	return _wirelessSwitchDatabase.UpdateAction(uuid, !wirelessSwitch.GetAction());
}
