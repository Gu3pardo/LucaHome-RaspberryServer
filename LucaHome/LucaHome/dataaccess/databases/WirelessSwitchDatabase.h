#include "ITemplateDatabase.h"
#include "../../domain/classes/WirelessSwitch.h"

using namespace std;

#ifndef WIRELESS_SWITCH_DATABASE_H
#define WIRELESS_SWITCH_DATABASE_H

class WirelessSwitchDatabase : public ITemplateDatabase<WirelessSwitch>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseWirelessSwitchListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyRoomUuid = "_roomUuid";
	string _keyName = "_name";
	string _keyRemoteId = "_remoteId";
	string _keyKeyCode = "_keycode";
	string _keyAction = "_action";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	WirelessSwitchDatabase();
	WirelessSwitchDatabase(string);
	~WirelessSwitchDatabase();

	virtual char Dispose();

	virtual vector<WirelessSwitch> GetList();
	virtual WirelessSwitch GetByUuid(string);

	virtual char Insert(int, WirelessSwitch);
	virtual char Update(WirelessSwitch);
	virtual char UpdateAction(string, bool);
	virtual char Delete(string);
};

#endif
