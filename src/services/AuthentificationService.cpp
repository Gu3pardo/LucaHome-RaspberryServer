#include "AuthentificationService.h"

/*===============PUBLIC==============*/

AuthentificationService::AuthentificationService() {
}

AuthentificationService::~AuthentificationService() {
}

void AuthentificationService::Initialize(FileController fileController, std::string userFile) {
	_fileController = fileController;
	_userFile = userFile;
	loadUsers();
}

std::string AuthentificationService::GetUsersString() {
	std::stringstream out;

	for (int index = 0; index < _userList.size(); index++) {
		out << _userList[index].ToString();
	}

	return out.str();
}

std::vector<std::string> AuthentificationService::GetUserNames() {
	std::vector < std::string > userNames;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		userNames.push_back((*it).GetName());
		++it;
	}

	return userNames;
}

bool AuthentificationService::AuthentificateUser(std::string userName, std::string password) {
	if (userName == DUMMY || password == NO_PASSWORD) {
		return false;
	}

	int failedUserLogins = getInvalidLoginCount(userName);
	if (failedUserLogins >= MAX_INVALID_LOGIN_COUNT || failedUserLogins == -1) {
		return false;
	}

	bool authentificationSuccess = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			if ((*it).GetPassword() == password) {
				authentificationSuccess = true;
				(*it).SetInvalidLoginCount(0);
			}
			else {
				(*it).IncreaseInvalidLoginCount();
			}

			break;
		}
		else {
			++it;
		}
	}

	return authentificationSuccess;
}

bool AuthentificationService::AuthentificateUserAction(std::string userName, std::string password, std::string action) {
	if (userName == DUMMY || password == NO_PASSWORD) {
		return false;
	}

	int actionId = -1;
	actionId = getActionId(action);
	if (actionId == ACTION_LEVEL_ERROR || actionId > ACTION_LEVEL_SYSTEM) {
		return false;
	}

	bool authentificationSuccess = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			if ((*it).GetPassword() == password) {
				if ((*it).GetRole() >= actionId) {
					if (isAdminAction(action)) {
						if (IsUserAdmin(userName)) {
							authentificationSuccess = true;
						}
					}
					else {
						authentificationSuccess = true;
					}
				}
			}

			break;
		}
		else {
			++it;
		}
	}

	return authentificationSuccess;
}

bool AuthentificationService::AddUser(std::string currentUserName, std::string currentUserPassword, UserDto newUser) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!IsUserAdmin(currentUserName)) {
		return false;
	}

	if (newUser.GetName() == DUMMY || newUser.GetPassword() == NO_PASSWORD || newUser.GetRole() == -1) {
		return false;
	}

	bool error = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == newUser.GetName()) {
			error = true;
			break;
		}
		else {
			++it;
		}
	}

	if (!error) {
		_userList.push_back(newUser);
		saveUsers();
		loadUsers();
	}

	return !error;
}

bool AuthentificationService::DeleteUser(std::string currentUserName, std::string currentUserPassword, std::string deleteUserName) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!IsUserAdmin(currentUserName)) {
		return false;
	}

	if (deleteUserName == DUMMY) {
		return false;
	}

	bool foundUser = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == deleteUserName) {
			it = _userList.erase(it);
			saveUsers();
			loadUsers();
			foundUser = true;
			break;
		}
		else {
			++it;
		}
	}

	return foundUser;
}

std::string AuthentificationService::ResetFailedLogin(std::string currentUserName, std::string currentUserPassword, std::string userToReset) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return AUTHENTIFICATION_ERROR_NR_15;
	}

	if (!IsUserAdmin(currentUserName)) {
		return AUTHENTIFICATION_ERROR_NR_15;
	}

	if (userToReset == "") {
		return AUTHENTIFICATION_ERROR_NR_15;
	}

	bool foundUser = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userToReset) {
			foundUser = true;

			(*it).SetInvalidLoginCount(0);

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		return AUTHENTIFICATION_ERROR_NR_15;
	}

	return AUTHENTIFICATION_RESET_FAILED_LOGIN_COUNT_SUCCESS;
}

bool AuthentificationService::IsUserAdmin(std::string userName) {
	if (userName == DUMMY) {
		return false;
	}

	bool isAdmin = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			isAdmin = (*it).IsAdmin();
			break;
		}
		else {
			++it;
		}
	}

	return isAdmin;
}

/*==============PRIVATE==============*/

void AuthentificationService::saveUsers() {
	std::string xmldata = _xmlService.GenerateUsersXml(_userList);
	_fileController.SaveFile(_userFile, xmldata);
}

void AuthentificationService::loadUsers() {
	std::string _userFileContent = _fileController.ReadFile(_userFile);
	_userList = _xmlService.GetUserList(_userFileContent);
}

int AuthentificationService::getActionId(std::string action) {
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
	else if (action == RESETFAILEDLOGIN || action == SETCONTROLTASK || action == SYSTEM) {
		return ACTION_LEVEL_SYSTEM;
	}
	return ACTION_LEVEL_ERROR;
}

bool AuthentificationService::isAdminAction(std::string action) {
	if (action == AVAILABILITY || action == CHECK || action == COUNT
		|| action == GET || action == VALIDATE || action == ACTIVATE
		|| action == PLAY || action == SET || action == START || action == TOGGLE
		|| action == STOP || action == ADD || action == UPDATE
		|| action == CLEAR || action == DEACTIVATE
		|| action == DELETE || action == RELOAD) {
		return false;
	}
	else if (action == RESETFAILEDLOGIN || action == SETCONTROLTASK || action == SYSTEM) {
		return true;
	}
	return true;
}

int AuthentificationService::getInvalidLoginCount(std::string userName) {
	if (userName == DUMMY) {
		return -1;
	}

	int invalidLoginCount = -1;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			invalidLoginCount = (*it).GetInvalidLoginCount();

			break;
		}
		else {
			++it;
		}
	}

	return invalidLoginCount;
}
