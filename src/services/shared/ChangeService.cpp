#include "ChangeService.h"

/*===============PUBLIC==============*/

ChangeService::ChangeService()
{
}

ChangeService::~ChangeService()
{
}

void ChangeService::Initialize(FileController fileController, std::string changeFile)
{
	_fileController = fileController;
	_changeFile = changeFile;
	LoadData();
}

void ChangeService::UpdateChange(std::string type, std::string user)
{
	time_t now;
	struct tm now_info;

	now = time(0);
	localtime_r(&now, &now_info);

	for (int index = 0; index < _changeList.size(); index++)
	{
		ChangeDto change = _changeList[index];

		if (change.GetType() == type)
		{
			change.SetHour(now_info.tm_hour);
			change.SetMinute(now_info.tm_min);
			change.SetDay(now_info.tm_mday);
			change.SetMonth(now_info.tm_mon + 1);
			change.SetYear(now_info.tm_year + 1900);
			change.SetUserName(user);
			break;
		}
	}

	std::string xmldata = _xmlService.GenerateChangesXml(_changeList);
	_fileController.SaveFile(_changeFile, xmldata);
}

void ChangeService::LoadData()
{
	std::string changeFileContent = _fileController.ReadFile(_changeFile);
	_changeList = _xmlService.GetChangeList(changeFileContent);
}

std::string ChangeService::PerformAction(std::vector<std::string> data)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL) {
			return getJsonString();
		}
		else if (actionParameter == PHP) {
			return getPhpString();
		}
		return  CHANGE_ERROR_NR_101;
	}

	return CHANGE_ERROR_NR_100;
}

/*==============PRIVATE==============*/

std::string ChangeService::getJsonString()
{
	std::stringstream out;
	out << "\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _changeList.size(); index++)
	{
		ChangeDto change = _changeList[index];
		data << change.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]" << "\x00" << std::endl;

	return out.str();
}

std::string ChangeService::getPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _changeList.size(); index++)
	{
		out << _changeList[index].PhpString();
	}

	out << "\x00" << std::endl;

	return out.str();
}
