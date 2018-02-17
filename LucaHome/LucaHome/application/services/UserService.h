#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/databases/UserDatabase.h"
#include "../../domain/classes/User.h"

using namespace std;

#ifndef USER_SERVICE_H
#define USER_SERVICE_H

class UserService {
private:
	UserDatabase _userDatabase;

	char addUser(vector<string>);
	char updateUser(vector<string>);
	char deleteUser(vector<string>);

	int getActionId(string);
	bool isAdminAction(string);
	bool isUserAdmin(string);

public:
	UserService();
	~UserService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	bool AuthentificateUser(string, string);
	bool AuthentificateUserAction(string, string, string);
};

#endif
