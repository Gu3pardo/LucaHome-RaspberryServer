#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/databases/RoomDatabase.h"
#include "../../domain/classes/Room.h"

using namespace std;

#ifndef ROOM_SERVICE_H
#define ROOM_SERVICE_H

class RoomService
{
private:
	RoomDatabase _roomDatabase;

	string getJsonString();

	char addRoom(vector<string>);
	char updateRoom(vector<string>);
	char deleteRoom(string);

public:
	RoomService();
	~RoomService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();
};

#endif
