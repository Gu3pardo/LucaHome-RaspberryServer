#include "PuckJsDatabase.h"

PuckJsDatabase::PuckJsDatabase() {}

PuckJsDatabase::PuckJsDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

PuckJsDatabase::~PuckJsDatabase()
{
	close();
}

char PuckJsDatabase::Dispose()
{
	return close();
}

vector<PuckJs> PuckJsDatabase::GetList()
{
	vector<PuckJs> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyRoomUuid;

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
		string mac = sqlite3_column_text(res, 4);

		PuckJs newEntry(uuid, roomUuid, name, mac);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char PuckJsDatabase::Insert(int rowId, PuckJs entry)
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
		+ _keyMac + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetMac() + "'"
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

char PuckJsDatabase::Update(PuckJs entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyRoomUuid + " = '" + entry.GetRoomUuid() + "',"
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyMac + " = '" + entry.GetMac() + "' "
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

char PuckJsDatabase::Delete(PuckJs entry)
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

char PuckJsDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char PuckJsDatabase::create()
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
		+ _keyMac + " TEXT NOT NULL);";

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

char PuckJsDatabase::close()
{
	sqlite3_close(database);
	return 0;
}