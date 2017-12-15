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

  public:
	ShoppingEntryDto();
	ShoppingEntryDto(int, std::string, std::string, int);
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

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
