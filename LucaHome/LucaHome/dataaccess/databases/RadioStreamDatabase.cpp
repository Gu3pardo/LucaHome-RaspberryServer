#include "RadioStreamDatabase.h"

RadioStreamDatabase::RadioStreamDatabase() {}

RadioStreamDatabase::RadioStreamDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

RadioStreamDatabase::~RadioStreamDatabase()
{
	close();
}

char RadioStreamDatabase::Dispose()
{
	return close();
}

vector<RadioStream> RadioStreamDatabase::GetList()
{
	vector<RadioStream> list;
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
		string title = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string url = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int playCount = sqlite3_column_int(res, 4);

		RadioStream newEntry(uuid, title, url, playCount);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char RadioStreamDatabase::Insert(RadioStream entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyTitle + " ,"
		+ _keyUrl + " ,"
		+ _keyPlayCount + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTitle() + "',"
		+ "'" + entry.GetUrl() + "',"
		+ Tools::ConvertIntToStr(entry.GetPlayCount())
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

char RadioStreamDatabase::Update(RadioStream entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTitle + " = '" + entry.GetTitle() + "',"
		+ "SET " + _keyUrl + " = '" + entry.GetUrl() + "',"
		+ "SET " + _keyPlayCount + " = " + Tools::ConvertIntToStr(entry.GetPlayCount()) + " "
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

char RadioStreamDatabase::Delete(string uuid)
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

char RadioStreamDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char RadioStreamDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTitle + " TEXT NOT NULL,"
		+ _keyUrl + " TEXT NOT NULL,"
		+ _keyPlayCount + " INTEGER NOT NULL);";

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

char RadioStreamDatabase::close()
{
	sqlite3_close(database);
	return 0;
}