#include "CoinDatabase.h"

CoinDatabase::CoinDatabase() {}

CoinDatabase::CoinDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

CoinDatabase::~CoinDatabase()
{
	close();
}

char CoinDatabase::Dispose()
{
	return close();
}

vector<Coin> CoinDatabase::GetList()
{
	vector<Coin> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyUserUuid + ";";

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
		string userUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		double amount = sqlite3_column_double(res, 4);

		Coin newEntry(uuid, userUuid, type, amount);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

vector<Coin> CoinDatabase::GetUserList(string userUuid)
{
	vector<Coin> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " WHERE " + _keyUserUuid + "=" + userUuid + " ORDER BY " + _keyType + ";";

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
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		double amount = sqlite3_column_double(res, 4);

		Coin newEntry(uuid, userUuid, type, amount);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char CoinDatabase::Insert(Coin entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyUserUuid + " ,"
		+ _keyType + " ,"
		+ _keyAmount + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetUserUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ Tools::ConvertDoubleToStr(entry.GetAmount())
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

char CoinDatabase::Update(Coin entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyUserUuid + " = '" + entry.GetUserUuid() + "',"
		+ "SET " + _keyType + " = '" + entry.GetType() + "',"
		+ "SET " + _keyAmount + " = " + Tools::ConvertDoubleToStr(entry.GetAmount()) + " "
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

char CoinDatabase::Delete(string uuid)
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

char CoinDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char CoinDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyUserUuid + " TEXT NOT NULL,"
		+ _keyType + " INTEGER NOT NULL,"
		+ _keyAmount + " REAL NOT NULL);";

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

char CoinDatabase::close()
{
	sqlite3_close(database);
	return 0;
}