#include "BirthdayDto.h"

BirthdayDto::BirthdayDto()
{
	_id = -1;
	_name = "Dummy";
	_day = 2;
	_month = 1;
	_year = 1990;
	_sendMail = false;
}

BirthdayDto::BirthdayDto(int id, std::string name, int day, int month, int year, bool sendMail)
{
	_id = id;
	_name = name;
	_day = day;
	_month = month;
	_year = year;
	_sendMail = sendMail;
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

void BirthdayDto::SetSendMail(bool sendMail) {
	_sendMail = sendMail;
}

bool BirthdayDto::GetSendMail() {
	return _sendMail;
}

std::string BirthdayDto::ToString()
{
	std::string str = std::string("BirthdayDto { id: ") + Tools::ConvertIntToStr(_id) 
		+ std::string("; name: ") + _name 
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day) 
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month) 
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year) 
		+ std::string(" }");
	return str;
}
