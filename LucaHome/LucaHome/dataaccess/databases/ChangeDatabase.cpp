#include "ChangeDatabase.h"

ChangeDatabase::ChangeDatabase() {}

ChangeDatabase::ChangeDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

ChangeDatabase::~ChangeDatabase()
{
	close();
}

char ChangeDatabase::Dispose()
{
	return close();
}

vector<Change> ChangeDatabase::GetList()
{
	vector<Change> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM '" + _tableName + "' ORDER BY '" + _keyType + "';";

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
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string userName = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		time_t changeTime = sqlite3_column_int(res, 4);

		Change newEntry(uuid, type, userName, changeTime);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char ChangeDatabase::Insert(int rowId, Change entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO '" + _tableName + "' ("
		+ "'" + _keyRowId + "' ,"
		+ "'" + _keyUuid + "' ,"
		+ "'" + _keyType + "' ,"
		+ "'" + _keyUserName + "' ,"
		+ "'" + _keyTime + "' ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ "'" + entry.GetUserName() + "',"
		+ Tools::ConvertIntToStr(entry.GetTime())
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

char ChangeDatabase::Update(Change entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE '" + _tableName + "' "
		+ "SET '" + _keyType + "' = '" + entry.GetType() + "',"
		+ "SET '" + _keyUserName + "' = '" + entry.GetUserName() + "',"
		+ "SET '" + _keyTime + "' = " + Tools::ConvertIntToStr(entry.GetTime()) + " "
		+ "WHERE '" + _keyUuid + "'='" + entry.GetUuid() + "';";

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

char ChangeDatabase::Delete(string uuid)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlDeleteCommand =
		"DELETE FROM '" + _tableName + "' "
		+ "WHERE '" + _keyUuid + "'='" + uuid + "';";

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

char ChangeDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char ChangeDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE '" + _tableName + "'("
		+ "'" + _keyRowId + "' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ "'" + _keyUuid + "' TEXT NOT NULL,"
		+ "'" + _keyType + "' TEXT NOT NULL,"
		+ "'" + _keyUserName + "' TEXT NOT NULL,"
		+ "'" + _keyTime + "' INTEGER NOT NULL);";

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

char ChangeDatabase::close()
{
	sqlite3_close(database);
	return 0;
}