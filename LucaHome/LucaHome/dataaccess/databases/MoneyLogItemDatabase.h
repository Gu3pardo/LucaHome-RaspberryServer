#include "ITemplateDatabase.h"
#include "../../domain/classes/MoneyLogItem.h";

using namespace std;

#ifndef MONEY_LOG_ITEM_DATABASE_H
#define MONEY_LOG_ITEM_DATABASE_H

class MoneyLogItemDatabase : public ITemplateDatabase<MoneyLogItem>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseMoneyLogItemListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTypeUuid = "_typeUuid";
	string _keyBank = "_bank";
	string _keyPlan = "_plan";
	string _keyAmount = "_amount";
	string _keyUnit = "_unit";
	string _keyDay = "_day";
	string _keyMonth = "_month";
	string _keyYear = "_year";
	string _keyUser = "_user";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	MoneyLogItemDatabase();
	MoneyLogItemDatabase(string);
	~MoneyLogItemDatabase();

	virtual char Dispose();

	virtual vector<MoneyLogItem> GetList();

	virtual char Insert(int, MoneyLogItem);
	virtual char Update(MoneyLogItem);
	virtual char Delete(string);
};

#endif
