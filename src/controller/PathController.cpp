#include "PathController.h"

PathController::PathController()
{
}

PathController::~PathController()
{
}

std::vector<std::string> PathController::ScanCameraFolder()
{
	std::vector<std::string> allFiles = scanDirForType(NAS_PATH_CAMERA, IS_FILE);

	std::vector<std::string> filter;
	filter.push_back(JPG_ENDING);
	filter.push_back(SWF_ENDING);

	return filterList(allFiles, filter);
}

std::vector<std::string> PathController::ScanMovieFolder()
{
	return scanDirForType(NAS_PATH_MOVIE, IS_FOLDER);
}

std::vector<std::string> PathController::ScanSeriesFolder()
{
	return scanDirForType(NAS_PATH_SERIES, IS_FOLDER);
}

std::vector<std::string> PathController::ScanMeterLogImageFolder()
{
	std::vector<std::string> allFiles = scanDirForType(NAS_PATH_METER_LOG, IS_FILE);

	std::vector<std::string> filter;
	filter.push_back(JPG_ENDING);

	return filterList(allFiles, filter);
}

// Private

std::vector<std::string> PathController::scanDirForType(std::string directory, int type)
{
	DIR *dir;
	struct dirent *dirEntry;
	std::vector<std::string> entries;

	const char *pathChar = directory.c_str();

	if ((dir = opendir(pathChar)) != NULL)
	{
		while ((dirEntry = readdir(dir)) != NULL)
		{
			if (dirEntry->d_type == type)
			{
				std::string dirName = dirEntry->d_name;
				entries.push_back(dirName);
			}
		}

		closedir(dir);
	}

	return entries;
}

std::vector<std::string> PathController::filterList(std::vector<std::string> listToFilter, std::vector<std::string> filterToTest)
{
	std::vector<std::string> relevantFiles;

	for (int index = 0; index < listToFilter.size(); index++)
	{
		std::string entry = listToFilter[index];

		for (int filterIndex = 0; filterIndex < filterToTest.size(); filterIndex++)
		{
			std::string currentFilter = filterToTest[filterIndex];

			if (Tools::HasEnding(entry, currentFilter))
			{
				relevantFiles.push_back(entry);
				break;
			}
		}
	}

	return relevantFiles;
}
