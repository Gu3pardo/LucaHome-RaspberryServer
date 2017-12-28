#include "MoneyMeterDataService.h"

/*===============PUBLIC==============*/

MoneyMeterDataService::MoneyMeterDataService()
{
}

MoneyMeterDataService::~MoneyMeterDataService()
{
}

void MoneyMeterDataService::Initialize(FileController fileController, std::string moneyMeterDataFile)
{
	_fileController = fileController;
	_moneyMeterDataFile = moneyMeterDataFile;
	LoadData();
}

void MoneyMeterDataService::LoadData()
{
	std::string moneyMeterDataFileContent = _fileController.ReadFile(_moneyMeterDataFile);
	_moneyMeterDataList = _xmlService.GetMoneyMeterDataList(moneyMeterDataFileContent);
}

std::string MoneyMeterDataService::PerformAction(std::vector<std::string> data, AuthentificationService authentificationService, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL) {
			if (!authentificationService.IsUserAdmin(username)) {
				return MONEY_METER_DATA_ERROR_NR_218;
			}

			return getJsonString();
		}
		else if (actionParameter == USER) {
			return getJsonStringUser(username);
		}
	}

	else if (action == ADD)
	{
		if (data.size() == MONEY_METER_DATA_SIZE)
		{
			if (addMoneyMeterData(data, changeService, username))
			{
				return MONEY_METER_DATA_ADD_SUCCESS;
			}
			return MONEY_METER_DATA_ERROR_NR_211;
		}
		return MONEY_METER_DATA_ERROR_NR_210;
	}

	else if (action == UPDATE)
	{
		if (data.size() == MONEY_METER_DATA_SIZE)
		{
			if (updateMoneyMeterData(data, changeService, username))
			{
				return MONEY_METER_DATA_UPDATE_SUCCESS;
			}
			return MONEY_METER_DATA_ERROR_NR_212;
		}
		return MONEY_METER_DATA_ERROR_NR_210;
	}

	else if (action == DELETE)
	{
		if (deleteMoneyMeterData(atoi(data[MONEY_METER_DATA_ID_INDEX].c_str()), changeService, username))
		{
			return MONEY_METER_DATA_DELETE_SUCCESS;
		}
		return MONEY_METER_DATA_ERROR_NR_213;
	}

	return MONEY_METER_DATA_ERROR_NR_214;
}

/*==============PRIVATE==============*/

void MoneyMeterDataService::saveMoneyMeterData(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateMoneyMeterDataXml(_moneyMeterDataList);
	_fileController.SaveFile(_moneyMeterDataFile, xmldata);

	changeService.UpdateChange("MoneyMeterData", username);
}

std::string MoneyMeterDataService::getJsonString()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _moneyMeterDataList.size(); index++)
	{
		data << _moneyMeterDataList[index].JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

std::string MoneyMeterDataService::getJsonStringUser(std::string username)
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _moneyMeterDataList.size(); index++)
	{
		MoneyMeterDataDto moneyMeterData = _moneyMeterDataList[index];

		if (moneyMeterData.GetUser() == username)
		{
			data << moneyMeterData.JsonString() << ",";
		}
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

bool MoneyMeterDataService::addMoneyMeterData(std::vector<std::string> newMoneyMeterDataData, ChangeService changeService, std::string username)
{
	MoneyMeterDataDto newMoneyMeterData(
		atoi(newMoneyMeterDataData[MONEY_METER_DATA_ID_INDEX].c_str()),
		newMoneyMeterDataData[MONEY_METER_DATA_BANK_INDEX],
		newMoneyMeterDataData[MONEY_METER_DATA_PLAN_INDEX],
		Tools::ConvertStrToDouble(newMoneyMeterDataData[MONEY_METER_DATA_AMOUNT_INDEX].c_str()),
		newMoneyMeterDataData[MONEY_METER_DATA_UNIT_INDEX],
		atoi(newMoneyMeterDataData[MONEY_METER_DATA_DAY_INDEX].c_str()),
		atoi(newMoneyMeterDataData[MONEY_METER_DATA_MONTH_INDEX].c_str()),
		atoi(newMoneyMeterDataData[MONEY_METER_DATA_YEAR_INDEX].c_str()),
		newMoneyMeterDataData[MONEY_METER_DATA_USER_INDEX]);

	_moneyMeterDataList.push_back(newMoneyMeterData);

	saveMoneyMeterData(changeService, username);
	LoadData();

	return true;
}

bool MoneyMeterDataService::updateMoneyMeterData(std::vector<std::string> updateMoneyMeterDataData, ChangeService changeService, std::string username)
{
	int updateMoneyMeterDataId = atoi(updateMoneyMeterDataData[MONEY_METER_DATA_ID_INDEX].c_str());

	for (int index = 0; index < _moneyMeterDataList.size(); index++)
	{
		if (_moneyMeterDataList[index].GetId() == updateMoneyMeterDataId)
		{
			_moneyMeterDataList[index].SetBank(updateMoneyMeterDataData[MONEY_METER_DATA_BANK_INDEX]);
			_moneyMeterDataList[index].SetPlan(updateMoneyMeterDataData[MONEY_METER_DATA_PLAN_INDEX]);

			_moneyMeterDataList[index].SetAmount(Tools::ConvertStrToDouble(updateMoneyMeterDataData[MONEY_METER_DATA_AMOUNT_INDEX].c_str()));
			_moneyMeterDataList[index].SetUnit(updateMoneyMeterDataData[MONEY_METER_DATA_UNIT_INDEX]);

			_moneyMeterDataList[index].SetDay(atoi(updateMoneyMeterDataData[MONEY_METER_DATA_DAY_INDEX].c_str()));
			_moneyMeterDataList[index].SetMonth(atoi(updateMoneyMeterDataData[MONEY_METER_DATA_MONTH_INDEX].c_str()));
			_moneyMeterDataList[index].SetYear(atoi(updateMoneyMeterDataData[MONEY_METER_DATA_YEAR_INDEX].c_str()));

			_moneyMeterDataList[index].SetUser(updateMoneyMeterDataData[MONEY_METER_DATA_USER_INDEX]);

			saveMoneyMeterData(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool MoneyMeterDataService::deleteMoneyMeterData(int id, ChangeService changeService, std::string username)
{
	std::vector<MoneyMeterDataDto>::iterator it = _moneyMeterDataList.begin();

	while (it != _moneyMeterDataList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _moneyMeterDataList.erase(it);

			saveMoneyMeterData(changeService, username);
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
