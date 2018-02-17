#include "BirthdayDatabase.h"

BirthdayDatabase::BirthdayDatabase() {}

BirthdayDatabase::BirthdayDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

BirthdayDatabase::~BirthdayDatabase()
{
	close();
}

char BirthdayDatabase::Dispose()
{
	return close();
}

vector<Birthday> BirthdayDatabase::GetList()
{
	vector<Birthday> list;
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
		int birthdayDay = sqlite3_column_int(res, 3);
		int birthdayMonth = sqlite3_column_int(res, 4);
		int birthdayYear = sqlite3_column_int(res, 5);
		string group = sqlite3_column_text(res, 6);
		bool remindMe = sqlite3_column_int(res, 7) == 1;
		bool sentMail = sqlite3_column_int(res, 8) == 1;

		Birthday newEntry(uuid, name, birthdayDay, birthdayMonth, birthdayYear, group, remindMe, sentMail);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char BirthdayDatabase::Insert(int rowId, Birthday entry)
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
		+ _keyBirthdayDay + " ,"
		+ _keyBirthdayMonth + " ,"
		+ _keyBirthdayYear + " ,"
		+ _keyGroup + " ,"
		+ _keyRemindMe + " ,"
		+ _keySentMail + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ Tools::ConvertIntToStr(entry.GetDay()) + ", "
		+ Tools::ConvertIntToStr(entry.GetMonth()) + ", "
		+ Tools::ConvertIntToStr(entry.GetYear()) + ", "
		+ "'" + entry.GetGroup() + "',"
		+ Tools::ConvertBoolToStr(entry.GetRemindMe()) + ", "
		+ Tools::ConvertBoolToStr(entry.GetSentMail())
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

char BirthdayDatabase::Update(Birthday entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyBirthdayDay + " = " + Tools::ConvertIntToStr(entry.GetDay()) + ","
		+ "SET " + _keyBirthdayMonth + " = " + Tools::ConvertIntToStr(entry.GetMonth()) + ","
		+ "SET " + _keyBirthdayYear + " = " + Tools::ConvertIntToStr(entry.GetYear()) + ","
		+ "SET " + _keyGroup + " = '" + entry.GetGroup() + "',"
		+ "SET " + _keyRemindMe + " = " + Tools::ConvertBoolToStr(entry.GetRemindMe()) + ","
		+ "SET " + _keySentMail + " = " + Tools::ConvertBoolToStr(entry.GetSentMail()) + " "
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

char BirthdayDatabase::Delete(Birthday entry)
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

char BirthdayDatabase::open()
{
	return sqlite3_open(_databaseName, &database);
}

char BirthdayDatabase::create()
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
		+ _keyBirthdayDay + " INT NOT NULL,"
		+ _keyBirthdayMonth + " INT NOT NULL,"
		+ _keyBirthdayYear + " INT NOT NULL,"
		+ _keyGroup + " TEXT NOT NULL,"
		+ _keyRemindMe + " INT NOT NULL,"
		+ _keySentMail + " INT NOT NULL);";

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

char BirthdayDatabase::close()
{
	sqlite3_close(database);
	return 0;
}