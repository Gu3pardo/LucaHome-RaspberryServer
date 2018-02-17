#include "ITemplateDatabase.h"
#include "../../domain/classes/PuckJs.h";

using namespace std;

#ifndef PUCK_JS_DATABASE_H
#define PUCK_JS_DATABASE_H

class PuckJsDatabase : public ITemplateDatabase<PuckJs>
{
protected:
	string _databaseName;
	string _tableName = "DatabasePuckJsListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyRoomUuid = "_roomUuid";
	string _keyName = "_name";
	string _keyMac = "_mac";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	PuckJsDatabase(string);
	~PuckJsDatabase();

	virtual char Dispose();

	virtual vector<PuckJs> GetList();

	virtual char Insert(int, PuckJs);
	virtual char Update(PuckJs);
	virtual char Delete(PuckJs);
};

#endif
