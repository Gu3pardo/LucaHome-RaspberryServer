#include "RadioStreamService.h"

/*===============PUBLIC==============*/

RadioStreamService::RadioStreamService() {}

RadioStreamService::~RadioStreamService() {}

void RadioStreamService::Initialize(string databaseName)
{
	_radioStreamDatabase = RadioStreamDatabase(databaseName);
}

string RadioStreamService::PerformAction(vector<string> data)
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
		if (data.size() == RADIO_STREAM_DATA_SIZE)
		{
			char error = addRadioStream(data);
			if (!error)
			{
				return RADIO_STREAM_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"RadioStream\",\"Error\":235,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return RADIO_STREAM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == RADIO_STREAM_DATA_SIZE)
		{
			char error = updateRadioStream(data);
			if (!error)
			{
				return RADIO_STREAM_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"RadioStream\",\"Error\":235,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return RADIO_STREAM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteRadioStream(actionParameter);
		if (!error)
		{
			return RADIO_STREAM_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "{\"Category\":\"RadioStream\",\"Error\":235,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void RadioStreamService::Dispose()
{
	_radioStreamDatabase.Dispose();
}

/*==============PRIVATE==============*/

string RadioStreamService::getJsonString()
{
	vector<RadioStream> radioStreamList = _radioStreamDatabase.GetList();

	stringstream data;
	for (int index = 0; index < radioStreamList.size(); index++)
	{
		data << radioStreamList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"RadioStream\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char RadioStreamService::addRadioStream(vector<string> newRadioStreamData)
{
	RadioStream newRadioStream(
		newRadioStreamData[RADIO_STREAM_UUID_INDEX].c_str(),
		newRadioStreamData[RADIO_STREAM_TITLE_INDEX].c_str(),
		newRadioStreamData[RADIO_STREAM_URL_INDEX].c_str(),
		atoi(newRadioStreamData[RADIO_STREAM_PLAY_COUNT_INDEX].c_str()));
	return _radioStreamDatabase.Insert(newRadioStream);
}

char RadioStreamService::updateRadioStream(vector<string> updateRadioStreamData)
{
	RadioStream updateRadioStream(
		updateRadioStreamData[RADIO_STREAM_UUID_INDEX].c_str(),
		updateRadioStreamData[RADIO_STREAM_TITLE_INDEX].c_str(),
		updateRadioStreamData[RADIO_STREAM_URL_INDEX].c_str(),
		atoi(updateRadioStreamData[RADIO_STREAM_PLAY_COUNT_INDEX].c_str()));
	return _radioStreamDatabase.Update(updateRadioStream);
}

char RadioStreamService::deleteRadioStream(string deleteUuid)
{
	return _radioStreamDatabase.Delete(deleteUuid);
}
