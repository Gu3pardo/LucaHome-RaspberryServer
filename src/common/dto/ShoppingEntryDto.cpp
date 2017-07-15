#include "ShoppingEntryDto.h"

ShoppingEntryDto::ShoppingEntryDto()
{
}

ShoppingEntryDto::ShoppingEntryDto(int id, std::string name, std::string group, int quantity)
{
	_id = id;
	_name = name;
	_group = group;
	_quantity = quantity;
}

ShoppingEntryDto::~ShoppingEntryDto()
{
}

void ShoppingEntryDto::SetId(int id)
{
	_id = id;
}

int ShoppingEntryDto::GetId()
{
	return _id;
}

void ShoppingEntryDto::SetName(std::string name)
{
	_name = name;
}

std::string ShoppingEntryDto::GetName()
{
	return _name;
}

void ShoppingEntryDto::SetGroup(std::string group)
{
	_group = group;
}

std::string ShoppingEntryDto::GetGroup()
{
	return _group;
}

void ShoppingEntryDto::SetQuantity(int quantity)
{
	_quantity = quantity;
}

void ShoppingEntryDto::IncreaseQuantity(int additionalQuantity)
{
	_quantity += additionalQuantity;
}

void ShoppingEntryDto::DecreaseQuantity(int removalQuantity)
{
	_quantity -= removalQuantity;
	if (_quantity < 1)
	{
		_quantity = 1;
	}
}

int ShoppingEntryDto::GetQuantity()
{
	return _quantity;
}

std::string ShoppingEntryDto::ToString()
{
	std::string str = 
		std::string("ShoppingEntryDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; name: ") + _name 
		+ std::string("; group: ") + _group 
		+ std::string("; quantity: ") + Tools::ConvertIntToStr(_quantity)
		+ std::string(" }");
	return str;
}
