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

	ReloadData();
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
			change.SetUser(user);
			break;
		}
	}

	std::string xmldata = _xmlService.GenerateChangesXml(_changeList);
	_fileController.SaveFile(_changeFile, xmldata);
}

void ChangeService::ReloadData()
{
	std::string changeFileContent = _fileController.ReadFile(_changeFile);
	_changeList = _xmlService.GetChangeList(changeFileContent);
}

std::string ChangeService::PerformAction(std::string action, std::vector<std::string> data)
{
	if (action == GET)
	{
		if (data.size() == CHANGE_DATA_SIZE)
		{
			if (data[4] == REST)
			{
				return getRestString();
			}
			else if (data[4] == REDUCED)
			{
				return getString();
			}
			else
			{
				return "Error 102:Wrong action parameter for change";
			}
		}
		else
		{
			return "Error 101:Wrong data size for change";
		}
	}
	else
	{
		return "Error 100:Action not found for change";
	}
}

/*==============PRIVATE==============*/

std::string ChangeService::getRestString()
{
	std::stringstream out;

	for (int index = 0; index < _changeList.size(); index++)
	{
		ChangeDto change = _changeList[index];

		out << "{change:"
			<< "{Type:" << change.GetType() << "};"
			<< "{Hour:" << Tools::ConvertIntToStr(change.GetHour()) << "};"
			<< "{Minute:" << Tools::ConvertIntToStr(change.GetMinute()) << "};"
			<< "{Day:" << Tools::ConvertIntToStr(change.GetDay()) << "};"
			<< "{Month:" << Tools::ConvertIntToStr(change.GetMonth()) << "};"
			<< "{Year:" << Tools::ConvertIntToStr(change.GetYear()) << "};"
			<< "{User:" << change.GetUser() << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string ChangeService::getString()
{
	std::stringstream out;

	for (int index = 0; index < _changeList.size(); index++)
	{
		ChangeDto change = _changeList[index];

		out << "change:" 
			<< change.GetType() << "::"
			<< Tools::ConvertIntToStr(change.GetHour()) << "::"
			<< Tools::ConvertIntToStr(change.GetMinute()) << "::"
			<< Tools::ConvertIntToStr(change.GetDay()) << "::"
			<< Tools::ConvertIntToStr(change.GetMonth()) << "::"
			<< Tools::ConvertIntToStr(change.GetYear()) << "::"
			<< change.GetUser() << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}
