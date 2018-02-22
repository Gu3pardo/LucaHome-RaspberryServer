#include "ChangeService.h"

/*===============PUBLIC==============*/

ChangeService::ChangeService() {}

ChangeService::~ChangeService() {}

void ChangeService::Initialize(string databaseName)
{
	_changeDatabase = ChangeDatabase(databaseName);
}

string ChangeService::PerformAction(vector<string> data)
{
	string action = data[ACTION_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void ChangeService::Dispose()
{
	_changeDatabase.Dispose();
}

void ChangeService::UpdateChange(string type, string userName)
{
	vector<Change> changeList = _changeDatabase.GetList();
	for (int index = 0; index < changeList.size(); index++)
	{
		Change change = changeList[index];
		if (change.GetType() == type)
		{
			change.SetTime(time(0));
			change.SetUserName(userName);
			_changeDatabase.Update(change);
			break;
		}
	}
}

/*==============PRIVATE==============*/

string ChangeService::getJsonString()
{
	vector<Change> changeList = _changeDatabase.GetList();

	stringstream data;
	for (int index = 0; index < changeList.size(); index++)
	{
		data << changeList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}