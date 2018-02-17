#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef USER_H
#define USER_H

class User
{
private:
	string _uuid;
	string _name;
	string _passphrase;
	int _role;
	bool _isAdmin;
	int _invalidLoginCount;

public:
	User();
	User(string, string, string, int, bool, int);
	~User();

	string GetUuid();
	string GetName();
	string GetPassphrase();
	int GetRole();
	bool IsAdmin();

	void SetInvalidLoginCount(int);
	void IncreaseInvalidLoginCount();
	int GetInvalidLoginCount();

	string ToString();
};

#endif
