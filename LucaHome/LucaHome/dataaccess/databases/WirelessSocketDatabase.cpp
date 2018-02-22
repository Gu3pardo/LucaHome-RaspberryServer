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
		string roomUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string code = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		bool state = sqlite3_column_int(res, 5) == 1;

		WirelessSocket newEntry(uuid, roomUuid, name, code, state);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

WirelessSocket WirelessSocketDatabase::GetByUuid(string uuid)
{
	if (!open()) {
		return WirelessSocket();
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + "WHERE " + _keyUuid + "=" + uuid + " LIMIT 1;";

	sqlite3_stmt *res;
	char *errorMessage = 0;

	int error = sqlite3_exec(database, sqlSelectCommand.c_str(), NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return WirelessSocket();
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
		string roomUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string code = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		bool state = sqlite3_column_int(res, 5) == 1;

		WirelessSocket wirelessSocket(uuid, roomUuid, name, code, state);
		sqlite3_finalize(res);
		close();

		return wirelessSocket;
	}

	sqlite3_finalize(res);
	close();
	return WirelessSocket();
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
	int error = sqlite3_exec(database, sqlInsertCommand.c_str(), NULL, NULL, &errorMessage);
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

char WirelessSocketDatabase::UpdateState(string uuid, bool newState)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyState + " = " + Tools::ConvertBoolToStr(newState) + ","
		+ "WHERE " + _keyUuid + "=" + uuid + ";";

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

char WirelessSocketDatabase::Delete(string uuid)
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

char WirelessSocketDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
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
	int error = sqlite3_exec(database, sqlCreateCommand.c_str(), NULL, NULL, &errorMessage);
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