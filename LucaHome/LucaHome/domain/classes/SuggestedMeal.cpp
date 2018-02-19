#include "SuggestedMeal.h"

SuggestedMeal::SuggestedMeal()
{
	SuggestedMeal("", "", "", 0, 0, vector<string>());
}

SuggestedMeal::SuggestedMeal(string uuid, string title, string description, int rating, int useCounter, vector<string> shoppingItemUuidList)
{
	_uuid = uuid;
	_title = title;
	_description = description;
	_rating = rating;
	_useCounter = useCounter;
	_shoppingItemUuidList = shoppingItemUuidList;
}

SuggestedMeal::~SuggestedMeal()
{
}

void SuggestedMeal::SetUuid(string uuid)
{
	_uuid = uuid;
}

string SuggestedMeal::GetUuid()
{
	return _uuid;
}

void SuggestedMeal::SetTitle(string title)
{
	_title = title;
}

string SuggestedMeal::GetTitle()
{
	return _title;
}

void SuggestedMeal::SetDescription(string description)
{
	_description = description;
}

string SuggestedMeal::GetDescription()
{
	return _description;
}

void SuggestedMeal::SetUseCount(int useCounter)
{
	_useCounter = useCounter;
}

int SuggestedMeal::GetUseCount()
{
	return _useCounter;
}

void SuggestedMeal::SetRating(int rating)
{
	_rating = rating;
}

int SuggestedMeal::GetRating()
{
	return _rating;
}

void SuggestedMeal::SetShoppingItemUuidList(vector<string> shoppingItemUuidList)
{
	_shoppingItemUuidList = shoppingItemUuidList;
}

string SuggestedMeal::GetShoppingItemUuidDbString()
{
	stringstream data;
	for (int index = 0; index < _shoppingItemUuidList.size(); index++)
	{
		data << "" << _shoppingItemUuidList[index] << ",";
	}
	return data.str().substr(0, data.str().size() - 1);
}

string SuggestedMeal::JsonString()
{
	string str =
		string("{")
		+ string("\"SuggestedMeal\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Title\":\"") + _title + string("\",")
		+ string("\"Description\":\"") + _description + string("\",")
		+ string("\"UseCounter\":") + Tools::ConvertIntToStr(_useCounter) + string(",")
		+ string("\"Rating\":") + Tools::ConvertIntToStr(_rating) + string(",")
		+ string("\"ShoppingItemUuidList\":") + getShoppingItemUuidJson()
		+ string("}")
		+ string("}");
	return str;
}

string SuggestedMeal::ToString()
{
	string str =
		string("SuggestedMeal { uuid: ") + _uuid
		+ string("; title: ") + _title
		+ string("; description: ") + _description
		+ string("; useCounter: ") + Tools::ConvertIntToStr(_useCounter)
		+ string("; rating: ") + Tools::ConvertIntToStr(_rating)
		+ string(" }");
	return str;
}

string SuggestedMeal::getShoppingItemUuidJson() {
	stringstream jsonStringStream;
	jsonStringStream << "[";

	std::stringstream data;
	for (int index = 0; index < _shoppingItemUuidList.size(); index++)
	{
		string uuid = _shoppingItemUuidList[index];
		data << "\"" << uuid << "\",";
	}

	jsonStringStream << data.str().substr(0, data.str().size() - 1) << "]" << std::endl;
	return jsonStringStream.str();
}
