#include "MapContentDatabase.h"

MapContentDatabase::MapContentDatabase() {}

MapContentDatabase::MapContentDatabase(string databaseName)
{
	_databaseName = databaseName;
	create();
}

MapContentDatabase::~MapContentDatabase()
{
	close();
}

char MapContentDatabase::Dispose()
{
	return close();
}

vector<MapContent> MapContentDatabase::GetList()
{
	vector<MapContent> list;
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
		string typeUuid = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
		string type = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
		int positionX = sqlite3_column_int(res, 4);
		int positionY = sqlite3_column_int(res, 5);
		string name = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
		string shortName = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 7)));
		bool visibility = sqlite3_column_int(res, 8) == 1;

		Position position(positionX, positionY);
		MapContent newEntry(uuid, typeUuid, type, position, name, shortName, visibility);
		list.push_back(newEntry);
	}

	sqlite3_finalize(res);
	close();
	return list;
}

char MapContentDatabase::Insert(int rowId, MapContent entry)
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
		+ _keyTypeUuid + " ,"
		+ _keyType + " ,"
		+ _keyPositionX + " ,"
		+ _keyPositionY + " ,"
		+ _keyName + " ,"
		+ _keyShortName + " ,"
		+ _keyVisibility + " ) "
		+ "VALUES("
		+ Tools::ConvertIntToStr(rowId) + ", "
		+ "'" + entry.GetUuid() + "',"
		+ "'" + entry.GetTypeUuid() + "',"
		+ "'" + entry.GetType() + "',"
		+ Tools::ConvertIntToStr(entry.GetPosition().GetX) + ","
		+ Tools::ConvertIntToStr(entry.GetPosition().GetY) + ","
		+ "'" + entry.GetName() + "',"
		+ "'" + entry.GetShortName() + "',"
		+ Tools::ConvertBoolToStr(entry.GetVisibility())
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

char MapContentDatabase::Update(MapContent entry)
{
	char openErrorMessage = open();
	if (openErrorMessage) {
		return openErrorMessage;
	}

	string sqlUpdateCommand =
		"UPDATE " + _tableName + " "
		+ "SET " + _keyTypeUuid + " = '" + entry.GetTypeUuid() + "',"
		+ "SET " + _keyType + " = '" + entry.GetType() + "',"
		+ "SET " + _keyPositionX + " = " + Tools::ConvertIntToStr(entry.GetPosition().GetX()) + ", "
		+ "SET " + _keyPositionX + " = " + Tools::ConvertIntToStr(entry.GetPosition().GetY()) + ", "
		+ "SET " + _keyName + " = '" + entry.GetName() + "',"
		+ "SET " + _keyShortName + " = '" + entry.GetShortName() + "',"
		+ "SET " + _keyVisibility + " = " + Tools::ConvertBoolToStr(entry.GetVisibility()) + " "
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

char MapContentDatabase::Delete(string uuid)
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

char MapContentDatabase::open()
{
	return sqlite3_open(_databaseName.c_str(), &database);
}

char MapContentDatabase::create()
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
		+ _keyType + " TEXT NOT NULL,"
		+ _keyPositionX + " INT NOT NULL,"
		+ _keyPositionY + " INT NOT NULL,"
		+ _keyName + " TEXT NOT NULL,"
		+ _keyShortName + " TEXT NOT NULL,"
		+ _keyVisibility + " INT NOT NULL);";

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

char MapContentDatabase::close()
{
	sqlite3_close(database);
	return 0;
}