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
#include "../../dataaccess/controller/MailController.h"
#include "../../dataaccess/databases/BirthdayDatabase.h"
#include "../../domain/classes/Birthday.h"

using namespace std;

#ifndef BIRTHDAY_SERVICE_H
#define BIRTHDAY_SERVICE_H

class BirthdayService
{
private:
	BirthdayDatabase _birthdayDatabase;

	string getJsonString();

	char addBirthday(vector<string>);
	char updateBirthday(vector<string>);
	char deleteBirthday(string);

public:
	BirthdayService();
	~BirthdayService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	void CheckBirthdayList(MailController);
};

#endif
