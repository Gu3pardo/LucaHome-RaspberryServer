#include "PointDto.h"

PointDto::PointDto()
{
	_x = -1;
	_y = -1;
}

PointDto::PointDto(int x, int y)
{
	_x = x;
	_y = y;
}

PointDto::~PointDto()
{
}

int PointDto::GetX()
{
	return _x;
}

int PointDto::GetY()
{
	return _y;
}

std::string PointDto::SaveString()
{
	std::string str = Tools::ConvertIntToStr(_x) + "|" + Tools::ConvertIntToStr(_y);
	return str;
}

std::string PointDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Point\":")
		+ std::string("{")
		+ std::string("\"X\":") + Tools::ConvertIntToStr(_x) + std::string(",")
		+ std::string("\"Y\":") + Tools::ConvertIntToStr(_y)
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string PointDto::ToString()
{
	std::string str =
		std::string("PointDto { ")
		+ std::string("; X: ") + Tools::ConvertIntToStr(_x)
		+ std::string("; Y: ") + Tools::ConvertIntToStr(_y)
		+ std::string(" }");
	return str;
}
