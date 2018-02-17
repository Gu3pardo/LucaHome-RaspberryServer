#include "AuthentificationService.h"

/*===============PUBLIC==============*/

AuthentificationService::AuthentificationService()
{
}

AuthentificationService::~AuthentificationService()
{
}

void AuthentificationService::Initialize(string databaseName)
{
	_userDatabase = UserDatabase(databaseName);
}

string AuthentificationService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (!isUserAdmin(username)) {
		return AUTHENTIFICATION_ERROR_NO_ADMIN;
	}

	if (action == ADD)
	{
		if (data.size() == USER_DATA_SIZE)
		{
			char error = addUser(data);
			if (!error)
			{
				return USER_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return USER_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == USER_DATA_SIZE)
		{
			char error = updateUser(data);
			if (!error)
			{
				return USER_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return USER_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		if (data.size() == USER_DATA_SIZE)
		{
			char error = deleteUser(data);
			if (!error)
			{
				return USER_DELETE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return USER_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void AuthentificationService::Dispose() {
	_userDatabase.Dispose();
}

bool AuthentificationService::AuthentificateUser(string userName, string passphrase) {
	if (userName == DUMMY || passphrase == NO_PASSWORD) {
		return false;
	}

	vector<User> userList = _userDatabase.GetList();

	for (int index = 0; index < userList.size(); index++) {
		User user = userList[index];
		if (user.GetName() == userName) {
			if (user.GetInvalidLoginCount() >= MAX_INVALID_LOGIN_COUNT) {
				return false;
			}

			if (user.GetPassphrase() == passphrase) {
				user.SetInvalidLoginCount(0);
			}
			else {
				user.IncreaseInvalidLoginCount();
			}

			_userDatabase.Update(user);
			return true;
		}
	}

	return false;
}

bool AuthentificationService::AuthentificateUserAction(string userName, string passphrase, string action) {
	if (userName == DUMMY || passphrase == NO_PASSWORD) {
		return false;
	}

	int actionId = -1;
	actionId = getActionId(action);
	if (actionId == ACTION_LEVEL_ERROR || actionId > ACTION_LEVEL_SYSTEM) {
		return false;
	}

	vector<User> userList = _userDatabase.GetList();

	for (int index = 0; index < userList.size(); index++) {
		User user = userList[index];
		if (user.GetName() == userName) {
			if (user.GetInvalidLoginCount() >= MAX_INVALID_LOGIN_COUNT) {
				return false;
			}

			if (user.GetPassphrase() == passphrase) {
				if (user.GetRole() >= actionId) {
					if (isAdminAction(action)) {
						if (isUserAdmin(userName)) {
							return true;
						}
					}
					else {
						return true;
					}
				}
			}

			return false;
		}
	}

	return false;
}

/*==============PRIVATE==============*/

char AuthentificationService::addUser(vector<string> newUserData)
{
	User newUser(
		newUserData[COIN_UUID_INDEX].c_str(),
		newUserData[USER_NAME_INDEX].c_str(),
		newUserData[USER_PASSPHRASE_INDEX].c_str(),
		Tools::ConvertStrToDouble(newUserData[USER_ROLE_INDEX].c_str()),
		Tools::ConvertStrToBool(newUserData[USER_IS_ADMIN_INDEX].c_str()),
		Tools::ConvertStrToDouble(newUserData[USER_INVALID_LOGIN_COUNT_INDEX].c_str()));
	return _userDatabase.Insert(_userDatabase.GetList().size(), newUser);
}

char AuthentificationService::updateUser(vector<string> updateUserData)
{
	User updateUser(
		updateUserData[COIN_UUID_INDEX].c_str(),
		updateUserData[USER_NAME_INDEX].c_str(),
		updateUserData[USER_PASSPHRASE_INDEX].c_str(),
		Tools::ConvertStrToDouble(updateUserData[USER_ROLE_INDEX].c_str()),
		Tools::ConvertStrToBool(updateUserData[USER_IS_ADMIN_INDEX].c_str()),
		Tools::ConvertStrToDouble(updateUserData[USER_INVALID_LOGIN_COUNT_INDEX].c_str()));
	return _userDatabase.Update(updateUser);
}

char AuthentificationService::deleteUser(vector<string> deleteUserData)
{
	User deleteUser(
		deleteUserData[COIN_UUID_INDEX].c_str(),
		deleteUserData[USER_NAME_INDEX].c_str(),
		deleteUserData[USER_PASSPHRASE_INDEX].c_str(),
		Tools::ConvertStrToDouble(deleteUserData[USER_ROLE_INDEX].c_str()),
		Tools::ConvertStrToBool(deleteUserData[USER_IS_ADMIN_INDEX].c_str()),
		Tools::ConvertStrToDouble(deleteUserData[USER_INVALID_LOGIN_COUNT_INDEX].c_str()));
	return _userDatabase.Delete(deleteUser);
}

int AuthentificationService::getActionId(string action) {
	if (action == AVAILABILITY || action == CHECK || action == COUNT || action == GET || action == VALIDATE || action == RELOAD) {
		return ACTION_LEVEL_LOW;
	}
	else if (action == ACTIVATE || action == PLAY || action == SET || action == START || action == STOP || action == TOGGLE) {
		return ACTION_LEVEL_MEDIUM;
	}
	else if (action == ADD || action == UPDATE) {
		return ACTION_LEVEL_NORMAL;
	}
	else if (action == CLEAR || action == DEACTIVATE || action == DELETE) {
		return ACTION_LEVEL_CRIT;
	}
	else if (action == RESETFAILEDLOGIN || action == SETCONTROLTASK) {
		return ACTION_LEVEL_SYSTEM;
	}
	return ACTION_LEVEL_ERROR;
}

bool AuthentificationService::isAdminAction(string action) {
	if (action == AVAILABILITY || action == CHECK || action == COUNT
		|| action == GET || action == VALIDATE || action == ACTIVATE
		|| action == PLAY || action == SET || action == START || action == TOGGLE
		|| action == STOP || action == ADD || action == UPDATE
		|| action == CLEAR || action == DEACTIVATE
		|| action == DELETE || action == RELOAD) {
		return false;
	}
	else if (action == RESETFAILEDLOGIN || action == SETCONTROLTASK) {
		return true;
	}
	return true;
}

bool AuthentificationService::isUserAdmin(string userName) {
	if (userName == DUMMY) {
		return false;
	}

	vector<User> userList = _userDatabase.GetList();

	for (int index = 0; index < userList.size(); index++) {
		User user = userList[index];
		if (user.GetName() == userName) {
			if (user.GetInvalidLoginCount() >= MAX_INVALID_LOGIN_COUNT) {
				return false;
			}

			if (user.IsAdmin()) {
				return true;
			}

			return false;
		}
	}

	return false;
}
