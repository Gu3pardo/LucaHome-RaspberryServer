#include "MeterDataService.h"

/*===============PUBLIC==============*/

MeterDataService::MeterDataService()
{
}

MeterDataService::~MeterDataService()
{
}

void MeterDataService::Initialize(FileController fileController, std::string meterDataFile)
{
	_fileController = fileController;
	_meterDataFile = meterDataFile;
	LoadData();
}

void MeterDataService::LoadData()
{
	std::string meterDataFileContent = _fileController.ReadFile(_meterDataFile);
	_meterDataList = _xmlService.GetMeterDataList(meterDataFileContent);
}

std::string MeterDataService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			return getJsonString();
		}
		else if (actionParameter == PHP)
		{
			return getPhpString();
		}
		return METER_DATA_ERROR_NR_196;
	}

	else if (action == ADD)
	{
		if (data.size() == METER_DATA_SIZE)
		{
			if (addMeterData(data, changeService, username))
			{
				return METER_DATA_ADD_SUCCESS;
			}
			return METER_DATA_ERROR_NR_191;
		}
		return METER_DATA_ERROR_NR_190;
	}

	else if (action == UPDATE)
	{
		if (data.size() == METER_DATA_SIZE)
		{
			if (updateMeterData(data, changeService, username))
			{
				return METER_DATA_UPDATE_SUCCESS;
			}
			return METER_DATA_ERROR_NR_192;
		}
		return METER_DATA_ERROR_NR_190;
	}

	else if (action == DELETE)
	{
		if (deleteMeterData(atoi(data[METER_DATA_ID_INDEX].c_str()), changeService, username))
		{
			return METER_DATA_DELETE_SUCCESS;
		}
		return METER_DATA_ERROR_NR_193;
	}

	return METER_DATA_ERROR_NR_194;
}

/*==============PRIVATE==============*/

void MeterDataService::saveMeterData(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateMeterDataXml(_meterDataList);
	_fileController.SaveFile(_meterDataFile, xmldata);

	changeService.UpdateChange("MeterData", username);
}

std::string MeterDataService::getJsonString()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _meterDataList.size(); index++)
	{
		data << _meterDataList[index].JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

std::string MeterDataService::getPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _meterDataList.size(); index++)
	{
		out << _meterDataList[index].PhpString();
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MeterDataService::addMeterData(std::vector<std::string> newMeterDataData, ChangeService changeService, std::string username)
{
	MeterDataDto newMeterData(
		atoi(newMeterDataData[METER_DATA_ID_INDEX].c_str()),
		newMeterDataData[METER_DATA_TYPE_INDEX],
		atoi(newMeterDataData[METER_DATA_TYPE_ID_INDEX].c_str()),
		atoi(newMeterDataData[METER_DATA_DAY_INDEX].c_str()),
		atoi(newMeterDataData[METER_DATA_MONTH_INDEX].c_str()),
		atoi(newMeterDataData[METER_DATA_YEAR_INDEX].c_str()),
		atoi(newMeterDataData[METER_DATA_HOUR_INDEX].c_str()),
		atoi(newMeterDataData[METER_DATA_MINUTE_INDEX].c_str()),
		newMeterDataData[METER_DATA_METER_ID_INDEX],
		newMeterDataData[METER_DATA_AREA_INDEX],
		Tools::ConvertStrToDouble(newMeterDataData[METER_DATA_VALUE_INDEX].c_str()),
		newMeterDataData[METER_DATA_IMAGE_NAME_INDEX]);

	_meterDataList.push_back(newMeterData);

	saveMeterData(changeService, username);
	LoadData();

	return true;
}

bool MeterDataService::updateMeterData(std::vector<std::string> updateMeterDataData, ChangeService changeService, std::string username)
{
	int updateMeterDataId = atoi(updateMeterDataData[METER_DATA_ID_INDEX].c_str());

	for (int index = 0; index < _meterDataList.size(); index++)
	{
		if (_meterDataList[index].GetId() == updateMeterDataId)
		{
			_meterDataList[index].SetType(updateMeterDataData[METER_DATA_TYPE_INDEX]);

			_meterDataList[index].SetDay(atoi(updateMeterDataData[METER_DATA_DAY_INDEX].c_str()));
			_meterDataList[index].SetMonth(atoi(updateMeterDataData[METER_DATA_MONTH_INDEX].c_str()));
			_meterDataList[index].SetYear(atoi(updateMeterDataData[METER_DATA_YEAR_INDEX].c_str()));

			_meterDataList[index].SetHour(atoi(updateMeterDataData[METER_DATA_HOUR_INDEX].c_str()));
			_meterDataList[index].SetMinute(atoi(updateMeterDataData[METER_DATA_MINUTE_INDEX].c_str()));

			_meterDataList[index].SetMeterId(updateMeterDataData[METER_DATA_METER_ID_INDEX]);
			_meterDataList[index].SetArea(updateMeterDataData[METER_DATA_AREA_INDEX]);

			_meterDataList[index].SetValue(Tools::ConvertStrToDouble(updateMeterDataData[METER_DATA_VALUE_INDEX].c_str()));

			_meterDataList[index].SetImageName(updateMeterDataData[METER_DATA_IMAGE_NAME_INDEX]);

			saveMeterData(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool MeterDataService::deleteMeterData(int id, ChangeService changeService, std::string username)
{
	std::vector<MeterDataDto>::iterator it = _meterDataList.begin();

	while (it != _meterDataList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _meterDataList.erase(it);

			saveMeterData(changeService, username);
			LoadData();

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}
