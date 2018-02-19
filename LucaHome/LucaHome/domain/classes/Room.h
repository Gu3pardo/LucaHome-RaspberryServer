#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"
#include "Polyline.h"

using namespace std;

#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
	string _uuid;
	string _name;
	int _type;
	vector<Polyline> _polylineList;

	string polylineJsonString();

public:
	Room();
	Room(string, string, int);
	Room(string, string, int, vector<Polyline>);
	~Room();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetType(int);
	int GetType();

	void SetPolylineList(vector<Polyline>);
	vector<Polyline> GetPolylineList();
	string GetPolylineDbString();
	void ParsePolylineDbString(string);

	string JsonString();
	string ToString();
};

#endif
