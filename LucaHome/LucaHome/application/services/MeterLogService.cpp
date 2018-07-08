#include "MeterLogService.h"

/*===============PUBLIC==============*/

MeterLogService::MeterLogService() {}

MeterLogService::~MeterLogService() {}

void MeterLogService::Initialize(string databaseName)
{
	_meterLogItemDatabase = MeterLogItemDatabase(databaseName);
}

string MeterLogService::PerformAction(vector<string> data)
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
		if (data.size() == METER_LOG_ITEM_DATA_SIZE)
		{
			char error = addMeterLogItem(data);
			if (!error)
			{
				return METER_LOG_ITEM_ADD_SUCCESS;
			}
			return METER_LOG_ITEM_ERROR_ADD;
		}
		return METER_LOG_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == METER_LOG_ITEM_DATA_SIZE)
		{
			char error = updateMeterLogItem(data);
			if (!error)
			{
				return METER_LOG_ITEM_UPDATE_SUCCESS;
			}
			return METER_LOG_ITEM_ERROR_UPDATE;
		}
		return METER_LOG_ITEM_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteMeterLogItem(actionParameter);
		if (!error)
		{
			return METER_LOG_ITEM_DELETE_SUCCESS;
		}
		return METER_LOG_ITEM_ERROR_DELETE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void MeterLogService::Dispose()
{
	_meterLogItemDatabase.Dispose();
}

/*==============PRIVATE==============*/

string MeterLogService::getJsonString()
{
	vector<MeterLogItem> meterLogItemList = _meterLogItemDatabase.GetList();

	stringstream data;
	for (int index = 0; index < meterLogItemList.size(); index++)
	{
		data << meterLogItemList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"MeterLogItem\","
		<< "\"Action\":\"Get\","
		<< "\"Error\":0,"
		<< "\"Success\":true,"
		<< "\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char MeterLogService::addMeterLogItem(vector<string> newMeterLogItemData)
{
	MeterLogItem newMeterLogItem(
		newMeterLogItemData[METER_LOG_ITEM_UUID_INDEX].c_str(),
		newMeterLogItemData[METER_LOG_ITEM_ROOM_UUID_INDEX].c_str(),
		newMeterLogItemData[METER_LOG_ITEM_TYPE_UUID_INDEX].c_str(),
		newMeterLogItemData[METER_LOG_ITEM_TYPE_INDEX].c_str(),
		newMeterLogItemData[METER_LOG_ITEM_METER_ID_INDEX].c_str(),
		Tools::ConvertStrToDouble(newMeterLogItemData[METER_LOG_ITEM_VALUE_INDEX].c_str()) == 1,
		newMeterLogItemData[METER_LOG_ITEM_IMAGE_NAME_INDEX].c_str(),
		atoi(newMeterLogItemData[METER_LOG_ITEM_SAVE_DATE_TIME_INDEX].c_str()));
	return _meterLogItemDatabase.Insert(newMeterLogItem);
}

char MeterLogService::updateMeterLogItem(vector<string> updateMeterLogItemData)
{
	MeterLogItem updateMeterLogItem(
		updateMeterLogItemData[METER_LOG_ITEM_UUID_INDEX].c_str(),
		updateMeterLogItemData[METER_LOG_ITEM_ROOM_UUID_INDEX].c_str(),
		updateMeterLogItemData[METER_LOG_ITEM_TYPE_UUID_INDEX].c_str(),
		updateMeterLogItemData[METER_LOG_ITEM_TYPE_INDEX].c_str(),
		updateMeterLogItemData[METER_LOG_ITEM_METER_ID_INDEX].c_str(),
		Tools::ConvertStrToDouble(updateMeterLogItemData[METER_LOG_ITEM_VALUE_INDEX].c_str()) == 1,
		updateMeterLogItemData[METER_LOG_ITEM_IMAGE_NAME_INDEX].c_str(),
		atoi(updateMeterLogItemData[METER_LOG_ITEM_SAVE_DATE_TIME_INDEX].c_str()));
	return _meterLogItemDatabase.Update(updateMeterLogItem);
}

char MeterLogService::deleteMeterLogItem(string deleteUuid)
{
	return _meterLogItemDatabase.Delete(deleteUuid);
}
