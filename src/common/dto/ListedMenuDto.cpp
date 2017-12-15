#include "ListedMenuDto.h"

ListedMenuDto::ListedMenuDto()
{
	_id = -1;
	_title = "N.A.";
	_description = "N.A.";
	_rating = 0;
	_useCounter = 0;
}

ListedMenuDto::ListedMenuDto(int id, std::string title, std::string description, int rating, int useCounter)
{
	_id = id;
	_title = title;
	_description = description;
	_rating = rating;
	_useCounter = useCounter;
}

ListedMenuDto::~ListedMenuDto()
{
}

void ListedMenuDto::SetId(int id)
{
	_id = id;
}

int ListedMenuDto::GetId()
{
	return _id;
}

void ListedMenuDto::SetTitle(std::string title)
{
	_title = title;
}

std::string ListedMenuDto::GetTitle()
{
	return _title;
}

void ListedMenuDto::SetDescription(std::string description)
{
	_description = description;
}

std::string ListedMenuDto::GetDescription()
{
	return _description;
}

void ListedMenuDto::SetUseCount(int useCounter)
{
	_useCounter = useCounter;
}

int ListedMenuDto::GetUseCount()
{
	return _useCounter;
}

void ListedMenuDto::SetRating(int rating)
{
	_rating = rating;
}

int ListedMenuDto::GetRating()
{
	return _rating;
}

std::string ListedMenuDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _title + ":"
		+ _description + ":"
		+ Tools::ConvertIntToStr(_useCounter) + ":"
		+ Tools::ConvertIntToStr(_rating) + ";";
	return str;
}

std::string ListedMenuDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"ListedMenu\":")
		+ std::string("{")
		+ std::string("\"ID\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Title\":\"") + _title + std::string("\",")
		+ std::string("\"Description\":\"") + _description + std::string("\",")
		+ std::string("\"UseCounter\":") + Tools::ConvertIntToStr(_useCounter) + std::string(",")
		+ std::string("\"Rating\":") + Tools::ConvertIntToStr(_rating)
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string ListedMenuDto::PhpString()
{
	std::stringstream out;

	out << "listedmenu::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _title << "::"
		<< _description << "::"
		<< Tools::ConvertIntToStr(_useCounter) << "::"
		<< Tools::ConvertIntToStr(_rating) << ";";

	return out.str();
}

std::string ListedMenuDto::ToString()
{
	std::string str =
		std::string("ListedMenuDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; title: ") + _title
		+ std::string("; description: ") + _description
		+ std::string("; useCounter: ") + Tools::ConvertIntToStr(_useCounter)
		+ std::string("; rating: ") + Tools::ConvertIntToStr(_rating)
		+ std::string(" }");
	return str;
}
