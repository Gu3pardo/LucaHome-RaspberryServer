#include "MoneyMeterDataDto.h"

MoneyMeterDataDto::MoneyMeterDataDto()
{
	_id = 0;
	_typeId = 0;
	_bank = "";
	_plan = "";
	_amount = 0.0;
	_unit = "";
	_day = 1;
	_month = 1;
	_year = 1970;
	_user = "";
}

MoneyMeterDataDto::MoneyMeterDataDto(
	int id,
	int typeId,
	std::string bank,
	std::string plan,
	double amount,
	std::string unit,
	int day, int month, int year,
	std::string user)
{
	_id = id;
	_typeId = typeId;
	_bank = bank;
	_plan = plan;
	_amount = amount;
	_unit = unit;
	_day = day;
	_month = month;
	_year = year;
	_user = user;
}

MoneyMeterDataDto::~MoneyMeterDataDto()
{
}

void MoneyMeterDataDto::SetId(int id)
{
	_id = id;
}

int MoneyMeterDataDto::GetId()
{
	return _id;
}

void MoneyMeterDataDto::SetTypeId(int typeId)
{
	_typeId = typeId;
}

int MoneyMeterDataDto::GetTypeId()
{
	return _typeId;
}

void MoneyMeterDataDto::SetBank(std::string bank)
{
	_bank = bank;
}

std::string MoneyMeterDataDto::GetBank()
{
	return _bank;
}

void MoneyMeterDataDto::SetPlan(std::string plan)
{
	_plan = plan;
}

std::string MoneyMeterDataDto::GetPlan()
{
	return _plan;
}

void MoneyMeterDataDto::SetAmount(double amount)
{
	_amount = amount;
}

double MoneyMeterDataDto::GetAmount()
{
	return _amount;
}

void MoneyMeterDataDto::SetUnit(std::string unit)
{
	_unit = unit;
}

std::string MoneyMeterDataDto::GetUnit()
{
	return _unit;
}

void MoneyMeterDataDto::SetDay(int day)
{
	_day = day;
}

int MoneyMeterDataDto::GetDay()
{
	return _day;
}

void MoneyMeterDataDto::SetMonth(int month)
{
	_month = month;
}

int MoneyMeterDataDto::GetMonth()
{
	return _month;
}

void MoneyMeterDataDto::SetYear(int year)
{
	_year = year;
}

int MoneyMeterDataDto::GetYear()
{
	return _year;
}

void MoneyMeterDataDto::SetUser(std::string user)
{
	_user = user;
}

std::string MoneyMeterDataDto::GetUser()
{
	return _user;
}

std::string MoneyMeterDataDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ Tools::ConvertIntToStr(_typeId) + ":"
		+ _bank + ":"
		+ _plan + ":"
		+ Tools::ConvertDoubleToStr(_amount) + ":"
		+ _unit + ":"
		+ Tools::ConvertIntToStr(_day) + ":"
		+ Tools::ConvertIntToStr(_month) + ":"
		+ Tools::ConvertIntToStr(_year) + ":"
		+ _user + ";";

	return str;
}

std::string MoneyMeterDataDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"MoneyMeterData\":")
		+ std::string("{")
		+ std::string("\"Id\":\"") + Tools::ConvertIntToStr(_id) + std::string("\",")
		+ std::string("\"TypeId\":\"") + Tools::ConvertIntToStr(_typeId) + std::string("\",")
		+ std::string("\"Bank\":\"") + _bank + std::string("\",")
		+ std::string("\"Plan\":\"") + _plan + std::string("\",")
		+ std::string("\"Amount\":") + Tools::ConvertDoubleToStr(_amount) + std::string(",")
		+ std::string("\"Unit\":\"") + _unit + std::string("\",")
		+ std::string("\"Date\":")
		+ std::string("{")
		+ std::string("\"Day\":") + Tools::ConvertIntToStr(_day) + std::string(",")
		+ std::string("\"Month\":") + Tools::ConvertIntToStr(_month) + std::string(",")
		+ std::string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ std::string("}")
		+ std::string(",")
		+ std::string("\"User\":\"") + _user + std::string("\"")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string MoneyMeterDataDto::ToString()
{
	std::string str =
		std::string("MoneyMeterDataDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; typeid: ") + Tools::ConvertIntToStr(_typeId)
		+ std::string("; bank: ") + _bank
		+ std::string("; plan: ") + _plan
		+ std::string("; amount: ") + Tools::ConvertDoubleToStr(_amount)
		+ std::string("; unit: ") + _unit
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year)
		+ std::string("; user: ") + _user
		+ std::string(" }");
	return str;
}
