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

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyType;

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
		string type = sqlite3_column_text(res, 2);
		string userName = sqlite3_column_text(res, 3);
		int hour = sqlite3_column_int(res, 4);
		int minute = sqlite3_column_int(res, 5);
		int day = sqlite3_column_int(res, 6);
		int month = sqlite3_column_int(res, 7);
		int year = sqlite3_column_int(res, 8);

		Change newEntry(uuid, type, userName, hour, minute, day, month, year);
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
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyType + " ,"
		+ _keyUserName + " ,"
		+ _keyHour + " ,"
		+ _keyMinute + " ,"
		+ _keyDay + " ,"
		+ _keyMonth + " ,"
		+ _keyYear + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ "'" + entry.GetUserName() + "',"
		+ Tools::ConvertIntToStr(entry.GetHour()) + ", "
		+ Tools::ConvertIntToStr(entry.GetMinute()) + ", "
		+ Tools::ConvertIntToStr(entry.GetDay()) + ", "
		+ Tools::ConvertIntToStr(entry.GetMonth()) + ", "
		+ Tools::ConvertIntToStr(entry.GetYear())
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

char ChangeDatabase::Update(Change entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyType + " = '" + entry.GetType() + "',"
		+ "SET " + _keyUserName + " = '" + entry.GetUserName() + "',"
		+ "SET " + _keyHour + " = " + Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ "SET " + _keyMinute + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyDay + " = " + Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "SET " + _keyMonth + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyYear + " = " + Tools::ConvertIntToStr(entry.GetYear()) + " "
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

char ChangeDatabase::Delete(Change entry)
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

char ChangeDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char ChangeDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyType + " TEXT NOT NULL,"
		+ _keyUserName + " TEXT NOT NULL,"
		+ _keyHour + " INT NOT NULL,"
		+ _keyMinute + " INT NOT NULL,"
		+ _keyDay + " INT NOT NULL,"
		+ _keyMonth + " INT NOT NULL,"
		+ _keyYear + " INT NOT NULL);";

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

char ChangeDatabase::close()
{
	sqlite3_close(database);
	return 0;
}