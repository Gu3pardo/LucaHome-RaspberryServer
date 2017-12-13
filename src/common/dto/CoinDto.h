#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef COIN_DTO_H
#define COIN_DTO_H

class CoinDto
{
private:
	int _id;
	std::string _user;
	std::string _type;
	double _amount;

public:
	CoinDto();
	CoinDto(int, std::string, std::string, double);
	~CoinDto();

	void SetId(int);
	int GetId();

	void SetUser(std::string);
	std::string GetUser();

	void SetType(std::string);
	std::string GetType();

	void SetAmount(double);
	double GetAmount();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif
