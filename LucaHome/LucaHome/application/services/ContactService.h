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
#include "../../dataaccess/databases/ContactDatabase.h"
#include "../../domain/classes/Contact.h"

using namespace std;

#ifndef CONTACT_SERVICE_H
#define CONTACT_SERVICE_H

class ContactService
{
private:
	ContactDatabase _contactDatabase;
	MailController _mailController;

	string getJsonString();

	char addContact(vector<string>);
	char updateContact(vector<string>);
	char deleteContact(string);

	string writeMailToContact(vector<string>);

public:
	ContactService();
	~ContactService();

	void Initialize(string, MailController);
	string PerformAction(vector<string>);
	void Dispose();

	void CheckContactBirthdayList();
};

#endif
