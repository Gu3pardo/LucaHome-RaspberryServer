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

std::string ShoppingEntryDto::SaveString()
{
	std::string str = 
		Tools::ConvertIntToStr(_id) + ":"
		+ _name + ":"
		+ _group + ":"
		+ Tools::ConvertIntToStr(_quantity) + ";";
	return str;
}

std::string ShoppingEntryDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"ShoppingEntry\":")
		+ std::string("{")
		+ std::string("\"ID\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Name\":") + _name + std::string(",")
		+ std::string("\"Group\":") + _group + std::string(",")
		+ std::string("\"Quantity\":") + Tools::ConvertIntToStr(_quantity)
		+ std::string("}")
		+ std::string("}");
	return str;
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
