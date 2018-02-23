#include "GpioDatabase.h"

GpioDatabase::GpioDatabase() {}

GpioDatabase::GpioDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

GpioDatabase::~GpioDatabase()
{
	close();
}

char GpioDatabase::Dispose()
{
	return close();
}

vector<Gpio> GpioDatabase::GetList()
{
	vector<Gpio> list;
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
		int pin = sqlite3_column_int(res, 3);
		bool state = sqlite3_column_int(res, 4) == 1;

		Gpio newEntry(uuid, name, pin, state);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

Gpio GpioDatabase::GetByUuid(string uuid)
{
	if (!open()) {
		return Gpio();
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + "WHERE " + _keyUuid + "=" + uuid + " LIMIT 1;";

	sqlite3_stmt *res;
	char *errorMessage = 0;

	int error = sqlite3_exec(database, sqlSelectCommand.c_str(), NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return Gpio();
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		int pin = sqlite3_column_int(res, 3);
		bool state = sqlite3_column_int(res, 4) == 1;

		Gpio gpio(uuid, name, pin, state);
		sqlite3_finalize(res);
		close();

		return gpio;
	}

	sqlite3_finalize(res);
	close();
	return Gpio();
}

char GpioDatabase::Insert(Gpio entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyName + " ,"
		+ _keyPin + " ,"
		+ _keyState + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ Tools::ConvertIntToStr(entry.GetPin()) + ","
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

char GpioDatabase::Update(Gpio entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyPin + " = " + Tools::ConvertIntToStr(entry.GetPin()) + ","
		+ "SET " + _keyState + " = " + Tools::ConvertBoolToStr(entry.GetState()) + " "
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

char GpioDatabase::UpdateState(string uuid, bool newState)
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

char GpioDatabase::Delete(string uuid)
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

char GpioDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char GpioDatabase::create()
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
		+ _keyPin + " INTEGER NOT NULL,"
		+ _keyState + " INTEGER NOT NULL);";

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

char GpioDatabase::close()
{
	sqlite3_close(database);
	return 0;
}