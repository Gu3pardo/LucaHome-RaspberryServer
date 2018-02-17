#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef COIN_H
#define COIN_H

class Coin
{
private:
	string _uuid;
	string _user;
	string _type;
	double _amount;

public:
	Coin();
	Coin(string, string, string, double);
	~Coin();

	void SetUuid(string);
	string GetUuid();

	void SetUser(string);
	string GetUser();

	void SetType(string);
	string GetType();

	void SetAmount(double);
	double GetAmount();

	string JsonString();
	string ToString();
};

#endif
