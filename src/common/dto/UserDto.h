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
	int _isAdmin;
	int _invalidLoginCount;

  public:
	UserDto();
	UserDto(std::string, std::string, int, int, int);
	~UserDto();

	void SetName(std::string);
	std::string GetName();

	void SetPassword(std::string);
	std::string GetPassword();

	void SetRole(int);
	int GetRole();

	void SetIsAdmin(int);
	int IsAdmin();

	void SetInvalidLoginCount(int);
	void IncreaseInvalidLoginCount();
	int GetInvalidLoginCount();

	std::string ToString();
};

#endif
