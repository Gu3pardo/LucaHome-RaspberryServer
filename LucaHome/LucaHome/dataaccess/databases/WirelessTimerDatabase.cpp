#include "WirelessTimerDatabase.h"

WirelessTimerDatabase::WirelessTimerDatabase() {}

WirelessTimerDatabase::WirelessTimerDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

WirelessTimerDatabase::~WirelessTimerDatabase()
{
	close();
}

char WirelessTimerDatabase::Dispose()
{
	return close();
}

vector<WirelessTimer> WirelessTimerDatabase::GetList()
{
	vector<WirelessTimer> list;
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
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		int weekday = sqlite3_column_int(res, 3);
		int hour = sqlite3_column_int(res, 4);
		int minute = sqlite3_column_int(res, 5);
		string gpioUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		bool gpioAction = sqlite3_column_int(res, 7) == 1;
		string wirelessSocketUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 8)));
		bool wirelessSocketAction = sqlite3_column_int(res, 9) == 1;
		string wirelessSwitchUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 10)));

		WirelessTimer newEntry(uuid, name, weekday, hour, minute, gpioUuid, gpioAction, wirelessSocketUuid, wirelessSocketAction, wirelessSwitchUuid);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char WirelessTimerDatabase::Insert(WirelessTimer entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyName + " ,"
		+ _keyWeekday + " ,"
		+ _keyHour + " ,"
		+ _keyMinute + " ,"
		+ _keyGpioUuid + " ,"
		+ _keyGpioAction + " ,"
		+ _keyWirelessSocketUuid + " ,"
		+ _keyWirelessSocketAction + " ,"
		+ _keyWirelessSwitchUuid + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ Tools::ConvertIntToStr(entry.GetWeekday()) + ","
		+ Tools::ConvertIntToStr(entry.GetHour()) + ","
		+ Tools::ConvertIntToStr(entry.GetMinute()) + ","
		+ "'" + entry.GetGpioUuid() + "',"
		+ Tools::ConvertBoolToStr(entry.GetGpioAction()) + ","
		+ "'" + entry.GetWirelessSocketUuid() + "',"
		+ Tools::ConvertBoolToStr(entry.GetWirelessSocketAction()) + ","
		+ "'" + entry.GetWirelessSwitchUuid() + "'"
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

char WirelessTimerDatabase::Update(WirelessTimer entry)
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
		+ "SET " + _keyGpioUuid + " = '" + entry.GetGpioUuid() + "',"
		+ "SET " + _keyGpioAction + " = " + Tools::ConvertBoolToStr(entry.GetGpioAction()) + ","
		+ "SET " + _keyWirelessSocketUuid + " = '" + entry.GetWirelessSocketUuid() + "',"
		+ "SET " + _keyWirelessSocketAction + " = " + Tools::ConvertBoolToStr(entry.GetWirelessSocketAction()) + ","
		+ "SET " + _keyWirelessSwitchUuid + " = '" + entry.GetWirelessSwitchUuid() + "' "
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

char WirelessTimerDatabase::Delete(string uuid)
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

char WirelessTimerDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char WirelessTimerDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyName + " TEXT NOT NULL,"
		+ _keyWeekday + " INTEGER NOT NULL,"
		+ _keyHour + " INTEGER NOT NULL,"
		+ _keyMinute + " INTEGER NOT NULL,"
		+ _keyGpioUuid + " TEXT NOT NULL,"
		+ _keyGpioAction + " INTEGER NOT NULL,"
		+ _keyWirelessSocketUuid + " TEXT NOT NULL,"
		+ _keyWirelessSocketAction + " INTEGER NOT NULL,"
		+ _keyWirelessSwitchUuid + " TEXT NOT NULL);";

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

char WirelessTimerDatabase::close()
{
	sqlite3_close(database);
	return 0;
}