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
	if (userName == "DUMMY" || password == "NO_PASSWORD") {
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
	if (userName == "DUMMY" || password == "NO_PASSWORD") {
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

	bool authentificationSuccess = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
			if ((*it).GetPassword() == password) {
				if ((*it).GetRole() >= actionId) {
					if (adminAction == 1) {
						if (isUserAdmin(userName)) {
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

bool AuthentificationService::UpdatePassword(std::string currentUserName, std::string currentUserPassword, std::string userName, std::string newPassword) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		return false;
	}

	if (userName == "DUMMY" || newPassword == "NO_PASSWORD") {
		return false;
	}

	bool error = true;
	bool foundUser = false;

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

			break;
		}
		else {
			++it;
		}
	}

	return foundUser && !error;
}

bool AuthentificationService::ResetPassword(std::string currentUserName, std::string currentUserPassword, std::string userName) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		return false;
	}

	if (userName == "DUMMY") {
		return false;
	}

	return UpdatePassword(currentUserName, currentUserPassword, userName, DEFAULT_PASSWORD);
}

bool AuthentificationService::AddUser(std::string currentUserName, std::string currentUserPassword, UserDto newUser) {
	if (!AuthentificateUser(currentUserName, currentUserPassword)) {
		return false;
	}

	if (!isUserAdmin(currentUserName)) {
		return false;
	}

	if (newUser.GetName() == "DUMMY" || newUser.GetPassword() == "NO_PASSWORD" || newUser.GetRole() == -1) {
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

	if (!isUserAdmin(currentUserName)) {
		return false;
	}

	if (deleteUserName == "DUMMY") {
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
		return false;
	}

	bool isAdmin = false;

	std::vector<UserDto>::iterator it = _userList.begin();
	while (it != _userList.end()) {
		if ((*it).GetName() == userName) {
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

	return isAdmin;
}

int AuthentificationService::getInvalidLoginCount(std::string userName) {
	if (userName == "DUMMY") {
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
