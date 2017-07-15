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
	std::string _description;
	int _rating;
	int _lastSuggestion;

  public:
	ListedMenuDto();
	ListedMenuDto(int, std::string, int, int);
	~ListedMenuDto();

	void SetId(int);
	int GetId();

	void SetDescription(std::string);
	std::string GetDescription();

	void SetRating(int);
	int GetRating();

	void SetLastSuggestion(int);
	int IsLastSuggestion();

	std::string ToString();
};

#endif
