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
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>

#include "../../crosscutting/utils/Tools.h"
#include "../../crosscutting/Constants.h"

using namespace std;

#ifndef PATH_CONTROLLER_H
#define PATH_CONTROLLER_H

class PathController
{
private:
	static vector<string> scanDirForType(string, int);
	static vector<string> filterList(vector<string>, vector<string>);
public:
	static vector<string> ScanCameraFolder();
	static vector<string> ScanMovieFolder();
	static vector<string> ScanSeriesFolder();
	static vector<string> ScanMeterLogImageFolder();
};

#endif
