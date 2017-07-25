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

	loadInformations();
}

std::string InformationService::PerformAction(std::string action, std::vector<std::string> data)
{
	if (action == GET)
	{
		if (data.size() == INFORMATION_DATA_SIZE)
		{
			if (data[4] == REST)
			{
				return getRestString();
			}
			else if (data[4] == REDUCED)
			{
				return getReducedString();
			}
			else
			{
				return "Error 112:Wrong action parameter for information";
			}
		}
		else
		{
			return "Error 111:Wrong data size for information";
		}
	}
	else
	{
		return "Error 110:Action not found for information";
	}
}

void InformationService::ReloadData()
{
	loadInformations();
}

/*==============PRIVATE==============*/

void InformationService::loadInformations()
{
	std::string informationFileContent = _fileController.ReadFile(_informationFile);
	_informationList = _xmlService.GetInformation(informationFileContent);
}

std::string InformationService::getRestString()
{
	std::stringstream out;

	out << "{information:"
		<< "{Author:" << _informationList.GetAuthor() << "};"
		<< "{Company:" << _informationList.GetCompany() << "};"
		<< "{Contact:" << _informationList.GetContact() << "};"
		<< "{Build Date:" << _informationList.GetBuildDate() << "};"
		<< "{Server Version:" << _informationList.GetServerVersion() << "};"
		<< "{Website Version:" << _informationList.GetWebsiteVersion() << "};"
		<< "{Temperature Logger Version:" << _informationList.GetTemperatureLoggerVersion() << "};"
		<< "{Android Application Version:" << _informationList.GetAndroidApplicationVersion() << "};"
		<< "{Android Wear Version:" << _informationList.GetAndroidWearableVersion() << "};"
		<< "{Android Access Application Version:" << _informationList.GetAndroidAccessApplicationVersion() << "};"
		<< "{Media Server Version:" << _informationList.GetMediaServerVersion() << "};"
		<< "{WPF Application Version:" << _informationList.GetWpfApplicationVersion() << "};"
		<< "};";

	out << "\x00" << std::endl;

	return out.str();
}

std::string InformationService::getReducedString()
{
	std::stringstream out;

	out << "information::" << "Author::" << _informationList.GetAuthor() << ";"
		<< "information::" << "Company::" << _informationList.GetCompany() << ";"
		<< "information::" << "Contact::" << _informationList.GetContact() << ";"
		<< "information::" << "Build Date::" << _informationList.GetBuildDate() << ";"
		<< "information::" << "Server Version::" << _informationList.GetServerVersion() << ";"
		<< "information::" << "Website Version::" << _informationList.GetWebsiteVersion() << ";"
		<< "information::" << "Temperature Logger Version::" << _informationList.GetTemperatureLoggerVersion() << ";"
		<< "information::" << "WPF Application Version::" << _informationList.GetWpfApplicationVersion() << ";"
		<< "information::" << "Android Application Version::" << _informationList.GetAndroidApplicationVersion() << ";"
		<< "information::" << "Android Wear Version::" << _informationList.GetAndroidWearableVersion() << ";"
		<< "information::" << "Android Access Application Version::" << _informationList.GetAndroidAccessApplicationVersion() << ";"
		<< "information::" << "Media Server Version::" << _informationList.GetMediaServerVersion() << ";";

	out << "\x00" << std::endl;

	return out.str();
}
