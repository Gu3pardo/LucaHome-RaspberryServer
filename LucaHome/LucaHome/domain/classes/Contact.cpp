#include "Contact.h"

Contact::Contact()
{
	Contact("", "", "", "", "", "", "", 1, 1, 1900, false, false);
}

Contact::Contact(
	string uuid, string name, string group,
	string address, string phoneHome, string phoneMobile, string email,
	int birthdayDay, int birthdayMonth, int birthdayYear,
	bool birthdayRemindMe, bool birthdaySentReminderMail)
{
	_uuid = uuid;
	_name = name;
	_group = group;
	_address = address;
	_phoneHome = phoneHome;
	_phoneMobile = phoneMobile;
	_email = email;
	_birthdayDay = birthdayDay;
	_birthdayMonth = birthdayMonth;
	_birthdayYear = birthdayYear;
	_birthdayRemindMe = birthdayRemindMe;
	_birthdaySentReminderMail = birthdaySentReminderMail;
}

Contact::~Contact()
{
}

void Contact::SetUuid(string uuid)
{
	_uuid = uuid;
}

string Contact::GetUuid()
{
	return _uuid;
}

void Contact::SetName(string name)
{
	_name = name;
}

string Contact::GetName()
{
	return _name;
}

void Contact::SetGroup(string group)
{
	_group = group;
}

string Contact::GetGroup()
{
	return _group;
}

void Contact::SetAddress(string address)
{
	_address = address;
}

string Contact::GetAddress()
{
	return _address;
}

void Contact::SetPhoneHome(string phoneHome)
{
	_phoneHome = phoneHome;
}

string Contact::GetPhoneHome()
{
	return _phoneHome;
}

void Contact::SetPhoneMobile(string phoneMobile)
{
	_phoneMobile = phoneMobile;
}

string Contact::GetPhoneMobile()
{
	return _phoneMobile;
}

void Contact::SetEMail(string email)
{
	_email = email;
}

string Contact::GetEMail()
{
	return _email;
}

void Contact::SetBirthdayDay(int birthdayDay)
{
	_birthdayDay = birthdayDay;
}

int Contact::GetBirthdayDay()
{
	return _birthdayDay;
}

void Contact::SetBirthdayMonth(int birthdayMonth)
{
	_birthdayMonth = birthdayMonth;
}

int Contact::GetBirthdayMonth()
{
	return _birthdayMonth;
}

void Contact::SetBirthdayYear(int birthdayYear)
{
	_birthdayYear = birthdayYear;
}

int Contact::GetBirthdayYear()
{
	return _birthdayYear;
}

int Contact::GetAge()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayYear = now->tm_year + 1900;
	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (_birthdayMonth < todayMonth)
	{
		return todayYear - _birthdayYear;
	}
	else if (_birthdayMonth == todayMonth)
	{
		if (_birthdayDay > todayDay)
		{
			return todayYear - _birthdayYear - 1;
		}
		else
		{
			return todayYear - _birthdayYear;
		}
	}
	else
	{
		return todayYear - _birthdayYear - 1;
	}
}

bool Contact::HasBirthday()
{
	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int todayMonth = now->tm_mon + 1;
	int todayDay = now->tm_mday;

	if (todayMonth == _birthdayMonth && todayDay == _birthdayDay)
	{
		return true;
	}

	return false;
}

void Contact::SetBirthdayRemindMe(bool birthdayRemindMe) {
	_birthdayRemindMe = birthdayRemindMe;
}

bool Contact::GetBirthdayRemindMe() {
	return _birthdayRemindMe;
}

void Contact::SetBirthdaySentReminderMail(bool birthdaySentReminderMail) {
	_birthdaySentReminderMail = birthdaySentReminderMail;
}

bool Contact::GetBirthdaySentReminderMail() {
	return _birthdaySentReminderMail;
}

string Contact::JsonString()
{
	string str =
		string("{")
		+ string("\"Contact\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"Name\":\"") + _name + string("\",")
		+ string("\"Group\":\"") + _group + string("\",")
		+ string("\"Address\":\"") + _address + string("\",")
		+ string("\"PhoneHome\":\"") + _phoneHome + string("\",")
		+ string("\"PhoneMobile\":\"") + _phoneMobile + string("\",")
		+ string("\"EMail\":\"") + _email + string("\",")
		+ string("\"Birthday\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_birthdayDay) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_birthdayMonth) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_birthdayYear) + string(",")
		+ string("\"RemindMe\":") + Tools::ConvertBoolToStr(_birthdayRemindMe) + string(",")
		+ string("\"SentMail\":") + Tools::ConvertBoolToStr(_birthdaySentReminderMail)
		+ string("}")
		+ string("}")
		+ string("}");
	return str;
}

string Contact::ToString()
{
	string str = string("Contact { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; group: ") + _group
		+ string("; address: ") + _address
		+ string("; phonehome: ") + _phoneHome
		+ string("; phonemobile: ") + _phoneMobile
		+ string("; email: ") + _email
		+ string("; birthdayday: ") + Tools::ConvertIntToStr(_birthdayDay)
		+ string("; birthdaymonth: ") + Tools::ConvertIntToStr(_birthdayMonth)
		+ string("; birthdayyear: ") + Tools::ConvertIntToStr(_birthdayYear)
		+ string("; birthdayremindme: ") + Tools::ConvertBoolToStr(_birthdayRemindMe)
		+ string("; birthdaysentremindermail: ") + Tools::ConvertBoolToStr(_birthdaySentReminderMail)
		+ string(" }");
	return str;
}
