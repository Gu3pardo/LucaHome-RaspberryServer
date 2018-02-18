#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#include "../../crosscutting/Constants.h"
#include "../../crosscutting/utils/Tools.h"
#include "../../dataaccess/controller.h"

using namespace std;

#ifndef SECURITY_SERVICE_H
#define SECURITY_SERVICE_H

class SecurityService
{
private:
	std::vector<std::string> _motionEventList;
	std::vector<std::string> _sentMotionEventList;

	bool _flagMotionStart;
	bool _flagMotionStop;
	bool _isMotionActive;

	string _motionUrl;

	MailController _mailController;
	PathController _pathController;

	string startMotion();
	string stopMotion();

	string getJsonString();
	string getMotionEventsJsonString();

public:
	SecurityService();
	~SecurityService();

	void Initialize(string);
	string PerformAction(vector<string>);
	void Dispose();

	void CheckMotionEvents();

	bool GetFlagMotionStart();
	bool GetFlagMotionStop();

	void StartMotion();
	void StopMotion();
};

#endif
