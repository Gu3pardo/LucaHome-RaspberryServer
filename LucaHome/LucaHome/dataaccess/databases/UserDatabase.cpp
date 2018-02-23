#include "UserDatabase.h"

UserDatabase::UserDatabase() {}

UserDatabase::UserDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

UserDatabase::~UserDatabase()
{
	close();
}

char UserDatabase::Dispose()
{
	return close();
}

vector<User> UserDatabase::GetList()
{
	vector<User> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyRowId + ";";

	sqlite3_stmt *res;
	char *errorMessage = 0;

	int error = sqlite3_exec(database, sqlSelectCommand.c_str(), NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return list;
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string passphrase = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int role = sqlite3_column_int(res, 4);
		bool isAdmin = sqlite3_column_int(res, 5) == 1;
		int invalidLoginCount = sqlite3_column_int(res, 6);

		User newEntry(uuid, name, passphrase, role, isAdmin, invalidLoginCount);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char UserDatabase::Insert(User entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyName + " ,"
		+ _keyPassPhrase + " ,"
		+ _keyRole + " ,"
		+ _keyIsAdmin + " ,"
		+ _keyInvalidLoginCount + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetPassphrase() + "',"
		+ Tools::ConvertIntToStr(entry.GetRole()) + ","
		+ Tools::ConvertBoolToStr(entry.IsAdmin()) + ","
		+ Tools::ConvertIntToStr(entry.GetInvalidLoginCount())
		+ ");";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlInsertCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char UserDatabase::Update(User entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyPassPhrase + " = '" + entry.GetPassphrase() + "',"
		+ "SET " + _keyRole + " = " + Tools::ConvertIntToStr(entry.GetRole()) + ","
		+ "SET " + _keyIsAdmin + " = " + Tools::ConvertBoolToStr(entry.IsAdmin()) + ","
		+ "SET " + _keyInvalidLoginCount + " = " + Tools::ConvertIntToStr(entry.GetInvalidLoginCount()) + " "
		+ "WHERE " + _keyUuid + "=" + entry.GetUuid() + ";";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlUpdateCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char UserDatabase::Delete(string uuid)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlDeleteCommand =
		"DELETE FROM " + _tableName + " "
		+ "WHERE " + _keyUuid + "=" + uuid + ";";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlDeleteCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char UserDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char UserDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyName + " TEXT NOT NULL,"
		+ _keyPassPhrase + " TEXT NOT NULL,"
		+ _keyRole + " INTEGER NOT NULL,"
		+ _keyIsAdmin + " INTEGER NOT NULL,"
		+ _keyInvalidLoginCount + " INTEGER NOT NULL);";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlCreateCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char UserDatabase::close()
{
	sqlite3_close(database);
	return 0;
}