#include "ITemplateDatabase.h"
#include "../../domain/classes/MapContent.h"

using namespace std;

#ifndef MAPCONTENT_DATABASE_H
#define MAPCONTENT_DATABASE_H

class MapContentDatabase : public ITemplateDatabase<MapContent>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseMapContentListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTypeUuid = "_typeUuid";
	string _keyType = "_type";
	string _keyPositionX = "_positionX";
	string _keyPositionY = "_positionY";
	string _keyName = "_name";
	string _keyShortName = "_shortName";
	string _keyVisibility = "_visibility";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	MapContentDatabase();
	MapContentDatabase(string);
	~MapContentDatabase();

	virtual char Dispose();

	virtual vector<MapContent> GetList();

	virtual char Insert(int, MapContent);
	virtual char Update(MapContent);
	virtual char Delete(string);
};

#endif
