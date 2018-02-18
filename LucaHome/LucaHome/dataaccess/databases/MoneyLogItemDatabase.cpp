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
		string typeUuid = sqlite3_column_text(res, 2);
		string bank = sqlite3_column_text(res, 3);
		string plan = sqlite3_column_text(res, 4);
		double amount = sqlite3_column_double(res, 5);
		string unit = sqlite3_column_text(res, 6);
		int day = sqlite3_column_int(res, 7);
		int month = sqlite3_column_int(res, 8);
		int year = sqlite3_column_int(res, 9);
		string user = sqlite3_column_text(res, 10);

		MoneyLogItem newEntry(uuid, typeUuid, bank, plan, amount, unit, day, month, year, user);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MoneyLogItemDatabase::Insert(int rowId, MoneyLogItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyTypeUuid + " ,"
		+ _keyBank + " ,"
		+ _keyPlan + " ,"
		+ _keyAmount + " ,"
		+ _keyUnit + " ,"
		+ _keyDay + " ,"
		+ _keyMonth + " ,"
		+ _keyYear + " ,"
		+ _keyUser + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTypeUuid() + "',"
		+ "'" + entry.GetBank() + "',"
		+ "'" + entry.GetPlan() + "',"
		+ Tools::ConvertDoubleToStr(entry.GetAmount()) + ","
		+ "'" + entry.GetUnit() + "',"
		+ Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "'" + entry.GetUser() + "'"
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
		+ "SET " + _keyDay + " = " + Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ "SET " + _keyMonth + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyYear + " = " + Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "SET " + _keyUser + " = '" + entry.GetUser() + "' "
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
	int error = sqlite3_exec(database, sqlDeleteCommand, NULL, NULL, &errorMessage);
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
	return sqlite3_open(_databaseName, &database);
}

char MoneyLogItemDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTypeUuid + " TEXT NOT NULL,"
		+ _keyBank + " TEXT NOT NULL,"
		+ _keyPlan + " TEXT NOT NULL,"
		+ _keyAmount + " REAL NOT NULL,"
		+ _keyUnit + " TEXT NOT NULL,"
		+ _keyDay + " INT NOT NULL,"
		+ _keyMonth + " INT NOT NULL,"
		+ _keyYear + " INT NOT NULL,"
		+ _keyUser + " TEXT NOT NULL);";

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

char MoneyLogItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}