#include "ApplicationInformation.h"

ApplicationInformation::ApplicationInformation()
{
}

ApplicationInformation::ApplicationInformation(string key, string value)
{
	_key = key;
	_value = value;
}

ApplicationInformation::~ApplicationInformation()
{
}

string ApplicationInformation::GetKey()
{
	return _key;
}

void ApplicationInformation::SetValue(string value)
{
	_value = value;
}

string ApplicationInformation::GetValue()
{
	return _value;
}

string ApplicationInformation::JsonString()
{
	string str =
		string("{")
		+ string("\"ApplicationInformation\":")
		+ string("{")
		+ string("\"Key\":\"") + _key + string("\",")
		+ string("\"Value\":\"") + _value + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string ApplicationInformation::ToString()
{
	string str =
		string("ApplicationInformation { key: ") + _key
		+ string("; value: ") + _value
		+ string(" }");
	return str;
}
