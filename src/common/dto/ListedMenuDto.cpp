#include "ListedMenuDto.h"

ListedMenuDto::ListedMenuDto()
{
	_id = -1;
	_description = "N.A.";
	_rating = 0;
	_lastSuggestion = 0;
}

ListedMenuDto::ListedMenuDto(int id, std::string description, int rating, int lastSuggestion)
{
	_id = id;
	_description = description;
	_rating = rating;
	_lastSuggestion = lastSuggestion;
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

void ListedMenuDto::SetDescription(std::string description)
{
	_description = description;
}

std::string ListedMenuDto::GetDescription()
{
	return _description;
}

void ListedMenuDto::SetRating(int rating)
{
	_rating = rating;
}

int ListedMenuDto::GetRating()
{
	return _rating;
}

void ListedMenuDto::SetLastSuggestion(int lastSuggestion)
{
	_lastSuggestion = lastSuggestion;
}

int ListedMenuDto::IsLastSuggestion()
{
	return _lastSuggestion;
}

std::string ListedMenuDto::ToString()
{
	std::string str =
		std::string("ListedMenuDto { id: ") + Tools::ConvertIntToStr(_id) 
		+ std::string("; description: ") + _description 
		+ std::string("; rating: ") + Tools::ConvertIntToStr(_rating)
		+ std::string("; isLastSuggestion: ") + Tools::ConvertIntToStr(_lastSuggestion)
		+ std::string(" }");
	return str;
}
