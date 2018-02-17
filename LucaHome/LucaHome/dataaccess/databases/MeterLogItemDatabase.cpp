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
		string typeUuid = sqlite3_column_text(res, 3);
		string type = sqlite3_column_text(res, 4);
		int day = sqlite3_column_int(res, 5);
		int month = sqlite3_column_int(res, 6);
		int year = sqlite3_column_int(res, 7);
		int hour = sqlite3_column_int(res, 8);
		int minute = sqlite3_column_int(res, 9);
		string meterId = sqlite3_column_text(res, 10);
		double value = sqlite3_column_double(res, 11);
		string imageName = sqlite3_column_text(res, 12);

		MeterLogItem newEntry(uuid, roomUuid, typeUuid, type, day, month, year, hour, minute, meterId, value, imageName);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MeterLogItemDatabase::Insert(int rowId, MeterLogItem entry)
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
		+ _keyTypeUuid + " ,"
		+ _keyType + " ,"
		+ _keyDay + " ,"
		+ _keyMonth + " ,"
		+ _keyYear + " ,"
		+ _keyHour + " ,"
		+ _keyMinute + " ,"
		+ _keyMeterId + " ,"
		+ _keyValue + " ,"
		+ _keyImageName + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetRoomUuid() + "',"
		+ "'" + entry.GetTypeUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ Tools::ConvertIntToStr(entry.GetHour()) + ","
		+ Tools::ConvertIntToStr(entry.GetMinute()) + ","
		+ "'" + entry.GetMeterId() + "',"
		+ Tools::ConvertDoubleToStr(entry.GetValue()) + ","
		+ "'" + entry.GetImageName() + "'"
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
		+ "SET " + _keyDay + " = " + Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ "SET " + _keyMonth + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyYear + " = " + Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "SET " + _keyHour + " = " + Tools::ConvertIntToStr(entry.GetHour()) + ","
		+ "SET " + _keyMinute + " = " + Tools::ConvertIntToStr(entry.GetMinute()) + ","
		+ "SET " + _keyMeterId + " = '" + entry.GetMeterId() + "',"
		+ "SET " + _keyValue + " = " + Tools::ConvertDoubleToStr(entry.GetValue()) + ","
		+ "SET " + _keyImageName + " = '" + entry.GetImageName() + "' "
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

char MeterLogItemDatabase::Delete(MeterLogItem entry)
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

char MeterLogItemDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char MeterLogItemDatabase::create()
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
		+ _keyTypeUuid + " TEXT NOT NULL,"
		+ _keyType + " TEXT NOT NULL,"
		+ _keyDay + " INT NOT NULL,"
		+ _keyMonth + " INT NOT NULL,"
		+ _keyYear + " INT NOT NULL,"
		+ _keyHour + " INT NOT NULL,"
		+ _keyMinute + " INT NOT NULL,"
		+ _keyMeterId + " TEXT NOT NULL,"
		+ _keyValue + " REAL NOT NULL,"
		+ _keyImageName + " TEXT NOT NULL);";

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

char MeterLogItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}