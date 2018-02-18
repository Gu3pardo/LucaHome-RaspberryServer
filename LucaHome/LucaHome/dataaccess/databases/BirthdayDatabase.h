#include "ITemplateDatabase.h"
#include "../../domain/classes/Birthday.h";

using namespace std;

#ifndef BIRTHDAY_DATABASE_H
#define BIRTHDAY_DATABASE_H

class BirthdayDatabase : public ITemplateDatabase<Birthday>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseBirthdayListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyBirthdayDay = "_birthdayDay";
	string _keyBirthdayMonth = "_birthdayMonth";
	string _keyBirthdayYear = "_birthdayYear";
	string _keyGroup = "_group";
	string _keyRemindMe = "_remindMe";
	string _keySentMail = "_sentMail";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	BirthdayDatabase();
	BirthdayDatabase(string);
	~BirthdayDatabase();

	virtual char Dispose();

	virtual vector<Birthday> GetList();

	virtual char Insert(int, Birthday);
	virtual char Update(Birthday);
	virtual char Delete(string);
};

#endif
