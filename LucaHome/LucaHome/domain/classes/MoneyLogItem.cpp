#include "MoneyLogItem.h"

MoneyLogItem::MoneyLogItem()
{
	MoneyLogItem("", "", "", "", 0.0, "", 1, 1, 1970, "");
}

MoneyLogItem::MoneyLogItem(
	string uuid,
	string typeUuid,
	string bank,
	string plan,
	double amount,
	string unit,
	int day, int month, int year,
	string userUuid)
{
	_uuid = uuid;
	_typeUuid = typeUuid;
	_bank = bank;
	_plan = plan;
	_amount = amount;
	_unit = unit;
	_day = day;
	_month = month;
	_year = year;
	_userUuid = userUuid;
}

MoneyLogItem::~MoneyLogItem()
{
}

void MoneyLogItem::SetUuid(string uuid)
{
	_uuid = uuid;
}

string MoneyLogItem::GetUuid()
{
	return _uuid;
}

void MoneyLogItem::SetTypeUuid(string typeUuid)
{
	_typeUuid = typeUuid;
}

string MoneyLogItem::GetTypeUuid()
{
	return _typeUuid;
}

void MoneyLogItem::SetBank(string bank)
{
	_bank = bank;
}

string MoneyLogItem::GetBank()
{
	return _bank;
}

void MoneyLogItem::SetPlan(string plan)
{
	_plan = plan;
}

string MoneyLogItem::GetPlan()
{
	return _plan;
}

void MoneyLogItem::SetAmount(double amount)
{
	_amount = amount;
}

double MoneyLogItem::GetAmount()
{
	return _amount;
}

void MoneyLogItem::SetUnit(string unit)
{
	_unit = unit;
}

string MoneyLogItem::GetUnit()
{
	return _unit;
}

void MoneyLogItem::SetDay(int day)
{
	_day = day;
}

int MoneyLogItem::GetDay()
{
	return _day;
}

void MoneyLogItem::SetMonth(int month)
{
	_month = month;
}

int MoneyLogItem::GetMonth()
{
	return _month;
}

void MoneyLogItem::SetYear(int year)
{
	_year = year;
}

int MoneyLogItem::GetYear()
{
	return _year;
}

void MoneyLogItem::SetUserUuid(string userUuid)
{
	_userUuid = userUuid;
}

string MoneyLogItem::GetUserUuid()
{
	return _userUuid;
}

string MoneyLogItem::JsonString()
{
	string str =
		string("{")
		+ string("\"MoneyLogItem\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"TypeId\":\"") + _typeUuid + string("\",")
		+ string("\"Bank\":\"") + _bank + string("\",")
		+ string("\"Plan\":\"") + _plan + string("\",")
		+ string("\"Amount\":") + Tools::ConvertDoubleToStr(_amount) + string(",")
		+ string("\"Unit\":\"") + _unit + string("\",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}")
		+ string(",")
		+ string("\"UserUuid\":\"") + _userUuid + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string MoneyLogItem::ToString()
{
	string str =
		string("MoneyLogItem { uuid: ") + _uuid
		+ string("; typeuuid: ") + _typeUuid
		+ string("; bank: ") + _bank
		+ string("; plan: ") + _plan
		+ string("; amount: ") + Tools::ConvertDoubleToStr(_amount)
		+ string("; unit: ") + _unit
		+ string("; day: ") + Tools::ConvertIntToStr(_day)
		+ string("; month: ") + Tools::ConvertIntToStr(_month)
		+ string("; year: ") + Tools::ConvertIntToStr(_year)
		+ string("; useruuid: ") + _userUuid
		+ string(" }");
	return str;
}
