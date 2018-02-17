#include "Position.h"

Position::Position()
{
	_x = 0;
	_y = 0;
}

Position::Position(int x, int y)
{
	_x = x;
	_y = y;
}

Position::~Position()
{
}

int Position::GetX()
{
	return _x;
}

int Position::GetY()
{
	return _y;
}

string Position::JsonString()
{
	string str =
		string("{")
		+ string("\"Position\":")
		+ string("{")
		+ string("\"X\":") + Tools::ConvertIntToStr(_x) + string(",")
		+ string("\"Y\":") + Tools::ConvertIntToStr(_y)
		+ string("}")
		+ string("}");
	return str;
}

string Position::ToString()
{
	string str =
		string("Position { ")
		+ string("; X: ") + Tools::ConvertIntToStr(_x)
		+ string("; Y: ") + Tools::ConvertIntToStr(_y)
		+ string(" }");
	return str;
}
