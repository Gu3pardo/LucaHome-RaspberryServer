#include "ITemplateDatabase.h"
#include "../../domain/classes/RadioStream.h"

using namespace std;

#ifndef RADIO_STREAM_DATABASE_H
#define RADIO_STREAM_DATABASE_H

class RadioStreamDatabase : public ITemplateDatabase<RadioStream>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseRadioStreamListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTitle = "_title";
	string _keyUrl = "_url";
	string _keyPlayCount = "_playCount";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	RadioStreamDatabase();
	RadioStreamDatabase(string);
	~RadioStreamDatabase();

	virtual char Dispose();

	virtual vector<RadioStream> GetList();

	virtual char Insert(RadioStream);
	virtual char Update(RadioStream);
	virtual char Delete(string);
};

#endif
