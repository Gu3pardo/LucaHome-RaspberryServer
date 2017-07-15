#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>

#include "../common/utils/Tools.h"

#define CAMERA_SAVE_PATH "/NAS/Camera/"
#define LIBRARY_PATH "/NAS/Library/"
#define MOVIE_PATH "/NAS/Movies/"
#define SERIES_PATH "/NAS/Series/"

#define IS_FOLDER 0x4
#define IS_FILE 0x8

#define JPG_ENDING ".jpg"
#define SWF_ENDING ".swf"

#ifndef PATHCONTROLLER_H
#define PATHCONTROLLER_H

class PathController
{
private:
	std::vector<std::string> scanForSubDir(std::string);
public:
	PathController();
	~PathController();

	std::vector<std::string> ScanCameraFolder();
	std::vector<std::string> ScanLibraryFolder();
	std::vector<std::string> ScanMovieFolder();
	std::vector<std::string> ScanSeriesFolder();
};

#endif
