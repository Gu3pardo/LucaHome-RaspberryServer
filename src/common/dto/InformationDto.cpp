#include "InformationDto.h"

InformationDto::InformationDto()
{
}

InformationDto::InformationDto(
	std::string author,
	std::string company,
	std::string contact,
	std::string buildDate,
	std::string serverVersion,
	std::string websiteVersion,
	std::string temperatureLoggerVersion,
	std::string androidApplicationVersion,
	std::string androidWearableVersion,
	std::string androidAccessApplicationVersion,
	std::string mediaServerVersion,
	std::string wpfApplicationVersion)
{
	_author = author;
	_company = company;
	_contact = contact;
	_buildDate = buildDate;
	_serverVersion = serverVersion;
	_websiteVersion = websiteVersion;
	_temperatureLoggerVersion = temperatureLoggerVersion;
	_androidApplicationVersion = androidApplicationVersion;
	_androidWearableVersion = androidWearableVersion;
	_androidAccessApplicationVersion = androidAccessApplicationVersion;
	_mediaServerVersion = mediaServerVersion;
	_wpfApplicationVersion = wpfApplicationVersion;
}

InformationDto::~InformationDto()
{
}

std::string InformationDto::GetAuthor()
{
	return _author;
}

std::string InformationDto::GetCompany()
{
	return _company;
}

std::string InformationDto::GetContact()
{
	return _contact;
}

std::string InformationDto::GetBuildDate()
{
	return _buildDate;
}

std::string InformationDto::GetServerVersion()
{
	return _serverVersion;
}

std::string InformationDto::GetWebsiteVersion()
{
	return _websiteVersion;
}

std::string InformationDto::GetTemperatureLoggerVersion()
{
	return _temperatureLoggerVersion;
}

std::string InformationDto::GetAndroidApplicationVersion()
{
	return _androidApplicationVersion;
}

std::string InformationDto::GetAndroidWearableVersion()
{
	return _androidWearableVersion;
}

std::string InformationDto::GetAndroidAccessApplicationVersion()
{
	return _androidAccessApplicationVersion;
}

std::string InformationDto::GetMediaServerVersion()
{
	return _mediaServerVersion;
}

std::string InformationDto::GetWpfApplicationVersion()
{
	return _wpfApplicationVersion;
}

std::string InformationDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Information\":")
		+ std::string("{")
		+ std::string("\"Author\":") + _author + std::string(",")
		+ std::string("\"Company\":") + _company + std::string(",")
		+ std::string("\"Contact\":") + _contact + std::string(",")
		+ std::string("\"BuildDate\":") + _buildDate + std::string(",")
		+ std::string("\"ServerVersion\":") + _serverVersion + std::string(",")
		+ std::string("\"WebsiteVersion\":") + _websiteVersion + std::string(",")
		+ std::string("\"TemperatureLoggerVersion\":") + _temperatureLoggerVersion + std::string(",")
		+ std::string("\"AndroidApplicationVersion\":") + _androidApplicationVersion + std::string(",")
		+ std::string("\"AndroidWearableVersion\":") + _androidWearableVersion + std::string(",")
		+ std::string("\"AndroidAccessApplicationVersion\":") + _androidAccessApplicationVersion + std::string(",")
		+ std::string("\"MediaServerVersion\":") + _mediaServerVersion + std::string(",")
		+ std::string("\"WpfApplicationVersion\":") + _wpfApplicationVersion
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string InformationDto::ToString()
{
	std::string str =
		std::string("InformationDto { Author: ") + _author
		+ std::string("; Company: ") + _company
		+ std::string("; Contact: ") + _contact
		+ std::string("; BuildDate: ") + _buildDate
		+ std::string("; ServerVersion: ") + _serverVersion
		+ std::string("; WebsiteVersion: ") + _websiteVersion
		+ std::string("; TemperatureLoggerVersion: ") + _temperatureLoggerVersion
		+ std::string("; AndroidApplicationVersion: ") + _androidApplicationVersion
		+ std::string("; AndroidWearableVersion: ") + _androidWearableVersion
		+ std::string("; AndroidAccessApplicationVersion: ") + _androidAccessApplicationVersion
		+ std::string("; MediaServerVersion: ") + _mediaServerVersion
		+ std::string("; WpfApplicationVersion: ") + _wpfApplicationVersion
		+ std::string(" }");
	return str;
}
