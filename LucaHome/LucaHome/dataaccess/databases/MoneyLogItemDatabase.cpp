#include "MoneyLogItemDatabase.h"

MoneyLogItemDatabase::MoneyLogItemDatabase() {}

MoneyLogItemDatabase::MoneyLogItemDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

MoneyLogItemDatabase::~MoneyLogItemDatabase()
{
	close();
}

char MoneyLogItemDatabase::Dispose()
{
	return close();
}

vector<MoneyLogItem> MoneyLogItemDatabase::GetList()
{
	vector<MoneyLogItem> list;
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
		string typeUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string bank = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string plan = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		double amount = sqlite3_column_double(res, 5);
		string unit = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		string userUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		int saveDate = sqlite3_column_int(res, 8);

		MoneyLogItem newEntry(uuid, typeUuid, bank, plan, amount, unit, userUuid, saveDate);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

vector<MoneyLogItem> MoneyLogItemDatabase::GetUserList(string userUuid)
{
	vector<MoneyLogItem> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " WHERE " + _keyUserUuid + "=" + userUuid + " ORDER BY " + _keyTypeUuid + ";";

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
		string typeUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string bank = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string plan = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		double amount = sqlite3_column_double(res, 5);
		string unit = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		string userUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		int saveDate = sqlite3_column_int(res, 8);

		MoneyLogItem newEntry(uuid, typeUuid, bank, plan, amount, unit, userUuid, saveDate);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MoneyLogItemDatabase::Insert(MoneyLogItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyTypeUuid + " ,"
		+ _keyBank + " ,"
		+ _keyPlan + " ,"
		+ _keyAmount + " ,"
		+ _keyUnit + " ,"
		+ _keyUserUuid + " ,"
		+ _keySaveDate + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTypeUuid() + "',"
		+ "'" + entry.GetBank() + "',"
		+ "'" + entry.GetPlan() + "',"
		+ Tools::ConvertDoubleToStr(entry.GetAmount()) + ","
		+ "'" + entry.GetUnit() + "',"
		+ "'" + entry.GetUserUuid() + "',"
		+ Tools::ConvertIntToStr(entry.GetSaveDate())
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

char MoneyLogItemDatabase::Update(MoneyLogItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTypeUuid + " = '" + entry.GetTypeUuid() + "',"
		+ "SET " + _keyBank + " = '" + entry.GetBank() + "',"
		+ "SET " + _keyPlan + " = '" + entry.GetPlan() + "',"
		+ "SET " + _keyAmount + " = " + Tools::ConvertDoubleToStr(entry.GetAmount()) + ","
		+ "SET " + _keyUnit + " = '" + entry.GetUnit() + "',"
		+ "SET " + _keyUserUuid + " = '" + entry.GetUserUuid() + "',"
		+ "SET " + _keySaveDate + " = " + Tools::ConvertIntToStr(entry.GetSaveDate()) + " "
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

char MoneyLogItemDatabase::Delete(string uuid)
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

char MoneyLogItemDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char MoneyLogItemDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTypeUuid + " TEXT NOT NULL,"
		+ _keyBank + " TEXT NOT NULL,"
		+ _keyPlan + " TEXT NOT NULL,"
		+ _keyAmount + " REAL NOT NULL,"
		+ _keyUnit + " TEXT NOT NULL,"
		+ _keyUserUuid + " TEXT NOT NULL,"
		+ _keySaveDate + " INTEGER NOT NULL);";

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

char MoneyLogItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}