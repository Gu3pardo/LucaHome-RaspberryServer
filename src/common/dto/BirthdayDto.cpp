#include "BirthdayDto.h"

BirthdayDto::BirthdayDto()
{
	_id = 0;
	_name = "Dummy";
	_day = 1;
	_month = 1;
	_year = 1900;
	_group = "";
	_remindMe = false;
	_sentMail = false;
}

BirthdayDto::BirthdayDto(int id, std::string name, int day, int month, int year, std::string group, bool remindMe, bool sentMail)
{
	_id = id;
	_name = name;
	_day = day;
	_month = month;
	_year = year;
	_group = group;
	_remindMe = remindMe;
	_sentMail = sentMail;
}

BirthdayDto::~BirthdayDto()
{
}

void BirthdayDto::SetId(int id)
{
	_id = id;
}

int BirthdayDto::GetId()
{
	return _id;
}

void BirthdayDto::SetName(std::string name)
{
	_name = name;
}

std::string BirthdayDto::GetName()
{
	return _name;
}

void BirthdayDto::SetDay(int day)
{
	_day = day;
}

int BirthdayDto::GetDay()
{
	return _day;
}

void BirthdayDto::SetMonth(int month)
{
	_month = month;
}

int BirthdayDto::GetMonth()
{
	return _month;
}

void BirthdayDto::SetYear(int year)
{
	_year = year;
}

int BirthdayDto::GetYear()
{
	return _year;
}

int BirthdayDto::GetAge()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayYear = now->tm_year + 1900;
	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (_month < todayMonth)
	{
		return todayYear - _year;
	}
	else if (_month == todayMonth)
	{
		if (_day > todayDay)
		{
			return todayYear - _year - 1;
		}
		else
		{
			return todayYear - _year;
		}
	}
	else
	{
		return todayYear - _year - 1;
	}
}

bool BirthdayDto::HasBirthday()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (todayMonth == _month && todayDay == _day)
	{
		return true;
	}

	return false;
}

void BirthdayDto::SetGroup(std::string group)
{
	_group = group;
}

std::string BirthdayDto::GetGroup()
{
	return _group;
}

void BirthdayDto::SetSentMail(bool sentMail) {
	_sentMail = sentMail;
}

bool BirthdayDto::GetSentMail() {
	return _sentMail;
}

void BirthdayDto::SetRemindMe(bool remindMe) {
	_remindMe = remindMe;
}

bool BirthdayDto::GetRemindMe() {
	return _remindMe;
}

std::string BirthdayDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _name + ":"
		+ Tools::ConvertIntToStr(_day) + ":"
		+ Tools::ConvertIntToStr(_month) + ":"
		+ Tools::ConvertIntToStr(_year) + ":"
		+ _group + ":"
		+ Tools::ConvertBoolToStr(_remindMe) + ":"
		+ Tools::ConvertBoolToStr(_sentMail) + ";";

	return str;
}

std::string BirthdayDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Birthday\":")
		+ std::string("{")
		+ std::string("\"Id\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"RemindMe\":") + Tools::ConvertBoolToStr(_remindMe) + std::string(",")
		+ std::string("\"SentMail\":") + Tools::ConvertBoolToStr(_sentMail) + std::string(",")
		+ std::string("\"Group\":\"") + _group + std::string("\",")
		+ std::string("\"Date\":")
		+ std::string("{")
		+ std::string("\"Day\":") + Tools::ConvertIntToStr(_day) + std::string(",")
		+ std::string("\"Month\":") + Tools::ConvertIntToStr(_month) + std::string(",")
		+ std::string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ std::string("}")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string BirthdayDto::PhpString()
{
	std::stringstream out;

	out << "birthday::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _name << "::"
		<< Tools::ConvertIntToStr(_day) << "::"
		<< Tools::ConvertIntToStr(_month) << "::"
		<< Tools::ConvertIntToStr(_year) << "::"
		<< _group << "::"
		<< Tools::ConvertBoolToStr(_remindMe) << "::"
		<< Tools::ConvertBoolToStr(_sentMail) << ";";

	return out.str();
}

std::string BirthdayDto::ToString()
{
	std::string str = std::string("BirthdayDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; name: ") + _name
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year)
		+ std::string("; group: ") + _group
		+ std::string("; remindme: ") + Tools::ConvertBoolToStr(_remindMe)
		+ std::string("; sentmail: ") + Tools::ConvertBoolToStr(_sentMail)
		+ std::string(" }");
	return str;
}
