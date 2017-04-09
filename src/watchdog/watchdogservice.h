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

#include "../common/tools.h"

#ifndef WATCHDOGSERVICE_H
#define WATCHDOGSERVICE_H

class WatchdogService {
private:
	int _count;

public:
	WatchdogService();
	~WatchdogService();

	std::string PerformAction(std::string, std::vector<std::string>);
};

#endif
