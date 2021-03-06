#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef CHANGE_DTO_H
#define CHANGE_DTO_H

class ChangeDto
{
  private:
	std::string _type;
	int _hour;
	int _minute;
	int _day;
	int _month;
	int _year;
	std::string _userName;

  public:
	ChangeDto();
	ChangeDto(std::string, int, int, int, int, int, std::string);
	~ChangeDto();

	void SetType(std::string);
	std::string GetType();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetUserName(std::string);
	std::string GetUserName();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
