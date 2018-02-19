#include "Coin.h"

Coin::Coin()
{
	Coin("", "", "", 0);
}

Coin::Coin(string uuid, string userUuid, string type, double amount)
{
	_uuid = uuid;
	_userUuid = userUuid;
	_type = type;
	_amount = amount;
}

Coin::~Coin()
{
}

void Coin::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Coin::GetUuid()
{
	return _uuid;
}

void Coin::SetUserUuid(string userUuid)
{
	_userUuid = userUuid;
}

string Coin::GetUserUuid()
{
	return _userUuid;
}

void Coin::SetType(string type)
{
	_type = type;
}

string Coin::GetType()
{
	return _type;
}

void Coin::SetAmount(double amount)
{
	_amount = amount;
}

double Coin::GetAmount()
{
	return _amount;
}

string Coin::JsonString()
{
	string str =
		string("{")
		+ string("\"Coin\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"UserUuid\":\"") + _userUuid + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"Amount\":") + Tools::ConvertDoubleToStr(_amount)
		+ string("}")
		+ string("}");
	return str;
}

string Coin::ToString()
{
	string str =
		string("Coin { uuid: ") + _uuid
		+ string("; useruuid: ") + _userUuid
		+ string("; type: ") + _type
		+ string("; amount: ") + Tools::ConvertDoubleToStr(_amount)
		+ string(" }");
	return str;
}
