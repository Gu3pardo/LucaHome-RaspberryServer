#include "ShoppingItemDatabase.h"

ShoppingItemDatabase::ShoppingItemDatabase() {}

ShoppingItemDatabase::ShoppingItemDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

ShoppingItemDatabase::~ShoppingItemDatabase()
{
	close();
}

char ShoppingItemDatabase::Dispose()
{
	return close();
}

vector<ShoppingItem> ShoppingItemDatabase::GetList()
{
	vector<ShoppingItem> list;
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
		string type = sqlite3_column_text(res, 3);
		int quantity = sqlite3_column_int(res, 4);
		string unit = sqlite3_column_text(res, 5);

		ShoppingItem newEntry(uuid, name, type, quantity, unit);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char ShoppingItemDatabase::Insert(int rowId, ShoppingItem entry)
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
		+ _keyType + " ,"
		+ _keyQuantity + " ,"
		+ _keyUnit + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetType() + "',"
		+ Tools::ConvertIntToStr(entry.GetQuantity()) + ","
		+ "'" + entry.GetUnit() + "'"
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

char ShoppingItemDatabase::Update(ShoppingItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyType + " = '" + entry.GetType() + "',"
		+ "SET " + _keyQuantity + " = " + Tools::ConvertIntToStr(entry.GetQuantity()) + ","
		+ "SET " + _keyUnit + " = '" + entry.GetUnit() + "' "
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

char ShoppingItemDatabase::Delete(ShoppingItem entry)
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

char ShoppingItemDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char ShoppingItemDatabase::create()
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
		+ _keyType + " TEXT NOT NULL,"
		+ _keyQuantity + " INT NOT NULL,"
		+ _keyUnit + " TEXT NOT NULL);";

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

char ShoppingItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}