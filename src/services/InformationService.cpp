#include "InformationService.h"

/*===============PUBLIC==============*/

InformationService::InformationService()
{
}

InformationService::~InformationService()
{
}

void InformationService::Initialize(FileController fileController, std::string informationFile)
{
	_fileController = fileController;
	_informationFile = informationFile;

	LoadData();
}

std::string InformationService::PerformAction(std::vector<std::string> data)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL) {
			return getJsonString();
		}
		else if (actionParameter == PHP) {
			return getPhpString();
		}
		return  INFORMATION_ERROR_NR_111;
	}

	return INFORMATION_ERROR_NR_110;
}

void InformationService::LoadData()
{
	std::string informationFileContent = _fileController.ReadFile(_informationFile);
	_informationList = _xmlService.GetInformation(informationFileContent);
}

/*==============PRIVATE==============*/

std::string InformationService::getJsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"Information\":")
		+ std::string("{")
		+ std::string("\"Author\":") + _informationList.GetAuthor() + std::string(",")
		+ std::string("\"Company\":") + _informationList.GetCompany() + std::string(",")
		+ std::string("\"Contact\":") + _informationList.GetContact() + std::string(",")
		+ std::string("\"Build Date\":") + _informationList.GetBuildDate() + std::string(",")
		+ std::string("\"Server Version\":") + _informationList.GetServerVersion() + std::string(",")
		+ std::string("\"Website Version\":") + _informationList.GetWebsiteVersion() + std::string(",")
		+ std::string("\"Temperature Logger Version\":") + _informationList.GetTemperatureLoggerVersion() + std::string(",")
		+ std::string("\"Android Application Version\":") + _informationList.GetAndroidApplicationVersion() + std::string(",")
		+ std::string("\"Android Wear Version\":") + _informationList.GetAndroidWearableVersion() + std::string(",")
		+ std::string("\"Android Access Application Version\":") + _informationList.GetAndroidAccessApplicationVersion() + std::string(",")
		+ std::string("\"Media Server Version\":") + _informationList.GetMediaServerVersion() + std::string(",")
		+ std::string("\"WPF Application Version\":") + _informationList.GetWpfApplicationVersion()
		+ std::string("}")
		+ std::string("}");

	std::stringstream out;
	out << str << "\x00" << std::endl;

	return out.str();
}

std::string InformationService::getPhpString()
{
	std::stringstream out;

	out << "information::" << "Author::" << _informationList.GetAuthor() << ";"
		<< "information::" << "Company::" << _informationList.GetCompany() << ";"
		<< "information::" << "Contact::" << _informationList.GetContact() << ";"
		<< "information::" << "Build Date::" << _informationList.GetBuildDate() << ";"
		<< "information::" << "Server Version::" << _informationList.GetServerVersion() << ";"
		<< "information::" << "Website Version::" << _informationList.GetWebsiteVersion() << ";"
		<< "information::" << "Temperature Logger Version::" << _informationList.GetTemperatureLoggerVersion() << ";"
		<< "information::" << "Android Application Version::" << _informationList.GetAndroidApplicationVersion() << ";"
		<< "information::" << "Android Wear Version::" << _informationList.GetAndroidWearableVersion() << ";"
		<< "information::" << "Android Access Application Version::" << _informationList.GetAndroidAccessApplicationVersion() << ";"
		<< "information::" << "Media Server Version::" << _informationList.GetMediaServerVersion() << ";"
		<< "information::" << "WPF Application Version::" << _informationList.GetWpfApplicationVersion() << ";";

	out << "\x00" << std::endl;

	return out.str();
}
