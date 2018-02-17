#include "ITemplateDatabase.h"
#include "../../domain/classes/YoutubeVideo.h";

using namespace std;

#ifndef YOUTUBE_VIDEO_DATABASE_H
#define YOUTUBE_VIDEO_DATABASE_H

class YoutubeVideoDatabase : public ITemplateDatabase<YoutubeVideo>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseYoutubeVideoListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyTitle = "_title";
	string _keyYoutubeId = "_youtubeId";
	string _keyPlayCount = "_playCount";
	string _keyDescription = "_description";
	string _keyMediumImageUrl = "_mediumImageUrl";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	YoutubeVideoDatabase(string);
	~YoutubeVideoDatabase();

	virtual char Dispose();

	virtual vector<YoutubeVideo> GetList();

	virtual char Insert(int, YoutubeVideo);
	virtual char Update(YoutubeVideo);
	virtual char Delete(YoutubeVideo);
};

#endif
