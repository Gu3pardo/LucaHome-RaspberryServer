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

	loadBirthdays();
}

void BirthdayService::CheckBirthdayList()
{
	std::vector<BirthdayDto>::iterator it = _birthdayList.begin();

	while (it != _birthdayList.end())
	{
		if ((*it).HasBirthday() && !(*it).GetSendMail())
		{
			std::stringstream information;
			information
				<< (*it).GetName()
				<< " has birthday today! It is the "
				<< Tools::ConvertIntToStr((*it).GetAge())
				<< "th birthday!";

			_mailController.SendMail(information.str());

			(*it).SetSendMail(true);
		}
		else if (!(*it).HasBirthday() && (*it).GetSendMail())
		{
			(*it).SetSendMail(false);
		}
	}

	std::string xmldata = _xmlService.GenerateBirthdaysXml(_birthdayList);
	_fileController.SaveFile(_birthdayFile, xmldata);
}

void BirthdayService::ReloadData()
{
	loadBirthdays();
}

std::string BirthdayService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	if (action == GET)
	{
		if (data.size() == 6)
		{
			if (data[5] == REDUCED)
			{
				return getReducedString();
			}
		}

		return getBirthdays();
	}
	else if (action == ADD)
	{
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			if (addBirthday(data, changeService, username))
			{
				return "addbirthday:1";
			}
			else
			{
				return "Error 30:Could not add birthday";
			}
		}
		else
		{
			return "Error 33:Wrong word size for birthday";
		}
	}
	else if (action == UPDATE)
	{
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			if (updateBirthday(data, changeService, username))
			{
				return "updatebirthday:1";
			}
			else
			{
				return "Error 31:Could not update birthday";
			}
		}
		else
		{
			return "Error 33:Wrong word size for birthday";
		}
	}
	else if (action == DELETE)
	{
		if (deleteBirthday(atoi(data[ID_INDEX].c_str()), changeService, username))
		{
			return "deletebirthday:1";
		}
		else
		{
			return "Error 32:Could not delete birthday";
		}
	}
	else if (action == SETCONTROLTASK)
	{
		if (data[4] == ON)
		{
			_birthdayControlActive = true;
			return "setBirthdayControl:1:1";
		}
		else if (data[4] == OFF)
		{
			_birthdayControlActive = false;
			return "setBirthdayControl:0:1";
		}
		else
		{
			return "Error 36:Invalid data for birthday";
		}
	}
	else
	{
		return "Error 34:Action not found for birthday";
	}
}

bool BirthdayService::GetBirthdayControlActive()
{
	return _birthdayControlActive;
}

/*==============PRIVATE==============*/

void BirthdayService::loadBirthdays()
{
	std::string birthdayFileContent = _fileController.ReadFile(_birthdayFile);
	_birthdayList = _xmlService.GetBirthdayList(birthdayFileContent);
}

void BirthdayService::saveBirthdays(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateBirthdaysXml(_birthdayList);
	_fileController.SaveFile(_birthdayFile, xmldata);

	changeService.UpdateChange("Birthdays", username);
}

std::string BirthdayService::getBirthdays()
{
	std::stringstream out;

	for (int index = 0; index < _birthdayList.size(); index++)
	{
		BirthdayDto birthday = _birthdayList[index];

		out
			<< "{birthday:"
			<< "{id:" << Tools::ConvertIntToStr(birthday.GetId()) << "};"
			<< "{name:" << birthday.GetName() << "};"
			<< "{day:" << Tools::ConvertIntToStr(birthday.GetDay()) << "};"
			<< "{month:" << Tools::ConvertIntToStr(birthday.GetMonth()) << "};"
			<< "{year:" << Tools::ConvertIntToStr(birthday.GetYear()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string BirthdayService::getReducedString()
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
			<< Tools::ConvertIntToStr(birthday.GetYear()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool BirthdayService::addBirthday(std::vector<std::string> newBirthdayData, ChangeService changeService, std::string username)
{
	BirthdayDto newBirthday(
		atoi(newBirthdayData[ID_INDEX].c_str()),
		newBirthdayData[NAME_INDEX],
		atoi(newBirthdayData[DAY_INDEX].c_str()),
		atoi(newBirthdayData[MONTH_INDEX].c_str()),
		atoi(newBirthdayData[YEAR_INDEX].c_str()),
		false);

	_birthdayList.push_back(newBirthday);

	saveBirthdays(changeService, username);
	loadBirthdays();

	return true;
}

bool BirthdayService::updateBirthday(std::vector<std::string> updateBirthdayData, ChangeService changeService, std::string username)
{
	BirthdayDto updateBirthday(
		atoi(updateBirthdayData[ID_INDEX].c_str()),
		updateBirthdayData[NAME_INDEX],
		atoi(updateBirthdayData[DAY_INDEX].c_str()),
		atoi(updateBirthdayData[MONTH_INDEX].c_str()),
		atoi(updateBirthdayData[YEAR_INDEX].c_str()),
		false);

	for (int index = 0; index < _birthdayList.size(); index++)
	{
		if (_birthdayList[index].GetId() == updateBirthday.GetId())
		{
			_birthdayList[index] = updateBirthday;

			saveBirthdays(changeService, username);
			loadBirthdays();

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
			loadBirthdays();

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}
