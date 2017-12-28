#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef SHOPPING_ENTRY_DTO_H
#define SHOPPING_ENTRY_DTO_H

class ShoppingEntryDto
{
private:
	int _id;
	std::string _name;
	std::string _group;
	int _quantity;
	std::string _unit;

public:
	ShoppingEntryDto();
	ShoppingEntryDto(int, std::string, std::string, int, std::string);
	~ShoppingEntryDto();

	void SetId(int);
	int GetId();

	void SetName(std::string);
	std::string GetName();

	void SetGroup(std::string);
	std::string GetGroup();

	void SetQuantity(int);
	void IncreaseQuantity(int);
	void DecreaseQuantity(int);
	int GetQuantity();

	void SetUnit(std::string);
	std::string GetUnit();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
