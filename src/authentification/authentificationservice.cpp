#include "authentificationservice.h"

/*===============PUBLIC==============*/

AuthentificationService::AuthentificationService() {
}

AuthentificationService::~AuthentificationService() {
}

void AuthentificationService::initialize(FileController fileController) {
	_fileController = fileController;
	_usersFile = "/etc/default/lucahome/users";
	_defaultPassword = "0000";
	loadUsers();
}

std::string AuthentificationService::getUsersString() {
	std::stringstream out;

	for (int index = 0; index < _users.size(); index++) {
		out << _users[index].toString();
	}

	return out.str();
}

std::vector<std::string> AuthentificationService::getUserNames() {
	std::vector < std::string > userNames;

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		userNames.push_back((*it).getName());
		++it;
	}

	return userNames;
}

bool AuthentificationService::authentificateUser(std::string userName, std::string password) {
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

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userName) {
			foundUser = true;

			if ((*it).getPassword() == password) {
				authentificationSuccess = true;
				(*it).setInvalidLoginCount(0);
			} else {
				syslog(LOG_INFO, "Entered wrong password for %s!",
						userName.c_str());
				(*it).increaseInvalidLoginCount();
			}

			break;
		} else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return authentificationSuccess;
}

bool AuthentificationService::authentificateUserAction(std::string userName, std::string password, std::string action) {
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

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userName) {
			foundUser = true;

			if ((*it).getPassword() == password) {
				if ((*it).getRole() >= actionId) {
					if(adminAction == 1) {
						if(isUserAdmin(userName)) {
							authentificationSuccess = true;
						} else {
							syslog(LOG_INFO, "Action not allowed for %s!",
									userName.c_str());
						}
					} else {
						authentificationSuccess = true;
					}
				} else {
					syslog(LOG_INFO, "Action not allowed for %s!",
							userName.c_str());
				}
			} else {
				syslog(LOG_INFO, "Entered wrong password for %s!",
						userName.c_str());
			}

			break;
		} else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return authentificationSuccess;
}

bool AuthentificationService::updatePassword(std::string currentUserName, std::string currentUserPassword, std::string userName, std::string newPassword) {
	if(!authentificateUser(currentUserName, currentUserPassword)){
		return false;
	}

	if(!isUserAdmin(currentUserName)){
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	if (userName == "DUMMY" || newPassword == "NO_PASSWORD") {
		syslog(LOG_INFO, "Dummy user or password cannot be used!");
		return false;
	}

	bool foundUser = false;
	bool error = true;

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userName) {
			foundUser = true;

			if ((*it).getPassword() != newPassword) {
				(*it).setPassword(newPassword);

				error = false;

				saveUsers();
				loadUsers();
			} else {
				syslog(LOG_INFO,
						"Could not update password of user %s! Password is equal to last!",
						userName.c_str());
			}

			break;
		} else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s to update password!",
				userName.c_str());
	}

	return foundUser && !error;
}

bool AuthentificationService::resetPassword(std::string currentUserName, std::string currentUserPassword, std::string userName) {
	if(!authentificateUser(currentUserName, currentUserPassword)){
		return false;
	}

	if(!isUserAdmin(currentUserName)){
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "reset password of user %s", userName.c_str());

	if (userName == "DUMMY") {
		syslog(LOG_INFO, "Dummy password cannot be reset!");
		return false;
	}

	return updatePassword(currentUserName, currentUserPassword, userName, _defaultPassword);
}

bool AuthentificationService::addUser(std::string currentUserName, std::string currentUserPassword, User newUser) {
	if(!authentificateUser(currentUserName, currentUserPassword)){
		return false;
	}

	if(!isUserAdmin(currentUserName)){
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "Add user %s", newUser.getName().c_str());

	if (newUser.getName() == "DUMMY" || newUser.getPassword() == "NO_PASSWORD" || newUser.getRole() == -1) {
		syslog(LOG_INFO, "Dummy user or password or role cannot be used!");
		return false;
	}

	bool error = false;

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == newUser.getName()) {
			syslog(LOG_INFO, "Could not add user %s! Name already existing!",
					newUser.getName().c_str());
			error = true;
			break;
		} else {
			++it;
		}
	}

	if (!error) {
		_users.push_back(newUser);
		saveUsers();
		loadUsers();
	}

	return !error;
}

bool AuthentificationService::deleteUser(std::string currentUserName, std::string currentUserPassword, std::string deleteUserName) {
	if(!authentificateUser(currentUserName, currentUserPassword)){
		return false;
	}

	if(!isUserAdmin(currentUserName)){
		syslog(LOG_INFO, "User is no admin!");
		return false;
	}

	syslog(LOG_INFO, "Delete user %s", deleteUserName.c_str());

	if (deleteUserName == "DUMMY") {
		syslog(LOG_INFO, "Dummy user cannot be deleted!");
		return false;
	}

	bool foundUser = false;

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == deleteUserName) {
			foundUser = true;
			it = _users.erase(it);
			saveUsers();
			loadUsers();
			break;
		} else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s to delete!",
				deleteUserName.c_str());
	}

	return foundUser;
}

std::string AuthentificationService::ResetFailedLogin(std::string currentUserName, std::string currentUserPassword, std::string userToReset) {
	if(!authentificateUser(currentUserName, currentUserPassword)){
		return "Error 15:Could not reset invalid login count";
	}

	if(!isUserAdmin(currentUserName)){
		return "Error 15:Could not reset invalid login count";
	}

	if(userToReset == ""){
		return "Error 15:Could not reset invalid login count";
	}

	bool foundUser = false;

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userToReset) {
			foundUser = true;

			(*it).setInvalidLoginCount(0);

			break;
		} else {
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
	std::string xmldata = _xmlService.generateUsersXml(_users);
	_fileController.saveFile(_usersFile, xmldata);
}

void AuthentificationService::loadUsers() {
	std::string usersString = _fileController.readFile(_usersFile);
	_xmlService.setContent(usersString);
	_users = _xmlService.getUsers();
}

int AuthentificationService::getActionId(std::string action) {
	if (action == "AVAILABILITY" || action == "CHECK" || action == "COUNT" || action == "GET" || action == "VALIDATE") {
		return 1;
	} else if (action == "ACTIVATE" || action == "PLAY" || action == "SET" || action == "START" || action == "STOP") {
		return 2;
	} else if (action == "ADD" || action == "UPDATE") {
		return 3;
	} else if (action == "CLEAR" || action == "DEACTIVATE" || action == "DELETE") {
		return 4;
	} else if (action == "SETCONTROLTASK" || action == "SYSTEM") {
		return 5;
	}
	return -1;
}

int AuthentificationService::isAdminAction(std::string action) {
	if (action == "AVAILABILITY" || action == "CHECK" || action == "COUNT"
			|| action == "GET" || action == "VALIDATE" ||action == "ACTIVATE"
			|| action == "PLAY" || action == "SET" || action == "START"
			|| action == "STOP" || action == "ADD" || action == "UPDATE"
			|| action == "CLEAR" || action == "DEACTIVATE"
			|| action == "DELETE") {
		return 0;
	} else if (action == "SETCONTROLTASK" || action == "SYSTEM") {
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

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userName) {
			foundUser = true;

			if((*it).isAdmin() == 1) {
				isAdmin = true;
			} else {
				isAdmin = false;
			}

			break;
		} else {
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

	std::vector<User>::iterator it = _users.begin();
	while (it != _users.end()) {
		if ((*it).getName() == userName) {
			foundUser = true;

			invalidLoginCount = (*it).getInvalidLoginCount();

			break;
		} else {
			++it;
		}
	}

	if (!foundUser) {
		syslog(LOG_INFO, "Did not found user %s!", userName.c_str());
	}

	return invalidLoginCount;
}
