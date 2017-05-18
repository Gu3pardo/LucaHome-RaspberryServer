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

#include "../common/picontrol.h"
#include "../mail/mailservice.h"
#include "../controller/filecontroller.h"
#include "../xml/xmlservice.h"

#ifndef TEMPERATURESERVICE_H
#define TEMPERATURESERVICE_H

class TemperatureService {
private:
	std::string _settingsFile;

	std::string _sensorPath;
	std::string _temperatureArea;
	std::string _graphPath;

	MailService _mailService;

	FileController _fileController;
	XmlService _xmlService;

	int _warningCount;
	bool _isInitialized;

	int MIN_TEMP;
	int MAX_TEMP;

	int LED_NORMAL_TEMP;
	int LED_ERROR_LOW_TEMP;
	int LED_ERROR_HIGH_TEMP;

	bool _temperatureControlActive;

	void saveSettings();
	void loadSettings();

	double loadTemperature();

	void sendWarningMail(std::string);
	void enableLED(int);

	double getValue();
	std::string getString();
	std::string getRestString();

public:
	TemperatureService();
	~TemperatureService();

	void Initialize(FileController, MailService, std::string, std::string,
			std::string);
	void ControlTemperature();

	bool GetTemperatureControlActive();

	std::string PerformAction(std::string, std::vector<std::string>);
};

#endif
