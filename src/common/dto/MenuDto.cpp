#include "MenuDto.h"

MenuDto::MenuDto()
{
	_weekday = "N.A.";
	_day = -1;
	_month = -1;
	_year = -1;
	_title = "N.A.";
	_description = "N.A.";
}

MenuDto::MenuDto(std::string weekday, int day, int month, int year, std::string title, std::string description)
{
	_weekday = weekday;
	_day = day;
	_month = month;
	_year = year;
	_title = title;
	_description = description;
}

MenuDto::~MenuDto()
{
}

void MenuDto::SetWeekday(std::string weekday)
{
	_weekday = weekday;
}

std::string MenuDto::GetWeekday()
{
	return _weekday;
}

void MenuDto::SetDay(int day)
{
	_day = day;
}

int MenuDto::GetDay()
{
	return _day;
}

void MenuDto::SetMonth(int month)
{
	_month = month;
}

int MenuDto::GetMonth()
{
	return _month;
}

void MenuDto::SetYear(int year)
{
	_year = year;
}

int MenuDto::GetYear()
{
	return _year;
}

void MenuDto::SetTitle(std::string title)
{
	_title = title;
}

std::string MenuDto::GetTitle()
{
	return _title;
}

void MenuDto::SetDescription(std::string description)
{
	_description = description;
}

std::string MenuDto::GetDescription()
{
	return _description;
}

std::string MenuDto::SaveString()
{
	std::string str =
		"<" + _weekday + ">"
		+ Tools::ConvertIntToStr(_day) + ":"
		+ Tools::ConvertIntToStr(_month) + ":"
		+ Tools::ConvertIntToStr(_year) + ":"
		+ _title + ":"
		+ _description
		+ "</" + _weekday + ">";
	return str;
}

std::string MenuDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Menu\":")
		+ std::string("{")
		+ std::string("\"Title\":\"") + _title + std::string("\",")
		+ std::string("\"Description\":\"") + _description + std::string("\",")
		+ std::string("\"Weekday\":\"") + _weekday + std::string("\",")
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

std::string MenuDto::PhpString()
{
	std::stringstream out;

	out << "menu::"
		<< _weekday << "::"
		<< Tools::ConvertIntToStr(_day) << "::"
		<< Tools::ConvertIntToStr(_month) << "::"
		<< Tools::ConvertIntToStr(_year) << "::"
		<< _title << "::"
		<< _description << ";";

	return out.str();
}

std::string MenuDto::ToString()
{
	std::string str =
		std::string("MenuDto { title: ") + _title
		+ std::string("; description: ") + _description
		+ std::string("; weekday: ") + _weekday
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year)
		+ std::string(" }");
	return str;
}
