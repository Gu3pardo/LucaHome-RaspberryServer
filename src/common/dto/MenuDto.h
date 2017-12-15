#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef MENU_DTO_H
#define MENU_DTO_H

class MenuDto
{
  private:
	std::string _weekday;
	int _day;
	int _month;
	int _year;
	std::string _title;
	std::string _description;

  public:
	MenuDto();
	MenuDto(std::string, int, int, int, std::string, std::string);
	~MenuDto();

	void SetWeekday(std::string);
	std::string GetWeekday();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetTitle(std::string);
	std::string GetTitle();

	void SetDescription(std::string);
	std::string GetDescription();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
