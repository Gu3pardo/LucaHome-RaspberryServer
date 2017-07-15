#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#ifndef LOG_DTO_H
#define LOG_DTO_H

class LogDto
{
  private:
	std::string _level;
	std::string _content;
	std::string _logTime;
	std::string _user;

  public:
	LogDto(std::string, std::string, std::string, std::string);
	~LogDto();

	std::string GetLevel();
	std::string GetContent();
	std::string GetLogTime();
	std::string GetUser();

	std::string ToFileString();
	std::string ToString();
};

#endif
