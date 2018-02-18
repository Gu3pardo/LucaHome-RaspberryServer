#include "ITemplateDatabase.h"
#include "../../domain/classes/WirelessTimer.h";

using namespace std;

#ifndef WIRELESS_TIMER_DATABASE_H
#define WIRELESS_TIMER_DATABASE_H

class WirelessTimerDatabase : public ITemplateDatabase<WirelessTimer>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseWirelessTimerListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyWeekday = "_weekday";
	string _keyHour = "_hour";
	string _keyMinute = "_minute";
	string _keyWirelessSocketUuid = "_wirelessSocketUuid";
	string _keyWirelessSocketAction = "_wirelessSocketAction";
	string _keyWirelessSwitchUuid = "_wirelessSwitchUuid";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	WirelessTimerDatabase();
	WirelessTimerDatabase(string);
	~WirelessTimerDatabase();

	virtual char Dispose();

	virtual vector<WirelessTimer> GetList();

	virtual char Insert(int, WirelessTimer);
	virtual char Update(WirelessTimer);
	virtual char Delete(string);
};

#endif
