#include "ITemplateDatabase.h"
#include "../../domain/classes/Gpio.h"

using namespace std;

#ifndef GPIO_DATABASE_H
#define GPIO_DATABASE_H

class GpioDatabase : public ITemplateDatabase<Gpio>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseGpioListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyPin = "_pin";
	string _keyState = "_state";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	GpioDatabase();
	GpioDatabase(string);
	~GpioDatabase();

	virtual char Dispose();

	virtual vector<Gpio> GetList();
	virtual Gpio GetByUuid(string);

	virtual char Insert(int, Gpio);
	virtual char Update(Gpio);
	virtual char UpdateState(string, bool);
	virtual char Delete(string);
};

#endif
