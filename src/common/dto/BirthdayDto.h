#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef BIRTHDAY_DTO_H
#define BIRTHDAY_DTO_H

class BirthdayDto
{
private:
	int _id;
	std::string _name;
	int _day;
	int _month;
	int _year;
	bool _sendMail;

public:
	BirthdayDto();
	BirthdayDto(int, std::string, int, int, int);
	~BirthdayDto();

	void SetId(int);
	int GetId();

	void SetName(std::string);
	std::string GetName();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	int GetAge();
	bool HasBirthday();

	void SetSendMail(bool);
	bool GetSendMail();

	std::string ToString();
};

#endif
