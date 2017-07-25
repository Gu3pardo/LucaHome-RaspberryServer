#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/dto/GpioDto.h"
#include "../common/dto/ScheduleDto.h"
#include "../common/dto/WirelessSocketDto.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#define GET "GET"
#define SET "SET"
#define ADD "ADD"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define GPIO "GPIO"
#define SCHEDULE "SCHEDULE"
#define SOCKET "SOCKET"
#define ALL "ALL"
#define SOUND "SOUND"
#define RASPBERRY "RASPBERRY"
#define AREA "AREA"
#define SENSOR "SENSOR"
#define URL "URL"
#define MAIN "MAIN"
#define CAMERA "CAMERA"
#define TEMPERATURE "TEMPERATURE"
#define REDUCED "REDUCED"

#ifndef REMOTESERVICE_H
#define REMOTESERVICE_H

class RemoteService {
private:
	std::string _settingsFile;

	int _port;
	int _datagpio;
	int _receivergpio;
	int _raspberry;

	std::string _alarmSound;
	std::string _wakeUpSound;

	std::string _area;
	std::vector<std::string> _areaList;

	std::string _sensor;
	std::vector<std::string> _sensorList;

	std::string _url;
	std::vector<std::string> _urlList;

	std::string _accessurl;

	std::vector<std::string> _mediaMirrorList;

	std::vector<GpioDto> _gpioList;
	std::vector<ScheduleDto> _scheduleList;
	std::vector<WirelessSocketDto> _socketList;

	FileController _fileController;
	XmlService _xmlService;

	void saveSettings(ChangeService, std::string);
	void loadSettings();

	int getDataGpio();

	std::vector<std::string> getAreaList();
	std::vector<std::string> getSensorList();

	std::vector<std::string> getUrlList();

	std::string getGpiosString();
	std::vector<GpioDto> getGpioList();
	std::string getGpiosRestString();
	std::string getGpiosReducedString();

	bool setGpio(std::string, int, ChangeService, std::string);
	bool addGpio(std::vector<std::string>, ChangeService, std::string);
	bool updateGpio(std::vector<std::string>, ChangeService, std::string);
	bool deleteGpio(std::string, ChangeService, std::string);
	bool setAllGpios(int, ChangeService, std::string);

	std::string getSchedulesString();
	std::string getSchedulesRestString();
	std::string getSchedulesReducedString();

	bool setSchedule(std::string, int, ChangeService, std::string);
	bool addSchedule(std::vector<std::string>, ChangeService, std::string);
	bool updateSchedule(std::vector<std::string>, ChangeService, std::string);
	bool deleteSchedule(std::string, ChangeService, std::string);
	bool setAllSchedules(int, ChangeService, std::string);

	std::string getSocketsString();
	std::vector<WirelessSocketDto> getSocketList();
	std::string getSocketsRestString();
	std::string getSocketsReducedString();

	bool setSocket(std::string, int, ChangeService, std::string);
	bool addSocket(std::vector<std::string>, ChangeService, std::string);
	bool updateSocket(std::vector<std::string>, ChangeService, std::string);
	bool deleteSocket(std::string, ChangeService, std::string);
	bool setAllSockets(int, ChangeService, std::string);
	bool setSoundSocket(int, ChangeService, std::string);

public:
	RemoteService();
	~RemoteService();

	void Initialize(FileController, std::string);

	std::string PerformAction(std::string, std::vector<std::string>, ChangeService, std::string);

	bool ActivateSockets(std::vector<std::string>, ChangeService, std::string);

	int GetRaspberry();
	int GetPort();
	int GetReceiverGpio();

	std::vector<ScheduleDto> GetScheduleList();

	std::string GetArea();
	std::string GetSensor();
	std::string GetUrl();
	std::string GetAccessUrl();
	std::string GetCameraUrl();
	std::vector<std::string> GetMediaMirrorList();
	std::string GetTemperatureGraphUrl();
	std::string GetAlarmSound();
	std::string GetWakeUpSound();

	void ReloadData();
};

#endif
