#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../crosscutting/Constants.h"
#include "../../dataaccess/databases/UserDatabase.h"
#include "../../domain/classes/User.h"

using namespace std;

#ifndef AUTHENTIFICATION_SERVICE_H
#define AUTHENTIFICATION_SERVICE_H

class AuthentificationService {
private:
	UserDatabase _userDatabase;

	char addUser(vector<string>);
	char updateUser(vector<string>);
	char deleteUser(vector<string>);

	int getActionId(string);
	bool isAdminAction(string);
	bool isUserAdmin(string);

public:
	AuthentificationService();
	~AuthentificationService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	bool AuthentificateUser(string, string);
	bool AuthentificateUserAction(string, string, string);
};

#endif
