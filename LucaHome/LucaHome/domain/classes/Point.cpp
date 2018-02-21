#include "Point.h"

Point::Point()
{
	Point(0, 0);
}

Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

Point::~Point()
{
}

int Point::GetX()
{
	return _x;
}

int Point::GetY()
{
	return _y;
}

string Point::JsonString()
{
	string str =
		string("{")
		+ string("\"Point\":")
		+ string("{")
		+ string("\"X\":") + Tools::ConvertIntToStr(_x) + string(",")
		+ string("\"Y\":") + Tools::ConvertIntToStr(_y)
		+ string("}")
		+ string("}");
	return str;
}

string Point::ToString()
{
	string str =
		string("Point { ")
		+ string("; X: ") + Tools::ConvertIntToStr(_x)
		+ string("; Y: ") + Tools::ConvertIntToStr(_y)
		+ string(" }");
	return str;
}
