#include "SuggestedShoppingItemDatabase.h"

SuggestedShoppingItemDatabase::SuggestedShoppingItemDatabase() {}

SuggestedShoppingItemDatabase::SuggestedShoppingItemDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

SuggestedShoppingItemDatabase::~SuggestedShoppingItemDatabase()
{
	close();
}

char SuggestedShoppingItemDatabase::Dispose()
{
	return close();
}

vector<SuggestedShoppingItem> SuggestedShoppingItemDatabase::GetList()
{
	vector<SuggestedShoppingItem> list;
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
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int quantity = sqlite3_column_int(res, 4);
		string unit = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));

		SuggestedShoppingItem newEntry(uuid, name, type, quantity, unit);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char SuggestedShoppingItemDatabase::Insert(int rowId, SuggestedShoppingItem entry)
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
	int error = sqlite3_exec(database, sqlInsertCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char SuggestedShoppingItemDatabase::Update(SuggestedShoppingItem entry)
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
	int error = sqlite3_exec(database, sqlUpdateCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char SuggestedShoppingItemDatabase::Delete(string uuid)
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

char SuggestedShoppingItemDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char SuggestedShoppingItemDatabase::create()
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
	int error = sqlite3_exec(database, sqlCreateCommand.c_str(), NULL, NULL, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return *errorMessage;
	}

	close();
	return 0;
}

char SuggestedShoppingItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}