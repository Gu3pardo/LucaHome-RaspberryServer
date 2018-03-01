#include "PathController.h"

vector<string> PathController::ScanCameraFolder()
{
	vector<string> allFiles = scanDirForType(NAS_PATH_CAMERA, IS_FILE);

	vector<string> filter;
	filter.push_back(JPG_ENDING);
	filter.push_back(SWF_ENDING);

	return filterList(allFiles, filter);
}

vector<string> PathController::ScanMovieFolder()
{
	return scanDirForType(NAS_PATH_MOVIE, IS_FOLDER);
}

vector<string> PathController::ScanSeriesFolder()
{
	return scanDirForType(NAS_PATH_SERIES, IS_FOLDER);
}

vector<string> PathController::ScanMeterLogImageFolder()
{
	vector<string> allFiles = scanDirForType(NAS_PATH_METER_LOG, IS_FILE);

	vector<string> filter;
	filter.push_back(JPG_ENDING);

	return filterList(allFiles, filter);
}

// Private

vector<string> PathController::scanDirForType(string directory, int type)
{
	DIR *dir;
	struct dirent *dirEntry;
	vector<string> entries;

	const char *pathChar = directory.c_str();

	if ((dir = opendir(pathChar)) != NULL)
	{
		while ((dirEntry = readdir(dir)) != NULL)
		{
			if (dirEntry->d_type == type)
			{
				string dirName = dirEntry->d_name;
				entries.push_back(dirName);
			}
		}

		closedir(dir);
	}

	return entries;
}

vector<string> PathController::filterList(vector<string> listToFilter, vector<string> filterToTest)
{
	vector<string> relevantFiles;

	for (int index = 0; index < listToFilter.size(); index++)
	{
		string entry = listToFilter[index];

		for (int filterIndex = 0; filterIndex < filterToTest.size(); filterIndex++)
		{
			string currentFilter = filterToTest[filterIndex];

			if (Tools::HasEnding(entry, currentFilter))
			{
				relevantFiles.push_back(entry);
				break;
			}
		}
	}

	return relevantFiles;
}
