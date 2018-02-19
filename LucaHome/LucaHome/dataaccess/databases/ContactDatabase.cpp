#include "ContactDatabase.h"

ContactDatabase::ContactDatabase() {}

ContactDatabase::ContactDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

ContactDatabase::~ContactDatabase()
{
	close();
}

char ContactDatabase::Dispose()
{
	return close();
}

vector<Contact> ContactDatabase::GetList()
{
	vector<Contact> list;
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
		string group = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string address = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		string phoneHome = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));
		string phoneMobile = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		string email = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		int birthdayDay = sqlite3_column_int(res, 8);
		int birthdayMonth = sqlite3_column_int(res, 9);
		int birthdayYear = sqlite3_column_int(res, 10);
		bool birthdayRemindMe = sqlite3_column_int(res, 11) == 1;
		bool birthdaySentReminderMail = sqlite3_column_int(res, 12) == 1;

		Contact newEntry(uuid, name, group, address, phoneHome, phoneMobile, email, birthdayDay, birthdayMonth, birthdayYear, birthdayRemindMe, birthdaySentReminderMail);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

Contact ContactDatabase::GetByUuid(string uuid)
{
	if (!open()) {
		return Contact();
	}

	string sqlSelectCommand = "SELECT * FROM " + _tableName + "WHERE " + _keyUuid + "=" + uuid + " LIMIT 1;";

	sqlite3_stmt *res;
	char *errorMessage = 0;

	int error = sqlite3_exec(database, sqlSelectCommand.c_str(), NULL, &res, &errorMessage);
	if (error != SQLITE_OK) {
		sqlite3_free(errorMessage);
		close();
		return Contact();
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		string uuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string group = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		string address = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
		string phoneHome = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));
		string phoneMobile = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		string email = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		int birthdayDay = sqlite3_column_int(res, 8);
		int birthdayMonth = sqlite3_column_int(res, 9);
		int birthdayYear = sqlite3_column_int(res, 10);
		bool birthdayRemindMe = sqlite3_column_int(res, 11) == 1;
		bool birthdaySentReminderMail = sqlite3_column_int(res, 12) == 1;

		Contact contact(uuid, name, group, address, phoneHome, phoneMobile, email, birthdayDay, birthdayMonth, birthdayYear, birthdayRemindMe, birthdaySentReminderMail);
		sqlite3_finalize(res);
		close();

		return contact;
	}

	sqlite3_finalize(res);
	close();
	return Contact();
}

char ContactDatabase::Insert(int rowId, Contact entry)
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
		+ _keyGroup + " ,"
		+ _keyAddress + " ,"
		+ _keyPhoneHome + " ,"
		+ _keyPhoneMobile + " ,"
		+ _keyEMail + " ,"
		+ _keyBirthdayDay + " ,"
		+ _keyBirthdayMonth + " ,"
		+ _keyBirthdayYear + " ,"
		+ _keyBirthdayRemindMe + " ,"
		+ _keyBirthdaySentReminderMail + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetGroup() + "',"
		+ "'" + entry.GetAddress() + "',"
		+ "'" + entry.GetPhoneHome() + "',"
		+ "'" + entry.GetPhoneMobile() + "',"
		+ "'" + entry.GetEMail() + "',"
		+ Tools::ConvertIntToStr(entry.GetBirthdayDay()) + ", "
		+ Tools::ConvertIntToStr(entry.GetBirthdayMonth()) + ", "
		+ Tools::ConvertIntToStr(entry.GetBirthdayYear()) + ", "
		+ Tools::ConvertBoolToStr(entry.GetBirthdayRemindMe()) + ", "
		+ Tools::ConvertBoolToStr(entry.GetBirthdaySentReminderMail())
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

char ContactDatabase::Update(Contact entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyGroup + " = '" + entry.GetGroup() + "',"
		+ "SET " + _keyAddress + " = '" + entry.GetAddress() + "',"
		+ "SET " + _keyPhoneHome + " = '" + entry.GetPhoneHome() + "',"
		+ "SET " + _keyPhoneMobile + " = '" + entry.GetPhoneMobile() + "',"
		+ "SET " + _keyEMail + " = '" + entry.GetEMail() + "',"
		+ "SET " + _keyBirthdayDay + " = " + Tools::ConvertIntToStr(entry.GetBirthdayDay()) + ","
		+ "SET " + _keyBirthdayMonth + " = " + Tools::ConvertIntToStr(entry.GetBirthdayMonth()) + ","
		+ "SET " + _keyBirthdayYear + " = " + Tools::ConvertIntToStr(entry.GetBirthdayYear()) + ","
		+ "SET " + _keyBirthdayRemindMe + " = " + Tools::ConvertBoolToStr(entry.GetBirthdayRemindMe()) + ","
		+ "SET " + _keyBirthdaySentReminderMail + " = " + Tools::ConvertBoolToStr(entry.GetBirthdaySentReminderMail()) + " "
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

char ContactDatabase::Delete(string uuid)
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

char ContactDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char ContactDatabase::create()
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
		+ _keyGroup + " TEXT NOT NULL,"
		+ _keyAddress + " TEXT NOT NULL,"
		+ _keyPhoneHome + " TEXT NOT NULL,"
		+ _keyPhoneMobile + " TEXT NOT NULL,"
		+ _keyEMail + " TEXT NOT NULL,"
		+ _keyBirthdayDay + " INT NOT NULL,"
		+ _keyBirthdayMonth + " INT NOT NULL,"
		+ _keyBirthdayYear + " INT NOT NULL,"
		+ _keyBirthdayRemindMe + " INT NOT NULL,"
		+ _keyBirthdaySentReminderMail + " INT NOT NULL);";

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

char ContactDatabase::close()
{
	sqlite3_close(database);
	return 0;
}