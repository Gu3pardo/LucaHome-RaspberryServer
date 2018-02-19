#include "SuggestedShoppingItem.h"

SuggestedShoppingItem::SuggestedShoppingItem()
{
	SuggestedShoppingItem("", "", "", 0, "");
}

SuggestedShoppingItem::SuggestedShoppingItem(string uuid, string name, string type, int quantity, string unit)
{
	_uuid = uuid;
	_name = name;
	_type = type;
	_quantity = quantity;
	_unit = unit;
}

SuggestedShoppingItem::~SuggestedShoppingItem()
{
}

void SuggestedShoppingItem::SetUuid(string uuid)
{
	_uuid = uuid;
}

string SuggestedShoppingItem::GetUuid()
{
	return _uuid;
}

void SuggestedShoppingItem::SetName(string name)
{
	_name = name;
}

string SuggestedShoppingItem::GetName()
{
	return _name;
}

void SuggestedShoppingItem::SetType(string type)
{
	_type = type;
}

string SuggestedShoppingItem::GetType()
{
	return _type;
}

void SuggestedShoppingItem::SetQuantity(int quantity)
{
	_quantity = quantity;
}

void SuggestedShoppingItem::IncreaseQuantity(int additionalQuantity)
{
	_quantity += additionalQuantity;
}

void SuggestedShoppingItem::DecreaseQuantity(int removalQuantity)
{
	_quantity -= removalQuantity;
	if (_quantity < 1)
	{
		_quantity = 1;
	}
}

int SuggestedShoppingItem::GetQuantity()
{
	return _quantity;
}

void SuggestedShoppingItem::SetUnit(string unit)
{
	_unit = unit;
}

string SuggestedShoppingItem::GetUnit()
{
	return _unit;
}

string SuggestedShoppingItem::JsonString()
{
	string str =
		string("{")
		+ string("\"SuggestedShoppingItem\":")
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

string SuggestedShoppingItem::ToString()
{
	string str =
		string("SuggestedShoppingItem { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; type: ") + _type
		+ string("; quantity: ") + Tools::ConvertIntToStr(_quantity)
		+ string("; unit: ") + _unit
		+ string(" }");
	return str;
}
