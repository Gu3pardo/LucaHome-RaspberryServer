#include "YoutubeVideoDatabase.h"

YoutubeVideoDatabase::YoutubeVideoDatabase() {}

YoutubeVideoDatabase::YoutubeVideoDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

YoutubeVideoDatabase::~YoutubeVideoDatabase()
{
	close();
}

char YoutubeVideoDatabase::Dispose()
{
	return close();
}

vector<YoutubeVideo> YoutubeVideoDatabase::GetList()
{
	vector<YoutubeVideo> list;
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
		string youtubeId = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int playCount = sqlite3_column_int(res, 4);
		string description = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5)));
		string mediumImageUrl = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));

		YoutubeVideo newEntry(uuid, title, youtubeId, playCount, description, mediumImageUrl);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char YoutubeVideoDatabase::Insert(YoutubeVideo entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlInsertCommand =
		"INSERT INTO " + _tableName + " ("
		+ _keyUuid + " ,"
		+ _keyTitle + " ,"
		+ _keyYoutubeId + " ,"
		+ _keyPlayCount + " ,"
		+ _keyDescription + " ,"
		+ _keyMediumImageUrl + " ) "
		+ "VALUES("
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTitle() + "',"
		+ "'" + entry.GetYoutubeId() + "',"
		+ Tools::ConvertIntToStr(entry.GetPlayCount()) + ","
		+ "'" + entry.GetDescription() + "',"
		+ "'" + entry.GetMediumImageUrl() + "'"
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

char YoutubeVideoDatabase::Update(YoutubeVideo entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTitle + " = '" + entry.GetTitle() + "',"
		+ "SET " + _keyYoutubeId + " = '" + entry.GetYoutubeId() + "',"
		+ "SET " + _keyPlayCount + " = " + Tools::ConvertIntToStr(entry.GetPlayCount()) + ","
		+ "SET " + _keyDescription + " = '" + entry.GetDescription() + "',"
		+ "SET " + _keyMediumImageUrl + " = '" + entry.GetMediumImageUrl() + "' "
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

char YoutubeVideoDatabase::Delete(string uuid)
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

char YoutubeVideoDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char YoutubeVideoDatabase::create()
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlCreateCommand =
		"CREATE TABLE " + _tableName + "("
		+ _keyRowId + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		+ _keyUuid + " TEXT NOT NULL,"
		+ _keyTitle + " TEXT NOT NULL,"
		+ _keyYoutubeId + " TEXT NOT NULL,"
		+ _keyPlayCount + " INTEGER NOT NULL,"
		+ _keyDescription + " TEXT NOT NULL,"
		+ _keyMediumImageUrl + " TEXT NOT NULL);";

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

char YoutubeVideoDatabase::close()
{
	sqlite3_close(database);
	return 0;
}