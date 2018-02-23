#include "MeterLogItemDatabase.h"

MeterLogItemDatabase::MeterLogItemDatabase() {}

MeterLogItemDatabase::MeterLogItemDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

MeterLogItemDatabase::~MeterLogItemDatabase()
{
	close();
}

char MeterLogItemDatabase::Dispose()
{
	return close();
}

vector<MeterLogItem> MeterLogItemDatabase::GetList()
{
	vector<MeterLogItem> list;
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
		string typeUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		string meterId = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));
		double value = sqlite3_column_double(res, 6);
		string imageName = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		int saveDateTime = sqlite3_column_int(res, 8);

		MeterLogItem newEntry(uuid, roomUuid, typeUuid, type, meterId, value, imageName, saveDateTime);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MeterLogItemDatabase::Insert(MeterLogItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyRoomUuid + " ,"
		+ _keyTypeUuid + " ,"
		+ _keyType + " ,"
		+ _keyMeterId + " ,"
		+ _keyValue + " ,"
		+ _keyImageName + " ,"
		+ _keySaveDateTime + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetTypeUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ "'" + entry.GetMeterId() + "',"
		+ Tools::ConvertDoubleToStr(entry.GetValue()) + ","
		+ "'" + entry.GetImageName() + "',"
		+ Tools::ConvertIntToStr(entry.GetSaveDateTime())
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

char MeterLogItemDatabase::Update(MeterLogItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyRoomUuid + " = '" + entry.GetRoomUuid() + "',"
		+ "SET " + _keyTypeUuid + " = '" + entry.GetTypeUuid() + "',"
		+ "SET " + _keyType + " = '" + entry.GetType() + "',"
		+ "SET " + _keyMeterId + " = '" + entry.GetMeterId() + "',"
		+ "SET " + _keyValue + " = " + Tools::ConvertDoubleToStr(entry.GetValue()) + ","
		+ "SET " + _keyImageName + " = '" + entry.GetImageName() + "',"
		+ "SET " + _keySaveDateTime + " = " + Tools::ConvertIntToStr(entry.GetSaveDateTime()) + " "
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

char MeterLogItemDatabase::Delete(string uuid)
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

char MeterLogItemDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char MeterLogItemDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyRoomUuid + " TEXT NOT NULL,"
		+ _keyTypeUuid + " TEXT NOT NULL,"
		+ _keyType + " TEXT NOT NULL,"
		+ _keyMeterId + " TEXT NOT NULL,"
		+ _keyValue + " REAL NOT NULL,"
		+ _keyImageName + " TEXT NOT NULL,"
		+ _keySaveDateTime + " INTEGER NOT NULL);";

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

char MeterLogItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}