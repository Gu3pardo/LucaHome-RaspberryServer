#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef LISTEDMENU_DTO_H
#define LISTEDMENU_DTO_H

class ListedMenuDto
{
  private:
	int _id;
	std::string _title;
	std::string _description;
	int _useCounter;
	int _rating;

  public:
	ListedMenuDto();
	ListedMenuDto(int, std::string, std::string, int, int);
	~ListedMenuDto();

	void SetId(int);
	int GetId();

	void SetTitle(std::string);
	std::string GetTitle();

	void SetDescription(std::string);
	std::string GetDescription();

	void SetUseCount(int);
	int GetUseCount();

	void SetRating(int);
	int GetRating();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
