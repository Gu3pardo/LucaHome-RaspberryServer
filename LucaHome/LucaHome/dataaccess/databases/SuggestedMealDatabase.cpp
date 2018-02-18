#include "SuggestedMealDatabase.h"

SuggestedMealDatabase::SuggestedMealDatabase() {}

SuggestedMealDatabase::SuggestedMealDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

SuggestedMealDatabase::~SuggestedMealDatabase()
{
	close();
}

char SuggestedMealDatabase::Dispose()
{
	return close();
}

vector<SuggestedMeal> SuggestedMealDatabase::GetList()
{
	vector<SuggestedMeal> list;
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
		string title = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string description = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int rating = sqlite3_column_int(res, 4);
		int useCounter = sqlite3_column_int(res, 5);
		string shoppingItemUuidListDbString = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));

		vector<string> shoppingItemUuidList = Tools::Explode(",", shoppingItemUuidListDbString);

		SuggestedMeal newEntry(uuid, title, description, rating, useCounter, shoppingItemUuidList);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char SuggestedMealDatabase::Insert(int rowId, SuggestedMeal entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyRowId + " ,"
		+ _keyUuid + " ,"
		+ _keyTitle + " ,"
		+ _keyDescription + " ,"
		+ _keyRating + " ,"
		+ _keyUseCounter + " ,"
		+ _keyShoppingItemUuidList + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTitle() + "',"
		+ "'" + entry.GetDescription() + "',"
		+ Tools::ConvertIntToStr(entry.GetRating()) + ","
		+ Tools::ConvertIntToStr(entry.GetUseCount()) + ","
		+ "'" + entry.GetShoppingItemUuidDbString() + "'"
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

char SuggestedMealDatabase::Update(SuggestedMeal entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTitle + " = '" + entry.GetTitle() + "',"
		+ "SET " + _keyDescription + " = '" + entry.GetDescription() + "',"
		+ "SET " + _keyRating + " = " + Tools::ConvertIntToStr(entry.GetRating()) + ","
		+ "SET " + _keyUseCounter + " = " + Tools::ConvertIntToStr(entry.GetUseCount()) + ","
		+ "SET " + _keyShoppingItemUuidList + " = '" + entry.GetShoppingItemUuidDbString() + "' "
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

char SuggestedMealDatabase::Delete(string uuid)
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

char SuggestedMealDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char SuggestedMealDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " KEY NOT NULL,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTitle + " TEXT NOT NULL,"
		+ _keyDescription + " TEXT NOT NULL,"
		+ _keyRating + " INT NOT NULL,"
		+ _keyUseCounter + " INT NOT NULL,"
		+ _keyShoppingItemUuidList + " TEXT NOT NULL);";

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

char SuggestedMealDatabase::close()
{
	sqlite3_close(database);
	return 0;
}