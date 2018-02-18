#include "ITemplateDatabase.h"
#include "../../domain/classes/Room.h";

using namespace std;

#ifndef ROOM_DATABASE_H
#define ROOM_DATABASE_H

class RoomDatabase : public ITemplateDatabase<Room>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseRoomListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyType = "_type";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	RoomDatabase();
	RoomDatabase(string);
	~RoomDatabase();

	virtual char Dispose();

	virtual vector<Room> GetList();

	virtual char Insert(int, Room);
	virtual char Update(Room);
	virtual char Delete(string);
};

#endif
