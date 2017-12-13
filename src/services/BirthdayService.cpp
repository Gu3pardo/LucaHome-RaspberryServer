#include "BirthdayService.h"

/*===============PUBLIC==============*/

BirthdayService::BirthdayService()
{
	_birthdayControlActive = true;
}

BirthdayService::~BirthdayService()
{
}

void BirthdayService::Initialize(FileController fileController, MailController mailController, std::string birthdayFile)
{
	_fileController = fileController;
	_mailController = mailController;

	_birthdayFile = birthdayFile;

	LoadData();
}

void BirthdayService::CheckBirthdayList()
{
	for (int index = 0; index < _birthdayList.size(); index++)
	{
		BirthdayDto birthday = _birthdayList[index];

		if (birthday.HasBirthday() && birthday.GetRemindMe() && !birthday.GetSendMail())
		{
			std::stringstream information;
			information
				<< birthday.GetName()
				<< " has birthday today! It is the "
				<< Tools::ConvertIntToStr(birthday.GetAge())
				<< "th birthday!";

			_mailController.SendMail(information.str());

			_birthdayList[index].SetSendMail(true);
		}
		else if (!birthday.HasBirthday() && birthday.GetSendMail())
		{
			_birthdayList[index].SetSendMail(false);
		}
	}

	std::string xmldata = _xmlService.GenerateBirthdaysXml(_birthdayList);
	_fileController.SaveFile(_birthdayFile, xmldata);
}

void BirthdayService::LoadData()
{
	std::string birthdayFileContent = _fileController.ReadFile(_birthdayFile);
	_birthdayList = _xmlService.GetBirthdayList(birthdayFileContent);
}

std::string BirthdayService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
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
		return BIRTHDAY_ERROR_NR_37;
	}

	else if (action == ADD)
	{
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			if (addBirthday(data, changeService, username))
			{
				return BIRTHDAY_ADD_SUCCESS;
			}
			return BIRTHDAY_ERROR_NR_30;
		}
		return BIRTHDAY_ERROR_NR_33;
	}

	else if (action == UPDATE)
	{
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			if (updateBirthday(data, changeService, username))
			{
				return BIRTHDAY_UPDATE_SUCCESS;
			}
			return BIRTHDAY_ERROR_NR_31;
		}
		return BIRTHDAY_ERROR_NR_33;
	}

	else if (action == DELETE)
	{
		if (deleteBirthday(atoi(data[BIRTHDAY_ID_INDEX].c_str()), changeService, username))
		{
			return BIRTHDAY_DELETE_SUCCESS;
		}
		return BIRTHDAY_ERROR_NR_32;
	}

	else if (action == SETCONTROLTASK)
	{
		std::string actionParameter = data[ACTION_PARAMETER_INDEX];

		if (actionParameter == ON)
		{
			_birthdayControlActive = true;
			return BIRTHDAY_ACTIVATE_CONTROL_SUCCESS;
		}
		else if (actionParameter == OFF)
		{
			_birthdayControlActive = false;
			return BIRTHDAY_DEACTIVATE_CONTROL_SUCCESS;
		}
		return BIRTHDAY_ERROR_NR_36;
	}

	return BIRTHDAY_ERROR_NR_34;
}

bool BirthdayService::GetBirthdayControlActive()
{
	return _birthdayControlActive;
}

/*==============PRIVATE==============*/

void BirthdayService::saveBirthdays(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateBirthdaysXml(_birthdayList);
	_fileController.SaveFile(_birthdayFile, xmldata);

	changeService.UpdateChange("Birthdays", username);
}

std::string BirthdayService::getJsonString()
{
	std::stringstream out;
	out << "\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _birthdayList.size(); index++)
	{
		BirthdayDto birthday = _birthdayList[index];
		data << birthday.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]" << "\x00" << std::endl;

	return out.str();
}

std::string BirthdayService::getPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _birthdayList.size(); index++)
	{
		BirthdayDto birthday = _birthdayList[index];

		out << "birthday::"
			<< Tools::ConvertIntToStr(birthday.GetId()) << "::"
			<< birthday.GetName() << "::"
			<< Tools::ConvertIntToStr(birthday.GetDay()) << "::"
			<< Tools::ConvertIntToStr(birthday.GetMonth()) << "::"
			<< Tools::ConvertIntToStr(birthday.GetYear()) << "::"
			<< Tools::ConvertBoolToStr(birthday.GetRemindMe()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool BirthdayService::addBirthday(std::vector<std::string> newBirthdayData, ChangeService changeService, std::string username)
{
	BirthdayDto newBirthday(
		atoi(newBirthdayData[BIRTHDAY_ID_INDEX].c_str()),
		newBirthdayData[BIRTHDAY_NAME_INDEX],
		atoi(newBirthdayData[BIRTHDAY_DAY_INDEX].c_str()),
		atoi(newBirthdayData[BIRTHDAY_MONTH_INDEX].c_str()),
		atoi(newBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()),
		Tools::ConvertStrToBool(newBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()),
		false);

	_birthdayList.push_back(newBirthday);

	saveBirthdays(changeService, username);
	LoadData();

	return true;
}

bool BirthdayService::updateBirthday(std::vector<std::string> updateBirthdayData, ChangeService changeService, std::string username)
{
	int updateBirthdayId = atoi(updateBirthdayData[BIRTHDAY_ID_INDEX].c_str());

	for (int index = 0; index < _birthdayList.size(); index++)
	{
		if (_birthdayList[index].GetId() == updateBirthdayId)
		{
			_birthdayList[index].SetName(updateBirthdayData[BIRTHDAY_NAME_INDEX]);

			_birthdayList[index].SetDay(atoi(updateBirthdayData[BIRTHDAY_DAY_INDEX].c_str()));
			_birthdayList[index].SetMonth(atoi(updateBirthdayData[BIRTHDAY_MONTH_INDEX].c_str()));
			_birthdayList[index].SetYear(atoi(updateBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()));

			_birthdayList[index].SetRemindMe(Tools::ConvertStrToBool(updateBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()));

			saveBirthdays(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool BirthdayService::deleteBirthday(int id, ChangeService changeService, std::string username)
{
	std::vector<BirthdayDto>::iterator it = _birthdayList.begin();

	while (it != _birthdayList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _birthdayList.erase(it);

			saveBirthdays(changeService, username);
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
