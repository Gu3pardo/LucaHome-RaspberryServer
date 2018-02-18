#include "MediaServerDatabase.h"

MediaServerDatabase::MediaServerDatabase() {}

MediaServerDatabase::MediaServerDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

MediaServerDatabase::~MediaServerDatabase()
{
	close();
}

char MediaServerDatabase::Dispose()
{
	return close();
}

vector<MediaServer> MediaServerDatabase::GetList()
{
	vector<MediaServer> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyRoomUuid + ";";

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
		string ip = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		bool isSleepingServer = sqlite3_column_int(res, 4) == 1;
		string wirelessSocketUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));

		MediaServer newEntry(uuid, roomUuid, ip, isSleepingServer, wirelessSocketUuid);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MediaServerDatabase::Insert(int rowId, MediaServer entry)
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
		+ _keyIp + " ,"
		+ _keyIsSleepingServer + " ,"
		+ _keyWirelessSocketUuid + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetIp() + "',"
		+ Tools::ConvertBoolToStr(entry.IsSleepingServer()) + ","
		+ "'" + entry.GetWirelessSocketUuid() + "'"
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

char MediaServerDatabase::Update(MediaServer entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyRoomUuid + " = '" + entry.GetRoomUuid() + "',"
		+ "SET " + _keyIp + " = '" + entry.GetIp() + "',"
		+ "SET " + _keyIsSleepingServer + " = " + Tools::ConvertBoolToStr(entry.IsSleepingServer()) + ","
		+ "SET " + _keyWirelessSocketUuid + " = '" + entry.GetWirelessSocketUuid() + "' "
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

char MediaServerDatabase::Delete(string uuid)
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

char MediaServerDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char MediaServerDatabase::create()
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
		+ _keyIp + " TEXT NOT NULL,"
		+ _keyIsSleepingServer + " INT NOT NULL,"
		+ _keyWirelessSocketUuid + " TEXT NOT NULL);";

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

char MediaServerDatabase::close()
{
	sqlite3_close(database);
	return 0;
}