#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef CONTACT_H
#define CONTACT_H

class Contact
{
private:
	string _uuid;
	string _name;
	string _group;
	string _address;
	string _phoneHome;
	string _phoneMobile;
	string _email;
	int _birthdayDay;
	int _birthdayMonth;
	int _birthdayYear;
	bool _birthdayRemindMe;
	bool _birthdaySentReminder;

public:
	Contact();
	Contact(string, string, string, string, string, string, string, int, int, int, bool, bool);
	~Contact();

	void SetUuid(string);
	string GetUuid();

	void SetName(string);
	string GetName();

	void SetGroup(string);
	string GetGroup();

	void SetAddress(string);
	string GetAddress();

	void SetPhoneHome(string);
	string GetPhoneHome();

	void SetPhoneMobile(string);
	string GetPhoneMobile();

	void SetEMail(string);
	string GetEMail();

	void SetBirthdayDay(int);
	int GetBirthdayDay();

	void SetBirthdayMonth(int);
	int GetBirthdayMonth();

	void SetBirthdayYear(int);
	int GetBirthdayYear();

	int GetAge();
	bool HasBirthday();

	void SetBirthdayRemindMe(bool);
	bool GetBirthdayRemindMe();

	void SetBirthdaySentReminder(bool);
	bool GetBirthdaySentReminder();

	string JsonString();
	string ToString();
};

#endif
