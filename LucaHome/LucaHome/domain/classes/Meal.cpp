#include "Meal.h"

Meal::Meal()
{
	Meal("", "", "", 1, 1, 1, 1970, vector<string>());
}

Meal::Meal(string uuid, string title, string description, int weekday, int day, int month, int year, vector<string> shoppingItemUuidList)
{
	_uuid = uuid;
	_title = title;
	_description = description;
	_weekday = weekday;
	_day = day;
	_month = month;
	_year = year;
	_shoppingItemUuidList = shoppingItemUuidList;
}

Meal::~Meal()
{
}

void Meal::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Meal::GetUuid()
{
	return _uuid;
}

void Meal::SetTitle(string title)
{
	_title = title;
}

string Meal::GetTitle()
{
	return _title;
}

void Meal::SetDescription(string description)
{
	_description = description;
}

string Meal::GetDescription()
{
	return _description;
}

void Meal::SetWeekday(int weekday)
{
	_weekday = weekday;
}

int Meal::GetWeekday()
{
	return _weekday;
}

void Meal::SetDay(int day)
{
	_day = day;
}

int Meal::GetDay()
{
	return _day;
}

void Meal::SetMonth(int month)
{
	_month = month;
}

int Meal::GetMonth()
{
	return _month;
}

void Meal::SetYear(int year)
{
	_year = year;
}

int Meal::GetYear()
{
	return _year;
}

void Meal::SetShoppingItemUuidList(vector<string> shoppingItemUuidList)
{
	_shoppingItemUuidList = shoppingItemUuidList;
}

string Meal::GetShoppingItemUuidDbString()
{
	stringstream data;
	for (int index = 0; index < _shoppingItemUuidList.size(); index++)
	{
		data << "" << _shoppingItemUuidList[index] << ",";
	}
	return data.str().substr(0, data.str().size() - 1);
}

string Meal::JsonString()
{
	string str =
		string("{")
		+ string("\"Meal\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"Description\":\"") + _description + string("\",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Weekday\":") + Tools::ConvertIntToStr(_weekday) + string(",")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}") + string("\",")
		+ string("\"ShoppingItemUuidList\":") + getShoppingItemUuidJson()
		+ string("}")
		+ string("}");
	return str;
}

string Meal::ToString()
{
	string str =
		string("Meal { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; description: ") + _description
		+ string("; weekday: ") + Tools::ConvertIntToStr(_weekday)
		+ string("; day: ") + Tools::ConvertIntToStr(_day)
		+ string("; month: ") + Tools::ConvertIntToStr(_month)
		+ string("; year: ") + Tools::ConvertIntToStr(_year)
		+ string(" }");
	return str;
}

string Meal::getShoppingItemUuidJson() {
	stringstream jsonStringStream;
	jsonStringStream << "[";

	stringstream data;
	for (int index = 0; index < _shoppingItemUuidList.size(); index++)
	{
		data << "\"" << _shoppingItemUuidList[index] << "\",";
	}

	jsonStringStream << data.str().substr(0, data.str().size() - 1) << "]" << endl;
	return jsonStringStream.str();
}