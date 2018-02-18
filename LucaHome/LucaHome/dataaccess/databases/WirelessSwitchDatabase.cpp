#include "WirelessSwitchDatabase.h"

WirelessSwitchDatabase::WirelessSwitchDatabase() {}

WirelessSwitchDatabase::WirelessSwitchDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

WirelessSwitchDatabase::~WirelessSwitchDatabase()
{
	close();
}

char WirelessSwitchDatabase::Dispose()
{
	return close();
}

vector<WirelessSwitch> WirelessSwitchDatabase::GetList()
{
	vector<WirelessSwitch> list;
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
		string roomUuid = sqlite3_column_text(res, 2);
		string name = sqlite3_column_text(res, 3);
		int remoteId = sqlite3_column_int(res, 4);
		string keyCodeString = sqlite3_column_text(res, 5);
		bool action = sqlite3_column_int(res, 6) == 1;

		unsigned char keyCode = Tools::ConvertStrToUnsignedChar(keyCodeString);

		WirelessSwitch newEntry(uuid, roomUuid, name, remoteId, keyCode, action);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

WirelessSwitch WirelessSwitchDatabase::GetByUuid(string uuid)
{
	if (!open()) {
		return WirelessSwitch();
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + "WHERE " + _keyUuid + "=" + uuid + " LIMIT 1;";

	sqlite3_stmt *res;
	char *errorMessage = 0;

	int error = sqlite3_exec(database, sqlSelectCommand, NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return WirelessSwitch();
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = sqlite3_column_text(res, 1);
		string roomUuid = sqlite3_column_text(res, 2);
		string name = sqlite3_column_text(res, 3);
		int remoteId = sqlite3_column_int(res, 4);
		string keyCodeString = sqlite3_column_text(res, 5);
		bool action = sqlite3_column_int(res, 6) == 1;

		unsigned char keyCode = Tools::ConvertStrToUnsignedChar(keyCodeString);

		WirelessSwitch wirelessSwitch(uuid, roomUuid, name, remoteId, keyCode, action);
		sqlite3_finalize(res);
		close();

		return wirelessSwitch;
	}

	sqlite3_finalize(res);
	close();
	return WirelessSwitch();
}

char WirelessSwitchDatabase::Insert(int rowId, WirelessSwitch entry)
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
		+ _keyRemoteId + " ,"
		+ _keyKeyCode + " ,"
		+ _keyAction + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ Tools::ConvertIntToStr(entry.GetRemoteId()) + ","
		+ "'" + Tools::ConvertUnsignedCharToStr(entry.GetKeyCode()) + "',"
		+ Tools::ConvertBoolToStr(entry.GetAction())
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

char WirelessSwitchDatabase::Update(WirelessSwitch entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyRoomUuid + " = '" + entry.GetRoomUuid() + "',"
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyRemoteId + " = " + Tools::ConvertIntToStr(entry.GetRemoteId()) + ","
		+ "SET " + _keyKeyCode + " = '" + Tools::ConvertUnsignedCharToStr(entry.GetKeyCode()) + "',"
		+ "SET " + _keyAction + " = " + Tools::ConvertBoolToStr(entry.GetAction())
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

char WirelessSwitchDatabase::UpdateAction(string uuid, bool newAction)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyAction + " = " + Tools::ConvertBoolToStr(newAction) + ","
		+ "WHERE " + _keyUuid + "=" + uuid + ";";

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

char WirelessSwitchDatabase::Delete(string uuid)
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

char WirelessSwitchDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char WirelessSwitchDatabase::create()
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
		+ _keyRemoteId + " INT NOT NULL,"
		+ _keyKeyCode + " TEXT NOT NULL,"
		+ _keyAction + " INT NOT NULL);";

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

char WirelessSwitchDatabase::close()
{
	sqlite3_close(database);
	return 0;
}