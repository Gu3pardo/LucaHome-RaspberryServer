#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../common/tools.h"

#ifndef MENU_H
#define MENU_H

class Menu {

private:
	std::string _weekday;
	int _day;
	int _month;
	int _year;
	std::string _title;
	std::string _description;

public:
	Menu();
	Menu(std::string, int, int, int, std::string, std::string);
	~Menu();

	void setWeekday(std::string);
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	void setTitle(std::string);
	void setDescription(std::string);

	std::string getWeekday();
	int getDay();
	int getMonth();
	int getYear();
	std::string getTitle();
	std::string getDescription();

	std::string toString();
};

#endif
