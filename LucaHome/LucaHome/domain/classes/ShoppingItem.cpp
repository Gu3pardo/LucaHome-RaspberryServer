#include "ShoppingItem.h"

ShoppingItem::ShoppingItem() :SuggestedShoppingItem()
{
	_creationTime = time(0);
	_sentDay7Reminder = false;
}

ShoppingItem::ShoppingItem(string uuid, string name, string type, int quantity, string unit, time_t creationTime, bool sentDay7Reminder)
	: SuggestedShoppingItem(uuid, name, type, quantity, unit)
{
	_creationTime = creationTime;
	_sentDay7Reminder = sentDay7Reminder;
}

ShoppingItem::~ShoppingItem()
{
}

void ShoppingItem::SetCreationTime(time_t creationTime)
{
	_creationTime = creationTime;
}

time_t ShoppingItem::GetCreationTime()
{
	return _creationTime;
}

void ShoppingItem::SetSentDay7Reminder(bool sentDay7Reminder)
{
	_sentDay7Reminder = sentDay7Reminder;
}

bool ShoppingItem::GetSentDay7Reminder()
{
	return _sentDay7Reminder;
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
		+ string("\"Unit\":\"") + _unit + string("\",")
		+ string("\"CreationTime\":") + Tools::ConvertIntToStr(_creationTime) + string(",")
		+ string("\"SentDay7Reminder\":") + Tools::ConvertBoolToStr(_sentDay7Reminder)
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
		+ string("; creationtime: ") + Tools::ConvertIntToStr(_creationTime)
		+ string("; sentday7reminder: ") + Tools::ConvertBoolToStr(_sentDay7Reminder)
		+ string(" }");
	return str;
}
