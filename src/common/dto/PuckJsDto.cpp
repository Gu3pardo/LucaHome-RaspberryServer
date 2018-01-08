#include "PuckJsDto.h"

PuckJsDto::PuckJsDto()
{
	_id = 0;
	_name = "";
	_area = "";
	_mac = "";
}

PuckJsDto::PuckJsDto(int id, std::string name, std::string area, std::string mac)
{
	_id = id;
	_name = name;
	_area = area;
	_mac = mac;
}

PuckJsDto::~PuckJsDto()
{
}

void PuckJsDto::SetId(int id)
{
	_id = id;
}

int PuckJsDto::GetId()
{
	return _id;
}

void PuckJsDto::SetName(std::string name)
{
	_name = name;
}

std::string PuckJsDto::GetName()
{
	return _name;
}

void PuckJsDto::SetArea(std::string area)
{
	_area = area;
}

std::string PuckJsDto::GetArea()
{
	return _area;
}

void PuckJsDto::SetMac(std::string mac)
{
	_mac = mac;
}

std::string PuckJsDto::GetMac()
{
	return _mac;
}

std::string PuckJsDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + "::"
		+ _name + "::"
		+ _area + "::"
		+ _mac + ";";

	return str;
}

std::string PuckJsDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"PuckJs\":")
		+ std::string("{")
		+ std::string("\"Id\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Name\":\"") + _name + std::string("\",")
		+ std::string("\"Area\":\"") + _area + std::string("\",")
		+ std::string("\"Mac\":\"") + _mac + std::string("\"")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string PuckJsDto::PhpString()
{
	std::stringstream out;

	out << "puckjs::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _name << "::"
		<< _area << "::"
		<< _mac << ";";

	return out.str();
}

std::string PuckJsDto::ToString()
{
	std::string str = std::string("PuckJsDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; name: ") + _name
		+ std::string("; area: ") + _area
		+ std::string("; mac: ") + _mac
		+ std::string(" }");
	return str;
}
