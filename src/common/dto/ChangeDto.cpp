#include "ChangeDto.h"

ChangeDto::ChangeDto()
{
	_type = "Dummy";
	_hour = -1;
	_minute = -1;
	_day = -1;
	_month = -1;
	_year = -1;
	_userName = "Dummy";
}

ChangeDto::ChangeDto(std::string type, int hour, int minute, int day, int month, int year, std::string userName)
{
	_type = type;
	_hour = hour;
	_minute = minute;
	_day = day;
	_month = month;
	_year = year;
	_userName = userName;
}

ChangeDto::~ChangeDto()
{
}

void ChangeDto::SetType(std::string type)
{
	_type = type;
}

std::string ChangeDto::GetType()
{
	return _type;
}

void ChangeDto::SetHour(int hour)
{
	_hour = hour;
}

int ChangeDto::GetHour()
{
	return _hour;
}

void ChangeDto::SetMinute(int minute)
{
	_minute = minute;
}

int ChangeDto::GetMinute()
{
	return _minute;
}

void ChangeDto::SetDay(int day)
{
	_day = day;
}

int ChangeDto::GetDay()
{
	return _day;
}

void ChangeDto::SetMonth(int month)
{
	_month = month;
}

int ChangeDto::GetMonth()
{
	return _month;
}

void ChangeDto::SetYear(int year)
{
	_year = year;
}

int ChangeDto::GetYear()
{
	return _year;
}

void ChangeDto::SetUserName(std::string userName)
{
	_userName = userName;
}

std::string ChangeDto::GetUserName()
{
	return _userName;
}

std::string ChangeDto::SaveString()
{
	std::string str = 
		_type + ":"
		+ Tools::ConvertIntToStr(_hour) + ":"
		+ Tools::ConvertIntToStr(_minute) + ":"
		+ Tools::ConvertIntToStr(_day) + ":"
		+ Tools::ConvertIntToStr(_month) + ":"
		+ Tools::ConvertIntToStr(_year) + ":"
		+ _userName + ";";
	return str;
}

std::string ChangeDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Change\":")
		+ std::string("{")
		+ std::string("\"Type\":") + _type + std::string(",")
		+ std::string("\"UserName\":") + _userName + std::string(",")
		+ std::string("{")
		+ std::string("\"Date\":")
		+ std::string("{")
		+ std::string("\"Day\":") + Tools::ConvertIntToStr(_day) + std::string(",")
		+ std::string("\"Month\":") + Tools::ConvertIntToStr(_month) + std::string(",")
		+ std::string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ std::string("}") + std::string(",")
		+ std::string("\"Time\":")
		+ std::string("{")
		+ std::string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + std::string(",")
		+ std::string("\"Minute\":") + Tools::ConvertIntToStr(_minute)
		+ std::string("}")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string ChangeDto::ToString()
{
	std::string str =
		std::string("ChangeDto { type: ") + _type 
		+ std::string("; hour: ") + Tools::ConvertIntToStr(_hour) 
		+ std::string("; minute: ") + Tools::ConvertIntToStr(_minute)
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year)
		+ std::string("; userName: ") + _userName 
		+ std::string(" }");
	return str;
}
