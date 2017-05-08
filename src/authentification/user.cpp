#include "user.h"

User::User() {
	_name = "DUMMY";
	_password = "NO_PASSWORD";
	_role = -1;
	_isAdmin = -1;
	_invalidLoginCount = -1;
}

User::User(std::string name, std::string password, int role, int isAdmin, int invalidLoginCount) {
	_name = name;
	_password = password;
	_role = role;
	_isAdmin = isAdmin;
	_invalidLoginCount = invalidLoginCount;
}

User::~User() {
}

void User::setName(std::string name) {
	_name = name;
}

void User::setPassword(std::string password) {
	_password = password;
}

void User::setRole(int role) {
	_role = role;
}

void User::setIsAdmin(int isAdmin) {
	_isAdmin = isAdmin;
}

void User::setInvalidLoginCount(int invalidLoginCount) {
	_invalidLoginCount = invalidLoginCount;
}

void User::increaseInvalidLoginCount() {
	_invalidLoginCount++;
}

std::string User::getName() {
	return _name;
}

std::string User::getPassword() {
	return _password;
}

int User::getRole() {
	return _role;
}

int User::isAdmin() {
	return _isAdmin;
}

int User::getInvalidLoginCount() {
	return _invalidLoginCount;
}

std::string User::toString() {
	std::string str = std::string("User { name: ") + _name
			+ std::string("; password: NO :P")
			+ std::string("; role: ") + Tools::convertIntToStr(_role)
			+ std::string("; invalidLoginCount: ") + Tools::convertIntToStr(_invalidLoginCount)
			+ std::string(" }");
	return str;
}
