#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef INFORMATION_DTO_H
#define INFORMATION_DTO_H

class InformationDto
{
private:
	std::string _author;
	std::string _company;
	std::string _contact;
	std::string _buildDate;
	std::string _serverVersion;
	std::string _websiteVersion;
	std::string _temperatureLoggerVersion;
	std::string _androidApplicationVersion;
	std::string _androidWearableVersion;
	std::string _androidAccessApplicationVersion;
	std::string _mediaServerVersion;
	std::string _wpfApplicationVersion;

public:
	InformationDto();
	InformationDto(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);
	~InformationDto();

	std::string GetAuthor();
	std::string GetCompany();
	std::string GetContact();
	std::string GetBuildDate();
	std::string GetServerVersion();
	std::string GetWebsiteVersion();
	std::string GetTemperatureLoggerVersion();
	std::string GetAndroidApplicationVersion();
	std::string GetAndroidWearableVersion();
	std::string GetAndroidAccessApplicationVersion();
	std::string GetMediaServerVersion();
	std::string GetWpfApplicationVersion();

	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
