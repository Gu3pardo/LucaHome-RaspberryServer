#include "ShoppingEntryDto.h"

ShoppingEntryDto::ShoppingEntryDto()
{
	_id = 0;
	_name = "";
	_group = "";
	_quantity = 0;
	_unit = "";
}

ShoppingEntryDto::ShoppingEntryDto(int id, std::string name, std::string group, int quantity, std::string unit)
{
	_id = id;
	_name = name;
	_group = group;
	_quantity = quantity;
	_unit = unit;
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

void ShoppingEntryDto::SetUnit(std::string unit)
{
	_unit = unit;
}

std::string ShoppingEntryDto::GetUnit()
{
	return _unit;
}

std::string ShoppingEntryDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _name + ":"
		+ _group + ":"
		+ Tools::ConvertIntToStr(_quantity) + ":"
		+ _unit + ";";
	return str;
}

std::string ShoppingEntryDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"ShoppingEntry\":")
		+ std::string("{")
		+ std::string("\"Id\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Group\":\"") + _group + std::string("\",")
		+ std::string("\"Quantity\":") + Tools::ConvertIntToStr(_quantity) + std::string(",")
		+ std::string("\"Unit\":\"") + _unit + std::string("\"")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string ShoppingEntryDto::PhpString()
{
	std::stringstream out;

	out << "shopping_entry::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _name << "::"
		<< _group << "::"
		<< Tools::ConvertIntToStr(_quantity) << "::"
		<< _unit << ";";

	return out.str();
}

std::string ShoppingEntryDto::ToString()
{
	std::string str =
		std::string("ShoppingEntryDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; name: ") + _name
		+ std::string("; group: ") + _group
		+ std::string("; quantity: ") + Tools::ConvertIntToStr(_quantity)
		+ std::string("; unit: ") + _unit
		+ std::string(" }");
	return str;
}
