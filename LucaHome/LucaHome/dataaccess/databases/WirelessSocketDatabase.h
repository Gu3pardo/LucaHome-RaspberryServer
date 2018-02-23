#include "ITemplateDatabase.h"
#include "../../domain/classes/WirelessSocket.h"

using namespace std;

#ifndef WIRELESS_SOCKET_DATABASE_H
#define WIRELESS_SOCKET_DATABASE_H

class WirelessSocketDatabase : public ITemplateDatabase<WirelessSocket>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseWirelessSocketListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyRoomUuid = "_roomUuid";
	string _keyName = "_name";
	string _keyCode = "_code";
	string _keyState = "_state";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	WirelessSocketDatabase();
	WirelessSocketDatabase(string);
	~WirelessSocketDatabase();

	virtual char Dispose();

	virtual vector<WirelessSocket> GetList();
	virtual WirelessSocket GetByUuid(string);

	virtual char Insert(WirelessSocket);
	virtual char Update(WirelessSocket);
	virtual char UpdateState(string, bool);
	virtual char Delete(string);
};

#endif
