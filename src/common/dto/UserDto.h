#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef USER_DTO_H
#define USER_DTO_H

class UserDto
{
  private:
	std::string _name;
	std::string _password;
	int _role;
	bool _isAdmin;
	int _invalidLoginCount;

  public:
	UserDto();
	UserDto(std::string, std::string, int, bool, int);
	~UserDto();

	std::string GetName();
	std::string GetPassword();
	int GetRole();
	bool IsAdmin();

	void SetInvalidLoginCount(int);
	void IncreaseInvalidLoginCount();
	int GetInvalidLoginCount();

	std::string ToString();
};

#endif
