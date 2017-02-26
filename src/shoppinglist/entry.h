#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../common/tools.h"

#ifndef ENTRY_H
#define ENTRY_H

class Entry {

private:
	int id;
	std::string name;
	std::string group;
	int quantity;

public:
	Entry();
	Entry(int, std::string, std::string, int);
	~Entry();

	void setId(int);
	void setName(std::string);
	void setGroup(std::string);
	void setQuantity(int);

	int getId();
	std::string getName();
	std::string getGroup();
	int getQuantity();

	std::string toString();
};

#endif
