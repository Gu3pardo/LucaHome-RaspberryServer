#include "ITemplateDatabase.h"
#include "../../domain/classes/Change.h"

using namespace std;

#ifndef CHANGE_DATABASE_H
#define CHANGE_DATABASE_H

class ChangeDatabase : public ITemplateDatabase<Change>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseChangeListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyType = "_type";
	string _keyUserName = "_userName";
	string _keyTime = "_time";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	ChangeDatabase();
	ChangeDatabase(string);
	~ChangeDatabase();

	virtual char Dispose();

	virtual vector<Change> GetList();

	virtual char Insert(int, Change);
	virtual char Update(Change);
	virtual char Delete(string);
};

#endif
