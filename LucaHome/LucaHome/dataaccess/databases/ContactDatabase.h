#include "ITemplateDatabase.h"
#include "../../domain/classes/Contact.h";

using namespace std;

#ifndef CONTACT_DATABASE_H
#define CONTACT_DATABASE_H

class ContactDatabase : public ITemplateDatabase<Contact>
{
protected:
	string _databaseName;
	string _tableName = "DatabaseContactListTable";
	string _keyRowId = "_rowId";
	string _keyUuid = "_uuid";
	string _keyName = "_name";
	string _keyGroup = "_group";
	string _keyAddress = "_address";
	string _keyPhoneHome = "_phoneHome";
	string _keyPhoneMobile = "_phoneMobile";
	string _keyEMail = "_email";
	string _keyBirthdayDay = "_birthdayDay";
	string _keyBirthdayMonth = "_birthdayMonth";
	string _keyBirthdayYear = "_birthdayYear";
	string _keyBirthdayRemindMe = "_birthdayRemindMe";
	string _keyBirthdaySentReminderMail = "_birthdaySentReminderMail";

	sqlite3 *database;

	virtual char create();
	virtual char open();
	virtual char close();

public:
	ContactDatabase();
	ContactDatabase(string);
	~ContactDatabase();

	virtual char Dispose();

	virtual vector<Contact> GetList();
	virtual Contact GetByUuid(string);

	virtual char Insert(int, Contact);
	virtual char Update(Contact);
	virtual char Delete(string);
};

#endif
