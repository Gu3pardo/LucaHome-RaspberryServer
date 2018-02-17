#include "WirelessScheduleDatabase.h"

WirelessScheduleDatabase::WirelessScheduleDatabase() {}

WirelessScheduleDatabase::WirelessScheduleDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

WirelessScheduleDatabase::~WirelessScheduleDatabase()
{
	close();
}

char WirelessScheduleDatabase::Dispose()
{
	return close();
}

vector<WirelessSchedule> WirelessScheduleDatabase::GetList()
{
	vector<WirelessSchedule> list;
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
		string name = sqlite3_column_text(res, 2);
		int weekday = sqlite3_column_int(res, 3);
		int hour = sqlite3_column_int(res, 4);
		int minute = sqlite3_column_int(res, 5);
		bool isActive = sqlite3_column_int(res, 6) == 1;
		string wirelessSocketUuid = sqlite3_column_text(res, 7);
		bool wirelessSocketAction = sqlite3_column_int(res, 8) == 1;
		string wirelessSwitchUuid = sqlite3_column_text(res, 9);

		WirelessSchedule newEntry(uuid, name, weekday, hour, minute, isActive, wirelessSocketUuid, wirelessSocketAction, wirelessSwitchUuid);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char WirelessScheduleDatabase::Insert(int rowId, WirelessSchedule entry)
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
		+ _keyWeekday + " ,"
		+ _keyHour + " ,"
		+ _keyMinute + " ,"
		+ _keyIsActive + " ,"
		+ _keyWirelessSocketUuid + " ,"
		+ _keyWirelessSocketAction + " ,"
		+ _keyWirelessSwitchUuid + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ Tools::ConvertIntToStr(entry.GetWeekday()) + ","
		+ Tools::ConvertIntToStr(entry.GetHour()) + ","
		+ Tools::ConvertIntToStr(entry.GetMinute()) + ","
		+ Tools::ConvertBoolToStr(entry.IsActive()) + ","
		+ "'" + entry.GetWirelessSocketUuid() + "',"
		+ Tools::ConvertBoolToStr(entry.GetWirelessSocketAction()) + ","
		+ "'" + entry.GetWirelessSwitchUuid() + "'"
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

char WirelessScheduleDatabase::Update(WirelessSchedule entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyWeekday + " = " + Tools::ConvertIntToStr(entry.GetWeekday()) + ","
		+ "SET " + _keyHour + " = " + Tools::ConvertIntToStr(entry.GetHour()) + ","
		+ "SET " + _keyMinute + " = " + Tools::ConvertIntToStr(entry.GetMinute()) + ","
		+ "SET " + _keyIsActive + " = " + Tools::ConvertBoolToStr(entry.IsActive()) + ","
		+ "SET " + _keyWirelessSocketUuid + " = '" + entry.GetWirelessSocketUuid() + "',"
		+ "SET " + _keyWirelessSocketAction + " = " + Tools::ConvertBoolToStr(entry.GetWirelessSocketAction()) + ","
		+ "SET " + _keyWirelessSwitchUuid + " = '" + entry.GetWirelessSwitchUuid() + "' "
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

char WirelessScheduleDatabase::Delete(WirelessSchedule entry)
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

char WirelessScheduleDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char WirelessScheduleDatabase::create()
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
		+ _keyWeekday + " INT NOT NULL,"
		+ _keyHour + " INT NOT NULL,"
		+ _keyMinute + " INT NOT NULL,"
		+ _keyIsActive + " INT NOT NULL,"
		+ _keyWirelessSocketUuid + " TEXT NOT NULL,"
		+ _keyWirelessSocketAction + " INT NOT NULL,"
		+ _keyWirelessSwitchUuid + " TEXT NOT NULL);";

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

char WirelessScheduleDatabase::close()
{
	sqlite3_close(database);
	return 0;
}