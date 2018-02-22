#include "MoneyLogItem.h"

MoneyLogItem::MoneyLogItem()
{
	MoneyLogItem("", "", "", "", 0.0, "", "", time(0));
}

MoneyLogItem::MoneyLogItem(
	string uuid,
	string typeUuid,
	string bank,
	string plan,
	double amount,
	string unit,
	string userUuid,
	time_t saveDate)
{
	_uuid = uuid;
	_typeUuid = typeUuid;
	_bank = bank;
	_plan = plan;
	_amount = amount;
	_unit = unit;
	_userUuid = userUuid;
	_saveDate = saveDate;
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

void MoneyLogItem::SetUserUuid(string userUuid)
{
	_userUuid = userUuid;
}

string MoneyLogItem::GetUserUuid()
{
	return _userUuid;
}

void MoneyLogItem::SetSaveDate(time_t saveDate)
{
	_saveDate = saveDate;
}

time_t MoneyLogItem::GetSaveDate()
{
	return _saveDate;
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
		+ string("\"UserUuid\":\"") + _userUuid + string("\",")
		+ string("\"SaveDate\":") + Tools::ConvertIntToStr(_saveDate)
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
		+ string("; useruuid: ") + _userUuid
		+ string("; savedate: ") + Tools::ConvertIntToStr(_saveDate)
		+ string(" }");
	return str;
}
