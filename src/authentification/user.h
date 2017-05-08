#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../common/tools.h"

#ifndef USER_H
#define USER_H

class User {

private:
	std::string _name;
	std::string _password;
	int _role;
	int _isAdmin;
	int _invalidLoginCount;

public:
	User();
	User(std::string, std::string, int, int, int);
	~User();

	void setName(std::string);
	void setPassword(std::string);
	void setRole(int);
	void setIsAdmin(int);
	void setInvalidLoginCount(int);
	void increaseInvalidLoginCount();

	std::string getName();
	std::string getPassword();
	int getRole();
	int isAdmin();
	int getInvalidLoginCount();

	std::string toString();
};

#endif
