#include "UserDto.h"

UserDto::UserDto()
{
	_name = "DUMMY";
	_password = "NO_PASSWORD";
	_role = -1;
	_isAdmin = -1;
	_invalidLoginCount = -1;
}

UserDto::UserDto(std::string name, std::string password, int role, int isAdmin, int invalidLoginCount)
{
	_name = name;
	_password = password;
	_role = role;
	_isAdmin = isAdmin;
	_invalidLoginCount = invalidLoginCount;
}

UserDto::~UserDto()
{
}

void UserDto::SetName(std::string name)
{
	_name = name;
}

std::string UserDto::GetName()
{
	return _name;
}

void UserDto::SetPassword(std::string password)
{
	_password = password;
}

std::string UserDto::GetPassword()
{
	return _password;
}

void UserDto::SetRole(int role)
{
	_role = role;
}

int UserDto::GetRole()
{
	return _role;
}

void UserDto::SetIsAdmin(int isAdmin)
{
	_isAdmin = isAdmin;
}

int UserDto::IsAdmin()
{
	return _isAdmin;
}

void UserDto::SetInvalidLoginCount(int invalidLoginCount)
{
	_invalidLoginCount = invalidLoginCount;
}

void UserDto::IncreaseInvalidLoginCount()
{
	_invalidLoginCount++;
}

int UserDto::GetInvalidLoginCount()
{
	return _invalidLoginCount;
}

std::string UserDto::ToString()
{
	std::string str = 
		std::string("User { name: ") + _name 
		+ std::string("; password: NO :P") 
		+ std::string("; role: ") + Tools::ConvertIntToStr(_role)
		+ std::string("; invalidLoginCount: ") + Tools::ConvertIntToStr(_invalidLoginCount)
		+ std::string(" }");
	return str;
}
