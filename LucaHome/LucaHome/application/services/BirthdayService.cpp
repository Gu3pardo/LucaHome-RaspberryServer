#include "BirthdayService.h"

/*===============PUBLIC==============*/

BirthdayService::BirthdayService() {}

BirthdayService::~BirthdayService() {}

void BirthdayService::Initialize(string databaseName)
{
	_birthdayDatabase = BirthdayDatabase(databaseName);
}

string BirthdayService::PerformAction(vector<string> data)
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
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			char error = addBirthday(data);
			if (!error)
			{
				return BIRTHDAY_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return BIRTHDAY_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == BIRTHDAY_DATA_SIZE)
		{
			char error = updateBirthday(data);
			if (!error)
			{
				return BIRTHDAY_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return BIRTHDAY_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteBirthday(actionParameter);
		if (!error)
		{
			return BIRTHDAY_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void BirthdayService::Dispose()
{
	_birthdayDatabase.Dispose();
}

void BirthdayService::CheckBirthdayList(MailController mailController)
{
	vector<Birthday> birthdayList = _birthdayDatabase.GetList();

	for (int index = 0; index < birthdayList.size(); index++)
	{
		Birthday birthday = birthdayList[index];
		if (birthday.HasBirthday() && birthday.GetRemindMe() && !birthday.GetSentMail())
		{
			std::stringstream information;
			information << birthday.GetName() << " has birthday today! It is the " << Tools::ConvertIntToStr(birthday.GetAge()) << "th birthday!";
			mailController.SendMail(information.str());
			birthdayList[index].SetSentMail(true);
		}
		else if (!birthday.HasBirthday() && birthday.GetSentMail())
		{
			birthdayList[index].SetSentMail(false);
		}
		_birthdayDatabase.Update(birthday);
	}
}

/*==============PRIVATE==============*/

string BirthdayService::getJsonString()
{
	vector<Birthday> birthdayList = _birthdayDatabase.GetList();

	stringstream data;
	for (int index = 0; index < birthdayList.size(); index++)
	{
		data << birthdayList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char BirthdayService::addBirthday(vector<string> newBirthdayData)
{
	Birthday newBirthday(
		newBirthdayData[BIRTHDAY_UUID_INDEX].c_str(),
		newBirthdayData[BIRTHDAY_NAME_INDEX].c_str(),
		atoi(newBirthdayData[BIRTHDAY_DAY_INDEX].c_str()),
		atoi(newBirthdayData[BIRTHDAY_MONTH_INDEX].c_str()),
		atoi(newBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()),
		newBirthdayData[BIRTHDAY_GROUP_INDEX].c_str(),
		atoi(newBirthdayData[BIRTHDAY_REMINDME_INDEX].c_str()) == 1,
		false);
	return _birthdayDatabase.Insert(_birthdayDatabase.GetList().size(), newBirthday);
}

char BirthdayService::updateBirthday(vector<string> updateBirthdayData)
{
	Birthday updateBirthday(
		updateBirthdayData[BIRTHDAY_UUID_INDEX].c_str(),
		updateBirthdayData[BIRTHDAY_NAME_INDEX].c_str(),
		atoi(updateBirthdayData[BIRTHDAY_DAY_INDEX].c_str()),
		atoi(updateBirthdayData[BIRTHDAY_MONTH_INDEX].c_str()),
		atoi(updateBirthdayData[BIRTHDAY_YEAR_INDEX].c_str()),
		updateBirthdayData[BIRTHDAY_GROUP_INDEX].c_str(),
		atoi(updateBirthdayData[BIRTHDAY_REMINDME_INDEX].c_str()) == 1,
		false);
	return _birthdayDatabase.Update(updateBirthday);
}

char BirthdayService::deleteBirthday(string deleteUuid)
{
	return _birthdayDatabase.Delete(deleteUuid);
}
