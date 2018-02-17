#include "RssFeedDatabase.h"

RssFeedDatabase::RssFeedDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

RssFeedDatabase::~RssFeedDatabase()
{
	close();
}

char RssFeedDatabase::Dispose()
{
	return close();
}

vector<RssFeed> RssFeedDatabase::GetList()
{
	vector<RssFeed> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyRowId;

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
		string title = sqlite3_column_text(res, 2);
		string url = sqlite3_column_text(res, 3);
		int playCount = sqlite3_column_int(res, 4);

		RssFeed newEntry(uuid, title, url, playCount);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char RssFeedDatabase::Insert(int rowId, RssFeed entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyTitle + " ,"
		+ _keyUrl + " ,"
		+ _keyPlayCount + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTitle() + "',"
		+ "'" + entry.GetUrl() + "',"
		+ Tools::ConvertIntToStr(entry.GetPlayCount())
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

char RssFeedDatabase::Update(RssFeed entry)
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
	int error = sqlite3_exec(database, sqlUpdateCommand, NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char RssFeedDatabase::Delete(RssFeed entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlDeleteCommand =
		"DELETE FROM " + _tableName + " "
		+ "WHERE " + _keyUuid + "=" + entry.GetUuid() + ";";

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

char RssFeedDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char RssFeedDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTitle + " TEXT NOT NULL,"
		+ _keyUrl + " TEXT NOT NULL,"
		+ _keyPlayCount + " INT NOT NULL);";

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

char RssFeedDatabase::close()
{
	sqlite3_close(database);
	return 0;
}