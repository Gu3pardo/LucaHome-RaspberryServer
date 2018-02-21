#include <string>
#include <cstring>
#include <iostream>
#include "Point.h"
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef MAPCONTENT_H
#define MAPCONTENT_H

class MapContent {

private:
	string _uuid;
	string _typeUuid;
	string _type;
	Point _position;
	string _name;
	string _shortName;
	bool _visibility;

public:
	MapContent();
	MapContent(string, string, string, Point, string, string, bool);
	~MapContent();

	string GetUuid();
	string GetTypeUuid();
	string GetType();
	Point GetPosition();
	string GetName();
	string GetShortName();
	bool GetVisibility();

	string JsonString();
	string ToString();
};

#endif
