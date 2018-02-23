#include "WirelessSocketService.h"

/*===============PUBLIC==============*/

WirelessSocketService::WirelessSocketService() {}

WirelessSocketService::~WirelessSocketService() {}

void WirelessSocketService::Initialize(string databaseName)
{
	_wirelessSocketDatabase = WirelessSocketDatabase(databaseName);
}

string WirelessSocketService::PerformAction(vector<string> data)
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
		if (data.size() == WIRELESS_SOCKET_DATA_SIZE)
		{
			char error = addWirelessSocket(data);
			if (!error)
			{
				return WIRELESS_SOCKET_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SOCKET_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == WIRELESS_SOCKET_DATA_SIZE)
		{
			char error = updateWirelessSocket(data);
			if (!error)
			{
				return WIRELESS_SOCKET_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SOCKET_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteWirelessSocket(actionParameter);
		if (!error)
		{
			return WIRELESS_SOCKET_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	else if (action == SET)
	{
		if (data.size() == WIRELESS_SOCKET_SET_DATA_SIZE)
		{
			char error = setWirelessSocket(data);
			if (!error)
			{
				return WIRELESS_SOCKET_SET_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return WIRELESS_SOCKET_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void WirelessSocketService::Dispose()
{
	_wirelessSocketDatabase.Dispose();
}

vector<WirelessSocket> WirelessSocketService::GetWirelessSocketList()
{
	return _wirelessSocketDatabase.GetList();
}
/*==============PRIVATE==============*/

string WirelessSocketService::getJsonString()
{
	vector<WirelessSocket> wirelessSocketList = _wirelessSocketDatabase.GetList();

	stringstream data;
	for (int index = 0; index < wirelessSocketList.size(); index++)
	{
		data << wirelessSocketList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char WirelessSocketService::addWirelessSocket(vector<string> newWirelessSocketData)
{
	WirelessSocket newWirelessSocket(
		newWirelessSocketData[WIRELESS_SOCKET_UUID_INDEX].c_str(),
		newWirelessSocketData[WIRELESS_SOCKET_ROOM_UUID_INDEX].c_str(),
		newWirelessSocketData[WIRELESS_SOCKET_NAME_INDEX].c_str(),
		newWirelessSocketData[WIRELESS_SOCKET_CODE_INDEX].c_str(),
		false);
	return _wirelessSocketDatabase.Insert(newWirelessSocket);
}

char WirelessSocketService::updateWirelessSocket(vector<string> updateWirelessSocketData)
{
	WirelessSocket updateWirelessSocket(
		updateWirelessSocketData[WIRELESS_SOCKET_UUID_INDEX].c_str(),
		updateWirelessSocketData[WIRELESS_SOCKET_ROOM_UUID_INDEX].c_str(),
		updateWirelessSocketData[WIRELESS_SOCKET_NAME_INDEX].c_str(),
		updateWirelessSocketData[WIRELESS_SOCKET_CODE_INDEX].c_str(),
		false);
	return _wirelessSocketDatabase.Update(updateWirelessSocket);
}

char WirelessSocketService::deleteWirelessSocket(string deleteUuid)
{
	return _wirelessSocketDatabase.Delete(deleteUuid);
}

char WirelessSocketService::setWirelessSocket(vector<string> setWirelessSocketData)
{
	string uuid = setWirelessSocketData[WIRELESS_SOCKET_UUID_INDEX].c_str();
	bool newState = atoi(setWirelessSocketData[WIRELESS_SOCKET_SET_STATE_INDEX].c_str()) == 1;

	WirelessSocket wirelessSocket = _wirelessSocketDatabase.GetByUuid(uuid);
	if (wirelessSocket.GetCode() == "") {
		return -1;
	}

	bool sendSuccess = PiControl::Send433Mhz(DATA_GPIO, wirelessSocket.GetCode(), newState ? 1 : 0);
	if (!sendSuccess) {
		return -2;
	}

	return _wirelessSocketDatabase.UpdateState(uuid, newState);
}
