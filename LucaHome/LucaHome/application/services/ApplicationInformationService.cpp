#include "ApplicationInformationService.h"

/*===============PUBLIC==============*/

ApplicationInformationService::ApplicationInformationService() {}

ApplicationInformationService::~ApplicationInformationService() {}

void ApplicationInformationService::Initialize(string databaseName)
{
	_applicationInformationDatabase = ApplicationInformationDatabase(databaseName);
}

string ApplicationInformationService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	else if (action == ADD)
	{
		if (data.size() == APPLICATION_INFORMATION_DATA_SIZE)
		{
			char error = addApplicationInformation(data);
			if (!error)
			{
				return APPLICATION_INFORMATION_ADD_SUCCESS;
			}
			return APPLICATION_INFORMATION_ERROR_ADD;
		}
		return APPLICATION_INFORMATION_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == APPLICATION_INFORMATION_DATA_SIZE)
		{
			char error = updateApplicationInformation(data);
			if (!error)
			{
				return APPLICATION_INFORMATION_UPDATE_SUCCESS;
			}
			return APPLICATION_INFORMATION_ERROR_UPDATE;
		}
		return APPLICATION_INFORMATION_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteApplicationInformation(actionParameter);
		if (!error)
		{
			return APPLICATION_INFORMATION_DELETE_SUCCESS;
		}
		return APPLICATION_INFORMATION_ERROR_DELETE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void ApplicationInformationService::Dispose()
{
	_applicationInformationDatabase.Dispose();
}

/*==============PRIVATE==============*/

string ApplicationInformationService::getJsonString()
{
	vector<ApplicationInformation> applicationInformationList = _applicationInformationDatabase.GetList();

	stringstream data;
	for (int index = 0; index < applicationInformationList.size(); index++)
	{
		data << applicationInformationList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"ApplicationInformation\","
		<< "\"Action\":\"Get\","
		<< "\"Error\":0,"
		<< "\"Success\":true,"
		<< "\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char ApplicationInformationService::addApplicationInformation(vector<string> newApplicationInformationData)
{
	ApplicationInformation newApplicationInformation(
		newApplicationInformationData[APPLICATION_INFORMATION_KEY_INDEX].c_str(),
		newApplicationInformationData[APPLICATION_INFORMATION_VALUE_INDEX].c_str());
	return _applicationInformationDatabase.Insert(newApplicationInformation);
}

char ApplicationInformationService::updateApplicationInformation(vector<string> updateApplicationInformationData)
{
	ApplicationInformation updateApplicationInformation(
		updateApplicationInformationData[APPLICATION_INFORMATION_KEY_INDEX].c_str(),
		updateApplicationInformationData[APPLICATION_INFORMATION_VALUE_INDEX].c_str());
	return _applicationInformationDatabase.Update(updateApplicationInformation);
}

char ApplicationInformationService::deleteApplicationInformation(string deleteKey)
{
	return _applicationInformationDatabase.Delete(deleteKey);
}
