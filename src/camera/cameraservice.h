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

#include "../common/tools.h"
#include "../mail/mailservice.h"
#include "../system/systemservice.h"

#ifndef CAMERASERVICE_H
#define CAMERASERVICE_H

class CameraService {
private:
	std::string _motionPath;
	std::string _cameraUrl;
	std::vector<std::string> _motionEvents;
	std::vector<std::string> _alreadySentEvents;
	bool _isMotionRunning;

	bool _startCamera;
	bool _stopCamera;

	bool _motionControlActive;

	MailService _mailService;
	SystemService _systemService;

	std::string startCamera();
	std::string stopCamera();

	std::string getData();

	std::vector<std::string> scanFolder();
	std::string getMotionEventsRestString();

public:
	CameraService();
	~CameraService();

	void Initialize(std::string, std::string, MailService, SystemService);

	std::string PerformAction(std::string, std::vector<std::string>);

	void Check();

	bool GetMotionControlActive();
	bool GetStartCamera();
	bool GetStopCamera();
	bool IsMotionRunning();

	std::string StartMotion();
	std::string StopMotion();
};

#endif
