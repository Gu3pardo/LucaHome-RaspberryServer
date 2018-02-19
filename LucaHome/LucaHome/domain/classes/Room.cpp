#include "Room.h"

Room::Room()
{
	Room("", "", -1, vector<Polyline>());
}

Room::Room(string uuid, string name, int type)
{
	Room(uuid, name, type, vector<Polyline>());
}

Room::Room(string uuid, string name, int type, vector<Polyline> polylineList)
{
	_uuid = uuid;
	_name = name;
	_type = type;
	_polylineList = polylineList;
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

void Room::SetPolylineList(vector<Polyline> polylineList)
{
	_polylineList = polylineList;
}

vector<Polyline> Room::GetPolylineList()
{
	return _polylineList;
}

string Room::GetPolylineDbString()
{
	stringstream data;
	for (int index = 0; index < _polylineList.size(); index++)
	{
		data << Tools::ConvertIntToStr(_polylineList[index].GetX()) << "--" << Tools::ConvertIntToStr(_polylineList[index].GetX()) << ",,";
	}
	return data.str().substr(0, data.str().size() - 1);
}

void Room::ParsePolylineDbString(string polylineDbString)
{
	vector<Polyline> polylineList;

	vector<string> stringList = Tools::Explode(polylineDbString, ",,");
	for (int index = 0; index < stringList.size(); index++)
	{
		string dataString = stringList[index];

		vector<string> data = Tools::Explode(dataString, "--");
		if (data.size() != 2) {
			continue;
		}

		int x = Tools::ConvertStrToInt(data[0]);
		int y = Tools::ConvertStrToInt(data[1]);

		Polyline polyline(x, y);
		polylineList.push_back(polyline);
	}

	_polylineList = polylineList;
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
		+ string("\"PolylineList\":") + polylineJsonString()
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

string Room::polylineJsonString()
{
	stringstream data;
	for (int index = 0; index < _polylineList.size(); index++)
	{
		string polylineJsonString =
			string("{")
			+ string("\"Polyline\":")
			+ string("{")
			+ string("\"X\":") + Tools::ConvertIntToStr(_polylineList[index].GetX()) + string(",")
			+ string("\"Y\":") + Tools::ConvertIntToStr(_polylineList[index].GetY()) + string("")
			+ string("}")
			+ string("}");
		data << polylineJsonString << ",";
	}

	stringstream out;
	out << "[" << data.str().substr(0, data.str().size() - 1) << "]";
	return out.str();
}