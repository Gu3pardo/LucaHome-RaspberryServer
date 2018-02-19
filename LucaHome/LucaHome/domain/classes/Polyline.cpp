#include "Polyline.h"

Polyline::Polyline()
{
	Polyline(0, 0);
}

Polyline::Polyline(int x, int y)
{
	_x = x;
	_y = y;
}

Polyline::~Polyline()
{
}

int Polyline::GetX()
{
	return _x;
}

int Polyline::GetY()
{
	return _y;
}

string Polyline::JsonString()
{
	string str =
		string("{")
		+ string("\"Polyline\":")
		+ string("{")
		+ string("\"X\":") + Tools::ConvertIntToStr(_x) + string(",")
		+ string("\"Y\":") + Tools::ConvertIntToStr(_y)
		+ string("}")
		+ string("}");
	return str;
}

string Polyline::ToString()
{
	string str =
		string("Polyline { ")
		+ string("; X: ") + Tools::ConvertIntToStr(_x)
		+ string("; Y: ") + Tools::ConvertIntToStr(_y)
		+ string(" }");
	return str;
}
