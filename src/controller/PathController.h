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
#include <dirent.h>

#include "../common/utils/Tools.h"
#include "../common/Constants.h"

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
