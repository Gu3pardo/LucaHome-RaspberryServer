#include "ITemplateDatabase.h"
#include "../../domain/classes/ApplicationInformation.h";

using namespace std;

#ifndef APPLICATION_INFORMATION_DATABASE_H
#define APPLICATION_INFORMATION_DATABASE_H

class ApplicationInformationDatabase : public ITemplateDatabase<ApplicationInformation>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseApplicationInformationListTable";
	string _keyRowId = "_rowId";
	string _keyKey = "_key";
	string _keyValue = "_value";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	ApplicationInformationDatabase();
	ApplicationInformationDatabase(string);
	~ApplicationInformationDatabase();

	virtual char Dispose();

	virtual vector<ApplicationInformation> GetList();

	virtual char Insert(int, ApplicationInformation);
	virtual char Update(ApplicationInformation);
	virtual char Delete(string);
};

#endif
