#include "ITemplateDatabase.h"
#include "../../domain/classes/MeterLogItem.h"

using namespace std;

#ifndef METER_LOG_ITEM_DATABASE_H
#define METER_LOG_ITEM_DATABASE_H

class MeterLogItemDatabase : public ITemplateDatabase<MeterLogItem>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseMeterLogItemListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyRoomUuid = "_roomUuid";
	string _keyTypeUuid = "_typeUuid";
	string _keyType = "_type";
	string _keyMeterId = "_meterId";
	string _keyValue = "_value";
	string _keyImageName = "_imageName";
	string _keySaveDateTime = "_saveDateTime";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	MeterLogItemDatabase();
	MeterLogItemDatabase(string);
	~MeterLogItemDatabase();

	virtual char Dispose();

	virtual vector<MeterLogItem> GetList();

	virtual char Insert(MeterLogItem);
	virtual char Update(MeterLogItem);
	virtual char Delete(string);
};

#endif
