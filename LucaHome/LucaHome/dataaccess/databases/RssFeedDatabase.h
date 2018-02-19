#include "ITemplateDatabase.h"
#include "../../domain/classes/RssFeed.h"

using namespace std;

#ifndef RSS_FEED_DATABASE_H
#define RSS_FEED_DATABASE_H

class RssFeedDatabase : public ITemplateDatabase<RssFeed>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseRssFeedListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTitle = "_title";
	string _keyUrl = "_url";
	string _keyPlayCount = "_playCount";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	RssFeedDatabase();
	RssFeedDatabase(string);
	~RssFeedDatabase();

	virtual char Dispose();

	virtual vector<RssFeed> GetList();

	virtual char Insert(int, RssFeed);
	virtual char Update(RssFeed);
	virtual char Delete(string);
};

#endif
