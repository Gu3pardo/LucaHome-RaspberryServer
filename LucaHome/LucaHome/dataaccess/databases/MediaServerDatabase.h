#include "ITemplateDatabase.h"
#include "../../domain/classes/MediaServer.h"

using namespace std;

#ifndef MEDIASERVER_DATABASE_H
#define MEDIASERVER_DATABASE_H

class MediaServerDatabase : public ITemplateDatabase<MediaServer>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseMediaServerListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyRoomUuid = "_roomUuid";
	string _keyIp = "_ip";
	string _keyIsSleepingServer = "_isSleepingServer";
	string _keyWirelessSocketUuid = "_wirelessSocketUuid";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	MediaServerDatabase();
	MediaServerDatabase(string);
	~MediaServerDatabase();

	virtual char Dispose();

	virtual vector<MediaServer> GetList();

	virtual char Insert(int, MediaServer);
	virtual char Update(MediaServer);
	virtual char Delete(string);
};

#endif
