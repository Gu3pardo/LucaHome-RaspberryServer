#include "ITemplateDatabase.h"
#include "../../domain/classes/WirelessSchedule.h"

using namespace std;

#ifndef WIRELESS_SCHEDULE_DATABASE_H
#define WIRELESS_SCHEDULE_DATABASE_H

class WirelessScheduleDatabase : public ITemplateDatabase<WirelessSchedule>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseWirelessScheduleListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyWeekday = "_weekday";
	string _keyHour = "_hour";
	string _keyMinute = "_minute";
	string _keyIsActive = "_isActive";
	string _keyWirelessSocketUuid = "_wirelessSocketUuid";
	string _keyWirelessSocketAction = "_wirelessSocketAction";
	string _keyWirelessSwitchUuid = "_wirelessSwitchUuid";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	WirelessScheduleDatabase();
	WirelessScheduleDatabase(string);
	~WirelessScheduleDatabase();

	virtual char Dispose();

	virtual vector<WirelessSchedule> GetList();

	virtual char Insert(int, WirelessSchedule);
	virtual char Update(WirelessSchedule);
	virtual char UpdateState(string, bool);
	virtual char Delete(string);
};

#endif
