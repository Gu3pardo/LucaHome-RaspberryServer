#include "MoneyLogItem.h"

MoneyLogItem::MoneyLogItem()
{
	_uuid = "";
	_typeUuid = "";
	_bank = "";
	_plan = "";
	_amount = 0.0;
	_unit = "";
	_day = 1;
	_month = 1;
	_year = 1970;
	_user = "";
}

MoneyLogItem::MoneyLogItem(
	string uuid,
	string typeUuid,
	string bank,
	string plan,
	double amount,
	string unit,
	int day, int month, int year,
	string user)
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
	_user = user;
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

void MoneyLogItem::SetUser(string user)
{
	_user = user;
}

string MoneyLogItem::GetUser()
{
	return _user;
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
		+ string("\"User\":\"") + _user + string("\"")
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
		+ string("; user: ") + _user
		+ string(" }");
	return str;
}
