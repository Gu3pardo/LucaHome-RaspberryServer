#include "Room.h"

Room::Room()
{
	Room("", "", -1, vector<Point>());
}

Room::Room(string uuid, string name, int type)
{
	Room(uuid, name, type, vector<Point>());
}

Room::Room(string uuid, string name, int type, vector<Point> pointList)
{
	_uuid = uuid;
	_name = name;
	_type = type;
	_pointList = pointList;
}

Room::~Room()
{
}

void Room::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Room::GetUuid()
{
	return _uuid;
}

void Room::SetName(string name)
{
	_name = name;
}

string Room::GetName()
{
	return _name;
}

void Room::SetType(int type)
{
	_type = type;
}

int Room::GetType()
{
	return _type;
}

void Room::SetPointList(vector<Point> pointList)
{
	_pointList = pointList;
}

vector<Point> Room::GetPointList()
{
	return _pointList;
}

string Room::GetPointDbString()
{
	stringstream data;
	for (int index = 0; index < _pointList.size(); index++)
	{
		data << Tools::ConvertIntToStr(_pointList[index].GetX()) << "--" << Tools::ConvertIntToStr(_pointList[index].GetX()) << ",,";
	}
	return data.str().substr(0, data.str().size() - 1);
}

void Room::ParsePointDbString(string pointDbString)
{
	vector<Point> pointList;

	vector<string> stringList = Tools::Explode(pointDbString, ",,");
	for (int index = 0; index < stringList.size(); index++)
	{
		string dataString = stringList[index];

		vector<string> data = Tools::Explode(dataString, "--");
		if (data.size() != 2) {
			continue;
		}

		int x = Tools::ConvertStrToInt(data[0]);
		int y = Tools::ConvertStrToInt(data[1]);

		Point Point(x, y);
		pointList.push_back(Point);
	}

	_pointList = pointList;
}

string Room::JsonString()
{
	string str =
		string("{")
		+ string("\"Room\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Type\":") + Tools::ConvertIntToStr(_type) + string(",")
		+ string("\"PointList\":") + pointJsonString()
		+ string("}")
		+ string("}");
	return str;
}

string Room::ToString()
{
	string str = string("Room { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; type: ") + Tools::ConvertIntToStr(_type)
		+ string(" }");
	return str;
}

string Room::pointJsonString()
{
	stringstream data;
	for (int index = 0; index < _pointList.size(); index++)
	{
		string pointJsonString =
			string("{")
			+ string("\"Point\":")
			+ string("{")
			+ string("\"X\":") + Tools::ConvertIntToStr(_pointList[index].GetX()) + string(",")
			+ string("\"Y\":") + Tools::ConvertIntToStr(_pointList[index].GetY()) + string("")
			+ string("}")
			+ string("}");
		data << pointJsonString << ",";
	}

	stringstream out;
	out << "[" << data.str().substr(0, data.str().size() - 1) << "]";
	return out.str();
}