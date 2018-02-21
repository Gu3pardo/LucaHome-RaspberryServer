#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "Point.h"
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
	string _uuid;
	string _name;
	int _type;
	vector<Point> _pointList;

	string pointJsonString();

public:
	Room();
	Room(string, string, int);
	Room(string, string, int, vector<Point>);
	~Room();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetType(int);
	int GetType();

	void SetPointList(vector<Point>);
	vector<Point> GetPointList();
	string GetPointDbString();
	void ParsePointDbString(string);

	string JsonString();
	string ToString();
};

#endif
