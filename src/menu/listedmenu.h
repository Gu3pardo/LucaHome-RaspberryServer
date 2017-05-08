#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../common/tools.h"

#ifndef LISTEDMENU_H
#define LISTEDMENU_H

class ListedMenu {

private:
	int _id;
	std::string _description;
	int _rating;
	int _lastSuggestion;

public:
	ListedMenu();
	ListedMenu(int, std::string, int, int);
	~ListedMenu();

	void setId(int);
	void setDescription(std::string);
	void setRating(int);
	void setLastSuggestion(int);

	int getId();
	std::string getDescription();
	int getRating();
	int isLastSuggestion();

	std::string toString();
};

#endif
