#include "ITemplateDatabase.h"
#include "../../domain/classes/User.h";

using namespace std;

#ifndef USER_DATABASE_H
#define USER_DATABASE_H

class UserDatabase : public ITemplateDatabase<User>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseUserListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyPassPhrase = "_passphrase";
	string _keyRole = "_role";
	string _keyIsAdmin = "_isAdmin";
	string _keyInvalidLoginCount = "_invalidLoginCount";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	UserDatabase();
	UserDatabase(string);
	~UserDatabase();

	virtual char Dispose();

	virtual vector<User> GetList();

	virtual char Insert(int, User);
	virtual char Update(User);
	virtual char Delete(string);
};

#endif
