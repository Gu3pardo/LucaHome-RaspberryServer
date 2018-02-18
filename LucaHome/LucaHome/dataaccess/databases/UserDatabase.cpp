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

	int error = sqlite3_exec(database, sqlSelectCommand, NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return list;
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = sqlite3_column_text(res, 1);
		string name = sqlite3_column_text(res, 2);
		string passphrase = sqlite3_column_text(res, 3);
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

char UserDatabase::Insert(int rowId, User entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyName + " ,"
		+ _keyPassPhrase + " ,"
		+ _keyRole + " ,"
		+ _keyIsAdmin + " ,"
		+ _keyInvalidLoginCount + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetPassphrase() + "',"
		+ Tools::ConvertIntToStr(entry.GetRole()) + ","
		+ Tools::ConvertBoolToStr(entry.IsAdmin()) + ","
		+ Tools::ConvertIntToStr(entry.GetInvalidLoginCount())
		+ ");";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlInsertCommand, NULL, NULL, &errorMessage);
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
	int error = sqlite3_exec(database, sqlUpdateCommand, NULL, NULL, &errorMessage);
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
	int error = sqlite3_exec(database, sqlDeleteCommand, NULL, NULL, &errorMessage);
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
	return sqlite3_open(_databaseName, &database);
}

char UserDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyName + " TEXT NOT NULL,"
		+ _keyPassPhrase + " TEXT NOT NULL,"
		+ _keyRole + " INT NOT NULL,"
		+ _keyIsAdmin + " INT NOT NULL,"
		+ _keyInvalidLoginCount + " INT NOT NULL);";

	char *errorMessage = 0;
	int error = sqlite3_exec(database, sqlCreateCommand, NULL, NULL, &errorMessage);
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