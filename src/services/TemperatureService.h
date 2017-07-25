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

#include "../common/utils/PiControl.h"
#include "../controller/FileController.h"
#include "../controller/MailController.h"
#include "xml/XmlService.h"

#define GET "GET"
#define REDUCED "REDUCED"
#define REST "REST"
#define SETCONTROLTASK "SETCONTROLTASK"
#define ON "ON"
#define OFF "OFF"
#define MENU_DATA_SIZE 11

#ifndef TEMPERATURESERVICE_H
#define TEMPERATURESERVICE_H

class TemperatureService
{
  private:
	std::string _settingsFile;

	std::string _sensorPath;
	std::string _temperatureArea;
	std::string _graphPath;

	MailController _mailController;

	FileController _fileController;
	XmlService _xmlService;

	int _warningCount;
	bool _isInitialized;

	int _minTemp;
	int _maxTemp;

	int _ledNormalTemp;
	int _ledErrorLowTemp;
	int _ledErrorHighTemp;

	bool _temperatureControlActive;

	void loadSettings();
	void saveSettings();

	double loadTemperature();

	void sendWarningMail(std::string);
	void enableLED(int);

	double getValue();
	std::string getRestString();
	std::string getReducedString();

  public:
	TemperatureService();
	~TemperatureService();

	void Initialize(FileController, MailController, std::string, std::string, std::string, std::string);
	void ControlTemperature();
	bool GetTemperatureControlActive();
	std::string PerformAction(std::string, std::vector<std::string>);
	void ReloadData();
};

#endif
