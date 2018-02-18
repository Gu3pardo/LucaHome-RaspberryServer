#include "MealDatabase.h"

MealDatabase::MealDatabase() {}

MealDatabase::MealDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

MealDatabase::~MealDatabase()
{
	close();
}

char MealDatabase::Dispose()
{
	return close();
}

vector<Meal> MealDatabase::GetList()
{
	vector<Meal> list;
	if (!open()) {
		return list;
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + " ORDER BY " + _keyWeekday + ";";

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
		string title = sqlite3_column_text(res, 2);
		string description = sqlite3_column_text(res, 3);
		int weekday = sqlite3_column_int(res, 4);
		int day = sqlite3_column_int(res, 5);
		int month = sqlite3_column_int(res, 6);
		int year = sqlite3_column_int(res, 7);
		string shoppingItemUuidListDbString = sqlite3_column_text(res, 8);

		vector<string> shoppingItemUuidList = Tools::Explode(",", shoppingItemUuidListDbString);

		Meal newEntry(uuid, title, description, weekday, day, month, year, shoppingItemUuidList);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MealDatabase::Insert(int rowId, Meal entry)
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
		+ _keyWeekday + " ,"
		+ _keyDay + " ,"
		+ _keyMonth + " ,"
		+ _keyYear + " ,"
		+ _keyShoppingItemUuidList + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTitle() + "',"
		+ "'" + entry.GetDescription() + "',"
		+ Tools::ConvertIntToStr(entry.GetWeekday()) + ","
		+ Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "'" + entry.GetShoppingItemUuidDbString() + "'"
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

char MealDatabase::Update(Meal entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTitle + " = '" + entry.GetTitle() + "',"
		+ "SET " + _keyDescription + " = '" + entry.GetDescription() + "',"
		+ "SET " + _keyWeekday + " = " + Tools::ConvertIntToStr(entry.GetWeekday()) + ","
		+ "SET " + _keyDay + " = " + Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ "SET " + _keyMonth + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyYear + " = " + Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "SET " + _keyShoppingItemUuidList + " = '" + entry.GetShoppingItemUuidDbString() + "' "
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

char MealDatabase::Delete(string uuid)
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

char MealDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char MealDatabase::create()
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
		+ _keyWeekday + " INT NOT NULL,"
		+ _keyDay + " INT NOT NULL,"
		+ _keyMonth + " INT NOT NULL,"
		+ _keyYear + " INT NOT NULL,"
		+ _keyShoppingItemUuidList + " TEXT NOT NULL);";

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

char MealDatabase::close()
{
	sqlite3_close(database);
	return 0;
}