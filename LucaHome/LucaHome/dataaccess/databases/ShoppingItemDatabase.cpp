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
		int creationTime = sqlite3_column_int(res, 6);
		bool sendDay7reminder = sqlite3_column_int(res, 7) == 1;

		ShoppingItem newEntry(uuid, name, type, quantity, unit, creationTime, sendDay7reminder);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char ShoppingItemDatabase::Insert(ShoppingItem entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyName + " ,"
		+ _keyType + " ,"
		+ _keyQuantity + " ,"
		+ _keyUnit + " ,"
		+ _keyCreationTime + " ,"
		+ _keySentDay7Reminder + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetType() + "',"
		+ Tools::ConvertIntToStr(entry.GetQuantity()) + ","
		+ "'" + entry.GetUnit() + "',"
		+ Tools::ConvertIntToStr(entry.GetCreationTime()) + ","
		+ Tools::ConvertBoolToStr(entry.GetSentDay7Reminder())
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
		+ "SET " + _keyUnit + " = '" + entry.GetUnit() + "', "
		+ "SET " + _keyCreationTime + " = " + Tools::ConvertIntToStr(entry.GetCreationTime()) + ","
		+ "SET " + _keySentDay7Reminder + " = " + Tools::ConvertBoolToStr(entry.GetSentDay7Reminder())
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

char ShoppingItemDatabase::UpdateReminder(string uuid, bool sendDay7Reminder)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keySentDay7Reminder + " = " + Tools::ConvertBoolToStr(sendDay7Reminder)
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

char ShoppingItemDatabase::Delete(string uuid)
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

char ShoppingItemDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char ShoppingItemDatabase::create()
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
		+ _keyType + " TEXT NOT NULL,"
		+ _keyQuantity + " INTEGER NOT NULL,"
		+ _keyUnit + " TEXT NOT NULL,"
		+ _keyCreationTime + " INTEGER NOT NULL,"
		+ _keySentDay7Reminder + " INTEGER NOT NULL);";

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

char ShoppingItemDatabase::close()
{
	sqlite3_close(database);
	return 0;
}