#include "Coin.h"

Coin::Coin()
{
	_uuid = "";
	_user = "";
	_type = "";
	_amount = 0;
}

Coin::Coin(string uuid, string user, string type, double amount)
{
	_uuid = uuid;
	_user = user;
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

void Coin::SetUser(string user)
{
	_user = user;
}

string Coin::GetUser()
{
	return _user;
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
		+ string("\"User\":\"") + _user + string("\",")
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
		+ string("; user: ") + _user
		+ string("; type: ") + _type
		+ string("; amount: ") + Tools::ConvertDoubleToStr(_amount)
		+ string(" }");
	return str;
}
