#include "ApplicationInformationDatabase.h"

ApplicationInformationDatabase::ApplicationInformationDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

ApplicationInformationDatabase::~ApplicationInformationDatabase()
{
	close();
}

char ApplicationInformationDatabase::Dispose()
{
	return close();
}

vector<ApplicationInformation> ApplicationInformationDatabase::GetList()
{
	vector<ApplicationInformation> list;
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
		string key = sqlite3_column_text(res, 1);
		string value = sqlite3_column_text(res, 2);

		ApplicationInformation newEntry(key, value);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char ApplicationInformationDatabase::Insert(int rowId, ApplicationInformation entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyKey + " ,"
		+ _keyValue + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetKey() + "',"
		+ "'" + entry.GetValue() + "'"
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

char ApplicationInformationDatabase::Update(ApplicationInformation entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyKey + " = '" + entry.GetKey() + "',"
		+ "SET " + _keyValue + " = '" + entry.GetValue() + "' "
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

char ApplicationInformationDatabase::Delete(ApplicationInformation entry)
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

char ApplicationInformationDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char ApplicationInformationDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyKey + " TEXT NOT NULL,"
		+ _keyValue + " TEXT NOT NULL);";

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

char ApplicationInformationDatabase::close()
{
	sqlite3_close(database);
	return 0;
}