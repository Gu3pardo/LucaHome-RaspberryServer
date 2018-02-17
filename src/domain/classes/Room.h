#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
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

public:
	Room();
	Room(string, string, int);
	~Room();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetType(int);
	int GetType();

	string JsonString();
	string ToString();
};

#endif
