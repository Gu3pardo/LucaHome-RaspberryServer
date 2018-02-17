#include "User.h"

User::User()
{
	_uuid = "";
	_name = "";
	_passphrase = "";
	_role = 0;
	_isAdmin = false;
	_invalidLoginCount = 0;
}

User::User(string uuid, string name, string passphrase, int role, bool isAdmin, int invalidLoginCount)
{
	_uuid = uuid;
	_name = name;
	_passphrase = passphrase;
	_role = role;
	_isAdmin = isAdmin;
	_invalidLoginCount = invalidLoginCount;
}

User::~User()
{
}

string User::GetUuid()
{
	return _uuid;
}

string User::GetName()
{
	return _name;
}

string User::GetPassphrase()
{
	return _passphrase;
}

int User::GetRole()
{
	return _role;
}

bool User::IsAdmin()
{
	return _isAdmin;
}

void User::SetInvalidLoginCount(int invalidLoginCount)
{
	_invalidLoginCount = invalidLoginCount;
}

void User::IncreaseInvalidLoginCount()
{
	_invalidLoginCount++;
}

int User::GetInvalidLoginCount()
{
	return _invalidLoginCount;
}

string User::ToString()
{
	string str =
		string("User { uuid: ") + _uuid
		+ string("; name: ") + _name
		+ string("; passphrase: ") + string("no ... :P")
		+ string("; role: ") + Tools::ConvertIntToStr(_role)
		+ string("; isAdmin: ") + Tools::ConvertBoolToStr(_isAdmin)
		+ string("; invalidLoginCount: ") + Tools::ConvertIntToStr(_invalidLoginCount)
		+ string(" }");
	return str;
}
