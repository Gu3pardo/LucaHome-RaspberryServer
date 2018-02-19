#include "ShoppingItem.h"

ShoppingItem::ShoppingItem()
{
	ShoppingItem("", "", "", 0, "");
}

ShoppingItem::ShoppingItem(string uuid, string name, string type, int quantity, string unit)
{
	_uuid = uuid;
	_name = name;
	_type = type;
	_quantity = quantity;
	_unit = unit;
}

ShoppingItem::~ShoppingItem()
{
}

void ShoppingItem::SetUuid(string uuid)
{
	_uuid = uuid;
}

string ShoppingItem::GetUuid()
{
	return _uuid;
}

void ShoppingItem::SetName(string name)
{
	_name = name;
}

string ShoppingItem::GetName()
{
	return _name;
}

void ShoppingItem::SetType(string type)
{
	_type = type;
}

string ShoppingItem::GetType()
{
	return _type;
}

void ShoppingItem::SetQuantity(int quantity)
{
	_quantity = quantity;
}

void ShoppingItem::IncreaseQuantity(int additionalQuantity)
{
	_quantity += additionalQuantity;
}

void ShoppingItem::DecreaseQuantity(int removalQuantity)
{
	_quantity -= removalQuantity;
	if (_quantity < 1)
	{
		_quantity = 1;
	}
}

int ShoppingItem::GetQuantity()
{
	return _quantity;
}

void ShoppingItem::SetUnit(string unit)
{
	_unit = unit;
}

string ShoppingItem::GetUnit()
{
	return _unit;
}

string ShoppingItem::JsonString()
{
	string str =
		string("{")
		+ string("\"ShoppingItem\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"Quantity\":") + Tools::ConvertIntToStr(_quantity) + string(",")
		+ string("\"Unit\":\"") + _unit + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string ShoppingItem::ToString()
{
	string str =
		string("ShoppingItem { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; type: ") + _type
		+ string("; quantity: ") + Tools::ConvertIntToStr(_quantity)
		+ string("; unit: ") + _unit
		+ string(" }");
	return str;
}
