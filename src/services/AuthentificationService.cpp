#include "AuthentificationService.h"

/*===============PUBLIC==============*/

AuthentificationService::AuthentificationService() {
}

AuthentificationService::~AuthentificationService() {
}

void AuthentificationService::Initialize(FileController fileController) {
	_fileController = fileController;
	_userFile = "/etc/default/lucahome/users";
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
	if (userName == "DUMMY" || password == "NO_PASSWORD") {
		syslog(LOG_INFO, "Dummy user or password cannot be used!");
		return false;
	}

	int failedUserLogins = getInvalidLoginCount(userName);
	if (failedUserLogins >= MAX_INVALID_LOGIN_COUNT || failedUserLogins == -1) {
		syslog(LOG_INFO, "Too many invalid login tries!");
		return false;
	}

	bool foundUser = false;
	bool authentificationSuccess = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			foundUser = true;

			if ((*it).GetPassword() == password) {
				authentificationSuccess = true;
				(*it).SetInvalidLoginCount(0);
			}
			else {
				syslog(LOG_INFO, "Entered wrong password for %s!", userName.c_str());
				(*it).IncreaseInvalidLoginCount();
			}

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return authentificationSuccess;
}

bool AuthentificationService::AuthentificateUserAction(std::string userName, std::string password, std::string action) {
	if (userName == "DUMMY" || password == "NO_PASSWORD") {
		syslog(LOG_INFO, "Dummy user or password cannot be used!");
		return false;
	}

	int actionId = -1;
	actionId = getActionId(action);
	if (actionId == -1 || actionId > 5) {
		return false;
	}

	int adminAction = -1;
	adminAction = isAdminAction(action);
	if (adminAction == -1 || adminAction > 1) {
		return false;
	}

	bool foundUser = false;
	bool authentificationSuccess = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			foundUser = true;

			if ((*it).GetPassword() == password) {
				if ((*it).GetRole() >= actionId) {
					if (adminAction == 1) {
						if (isUserAdmin(userName)) {
							authentificationSuccess = true;
						}
						else {
							syslog(LOG_INFO, "Action not allowed for %s!", userName.c_str());
						}
					}
					else {
						authentificationSuccess = true;
					}
				}
				else {
					syslog(LOG_INFO, "Action not allowed for %s!", userName.c_str());
				}
			}
			else {
				syslog(LOG_INFO, "Entered wrong password for %s!", userName.c_str());
			}

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return authentificationSuccess;
}

bool AuthentificationService::UpdatePassword(std::string currentUserName, std::string currentUserPassword, std::string userName, std::string newPassword) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	if (userName == "DUMMY" || newPassword == "NO_PASSWORD") {
		syslog(LOG_INFO, "Dummy user or password cannot be used!");
		return false;
	}

	bool foundUser = false;
	bool error = true;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			foundUser = true;

			if ((*it).GetPassword() != newPassword) {
				(*it).SetPassword(newPassword);

				error = false;

				saveUsers();
				loadUsers();
			}
			else {
				syslog(LOG_INFO, "Could not update password of user %s! Password is equal to last!", userName.c_str());
			}

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s to update password!", userName.c_str());
	}

	return foundUser && !error;
}

bool AuthentificationService::ResetPassword(std::string currentUserName, std::string currentUserPassword, std::string userName) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "reset password of user %s", userName.c_str());

	if (userName == "DUMMY") {
		syslog(LOG_INFO, "Dummy password cannot be reset!");
		return false;
	}

	return UpdatePassword(currentUserName, currentUserPassword, userName, DEFAULT_PASSWORD);
}

bool AuthentificationService::AddUser(std::string currentUserName, std::string currentUserPassword, UserDto newUser) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "Add user %s", newUser.GetName().c_str());

	if (newUser.GetName() == "DUMMY" || newUser.GetPassword() == "NO_PASSWORD" || newUser.GetRole() == -1) {
		syslog(LOG_INFO, "Dummy user or password or role cannot be used!");
		return false;
	}

	bool error = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == newUser.GetName()) {
			syslog(LOG_INFO, "Could not add user %s! Name already existing!", newUser.GetName().c_str());
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

	if (!isUserAdmin(currentUserName)) {
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "Delete user %s", deleteUserName.c_str());

	if (deleteUserName == "DUMMY") {
		syslog(LOG_INFO, "Dummy user cannot be deleted!");
		return false;
	}

	bool foundUser = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == deleteUserName) {
			foundUser = true;
			it = _userList.erase(it);
			saveUsers();
			loadUsers();
			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s to delete!", deleteUserName.c_str());
	}

	return foundUser;
}

std::string AuthentificationService::ResetFailedLogin(std::string currentUserName, std::string currentUserPassword, std::string userToReset) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return "Error 15:Could not reset invalid login count";
	}

	if (!isUserAdmin(currentUserName)) {
		return "Error 15:Could not reset invalid login count";
	}

	if (userToReset == "") {
		return "Error 15:Could not reset invalid login count";
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
		return "Error 15:Could not reset invalid login count";
	}

	return "ResetFailedLogin:1";
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
	if (action == "AVAILABILITY" || action == "CHECK" || action == "COUNT" || action == "GET" || action == "VALIDATE") {
		return 1;
	}
	else if (action == "ACTIVATE" || action == "PLAY" || action == "SET" || action == "START" || action == "STOP") {
		return 2;
	}
	else if (action == "ADD" || action == "UPDATE") {
		return 3;
	}
	else if (action == "CLEAR" || action == "DEACTIVATE" || action == "DELETE") {
		return 4;
	}
	else if (action == "SETCONTROLTASK" || action == "SYSTEM") {
		return 5;
	}
	return -1;
}

int AuthentificationService::isAdminAction(std::string action) {
	if (action == "AVAILABILITY" || action == "CHECK" || action == "COUNT"
		|| action == "GET" || action == "VALIDATE" || action == "ACTIVATE"
		|| action == "PLAY" || action == "SET" || action == "START"
		|| action == "STOP" || action == "ADD" || action == "UPDATE"
		|| action == "CLEAR" || action == "DEACTIVATE"
		|| action == "DELETE") {
		return 0;
	}
	else if (action == "SETCONTROLTASK" || action == "SYSTEM") {
		return 1;
	}
	return -1;
}

bool AuthentificationService::isUserAdmin(std::string userName) {
	if (userName == "DUMMY") {
		syslog(LOG_INFO, "Dummy user cannot be used!");
		return false;
	}

	bool foundUser = false;
	bool isAdmin = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			foundUser = true;

			if ((*it).IsAdmin() == 1) {
				isAdmin = true;
			}
			else {
				isAdmin = false;
			}

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return isAdmin;
}

int AuthentificationService::getInvalidLoginCount(std::string userName) {
	if (userName == "DUMMY") {
		syslog(LOG_INFO, "Dummy user cannot be used!");
		return -1;
	}

	bool foundUser = false;
	int invalidLoginCount = -1;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			foundUser = true;

			invalidLoginCount = (*it).GetInvalidLoginCount();

			break;
		}
		else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return invalidLoginCount;
}
