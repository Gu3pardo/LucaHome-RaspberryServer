#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include "../../crosscutting/utils/Tools.h"

using namespace std;

#ifndef APPLICATION_INFORMATION_H
#define APPLICATION_INFORMATION_H

class ApplicationInformation
{
private:
	string _key;
	string _value;

public:
	ApplicationInformation();
	ApplicationInformation(string, string);
	~ApplicationInformation();

	string GetKey();

	void SetValue(string);
	string GetValue();

	string JsonString();
	string ToString();
};

#endif
