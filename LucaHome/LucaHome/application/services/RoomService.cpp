#include "RoomService.h"

/*===============PUBLIC==============*/

RoomService::RoomService() {}

RoomService::~RoomService() {}

void RoomService::Initialize(string databaseName)
{
	_roomDatabase = RoomDatabase(databaseName);
}

string RoomService::PerformAction(vector<string> data)
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
		if (data.size() == ROOM_DATA_SIZE)
		{
			char error = addRoom(data);
			if (!error)
			{
				return ROOM_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Room\",\"Error\":205,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return ROOM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == ROOM_DATA_SIZE)
		{
			char error = updateRoom(data);
			if (!error)
			{
				return ROOM_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Room\",\"Error\":205,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return ROOM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteRoom(actionParameter);
		if (!error)
		{
			return ROOM_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "{\"Category\":\"Room\",\"Error\":205,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void RoomService::Dispose()
{
	_roomDatabase.Dispose();
}

/*==============PRIVATE==============*/

string RoomService::getJsonString()
{
	vector<Room> RoomList = _roomDatabase.GetList();

	stringstream data;
	for (int index = 0; index < RoomList.size(); index++)
	{
		data << RoomList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"Room\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char RoomService::addRoom(vector<string> newRoomData)
{
	Room newRoom(
		newRoomData[ROOM_UUID_INDEX].c_str(),
		newRoomData[ROOM_NAME_INDEX].c_str(),
		atoi(newRoomData[ROOM_TYPE_INDEX].c_str()));
	return _roomDatabase.Insert(newRoom);
}

char RoomService::updateRoom(vector<string> updateRoomData)
{
	Room updateRoom(
		updateRoomData[ROOM_UUID_INDEX].c_str(),
		updateRoomData[ROOM_NAME_INDEX].c_str(),
		atoi(updateRoomData[ROOM_TYPE_INDEX].c_str()));
	return _roomDatabase.Update(updateRoom);
}

char RoomService::deleteRoom(string deleteUuid)
{
	return _roomDatabase.Delete(deleteUuid);
}
