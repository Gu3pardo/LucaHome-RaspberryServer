#include "WirelessSocketDatabase.h"

WirelessSocketDatabase::WirelessSocketDatabase() {}

WirelessSocketDatabase::WirelessSocketDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

WirelessSocketDatabase::~WirelessSocketDatabase()
{
	close();
}

char WirelessSocketDatabase::Dispose()
{
	return close();
}

vector<WirelessSocket> WirelessSocketDatabase::GetList()
{
	vector<WirelessSocket> list;
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
		string roomUuid = sqlite3_column_text(res, 2);
		string name = sqlite3_column_text(res, 3);
		string code = sqlite3_column_text(res, 4);
		bool state = sqlite3_column_int(res, 5) == 1;

		WirelessSocket newEntry(uuid, roomUuid, name, code, state);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char WirelessSocketDatabase::Insert(int rowId, WirelessSocket entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyRoomUuid + " ,"
		+ _keyName + " ,"
		+ _keyCode + " ,"
		+ _keyState + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetCode() + "',"
		+ Tools::ConvertBoolToStr(entry.GetState())
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

char WirelessSocketDatabase::Update(WirelessSocket entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyRoomUuid + " = '" + entry.GetRoomUuid() + "',"
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyCode + " = '" + entry.GetCode() + "',"
		+ "SET " + _keyState + " = " + Tools::ConvertBoolToStr(entry.GetState())
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

char WirelessSocketDatabase::Delete(WirelessSocket entry)
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

char WirelessSocketDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char WirelessSocketDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyRoomUuid + " TEXT NOT NULL,"
		+ _keyName + " TEXT NOT NULL,"
		+ _keyCode + " TEXT NOT NULL,"
		+ _keyState + " INT NOT NULL);";

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

char WirelessSocketDatabase::close()
{
	sqlite3_close(database);
	return 0;
}