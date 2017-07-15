#include "LogDto.h"

LogDto::LogDto(std::string level, std::string content, std::string logTime, std::string user)
{
	_level = level;
	_content = content;
	_logTime = logTime;
	_user = user;
}

LogDto::~LogDto()
{
}

std::string LogDto::GetLevel()
{
	return _level;
}

std::string LogDto::GetContent()
{
	return _content;
}

std::string LogDto::GetLogTime()
{
	return _logTime;
}

std::string LogDto::GetUser()
{
	return _user;
}

std::string LogDto::ToFileString()
{
	std::string str =
		_level + std::string(":") + _content + std::string(":") + _logTime + std::string(":") + _user + std::string(";");
	return str;
}

std::string LogDto::ToString()
{
	std::string str =
		std::string("LogDto { level: ") + _level 
		+ std::string("; content: ") + _content 
		+ std::string("; logTime: ") + _logTime 
		+ std::string("; user: ") + _user 
		+ std::string(" }");
	return str;
}
