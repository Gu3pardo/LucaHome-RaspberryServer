#include "PathController.h"

PathController::PathController()
{
}

PathController::~PathController()
{
}

std::vector<std::string> PathController::ScanCameraFolder()
{
	DIR *dir;
	struct dirent *dirEntry;
	std::vector<std::string> imageEntries;

	const char *motionPathChar = NAS_PATH_CAMERA;

	if ((dir = opendir(motionPathChar)) != NULL)
	{
		while ((dirEntry = readdir(dir)) != NULL)
		{
			std::string fileName = dirEntry->d_name;

			if (fileName[0] == '.')
			{
				continue;
			}

			if (Tools::HasEnding(fileName, JPG_ENDING)
				|| Tools::HasEnding(fileName, SWF_ENDING))
			{
				imageEntries.push_back(fileName);
			}
		}

		closedir(dir);
	}

	return imageEntries;
}

std::vector<std::string> PathController::ScanLibraryFolder()
{
	return scanForSubDir(NAS_PAH_LIBRARY);
}

std::vector<std::string> PathController::ScanMovieFolder()
{
	return scanForSubDir(NAS_PAH_MOVIE);
}

std::vector<std::string> PathController::ScanSeriesFolder()
{
	return scanForSubDir(NAS_PATH_SERIES);
}

// Private

std::vector<std::string> PathController::scanForSubDir(std::string directory)
{
	DIR *dir;
	struct dirent *dirEntry;
	std::vector<std::string> entries;

	const char *pathChar = directory.c_str();

	if ((dir = opendir(pathChar)) != NULL)
	{
		while ((dirEntry = readdir(dir)) != NULL)
		{
			if (dirEntry->d_type == IS_FOLDER)
			{
				std::string dirName = dirEntry->d_name;
				entries.push_back(dirName);
			}
		}

		closedir(dir);
	}

	return entries;
}
