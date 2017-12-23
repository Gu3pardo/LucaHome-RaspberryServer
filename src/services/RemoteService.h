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
#include "../common/dto/WirelessSwitchDto.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef REMOTESERVICE_H
#define REMOTESERVICE_H

class RemoteService {
private:
	std::string _settingsFile;

	int _port;
	int _datagpio;
	int _raspberry;

	std::string _area;
	std::vector<std::string> _areaList;

	std::string _sensor;
	std::vector<std::string> _sensorList;

	std::string _url;
	std::vector<std::string> _urlList;

	std::vector<std::string> _mediaMirrorList;

	std::vector<GpioDto> _gpioList;
	std::vector<ScheduleDto> _scheduleList;
	std::vector<WirelessSocketDto> _socketList;
	std::vector<WirelessSwitchDto> _switchList;

	FileController _fileController;
	XmlService _xmlService;

	void saveSettings(ChangeService, std::string);

	int getDataGpio();

	std::vector<std::string> getAreaList();
	std::vector<std::string> getSensorList();

	std::vector<std::string> getUrlList();

	std::vector<GpioDto> getGpioList();
	std::string getJsonStringGpios();

	bool setGpio(std::string, int, ChangeService, std::string);
	bool addGpio(std::vector<std::string>, ChangeService, std::string);
	bool updateGpio(std::vector<std::string>, ChangeService, std::string);
	bool deleteGpio(std::string, ChangeService, std::string);
	bool setAllGpios(int, ChangeService, std::string);

	std::string getJsonStringSchedules();

	bool setSchedule(std::string, int, ChangeService, std::string);
	bool addSchedule(std::vector<std::string>, ChangeService, std::string);
	bool updateSchedule(std::vector<std::string>, ChangeService, std::string);
	bool deleteSchedule(std::string, ChangeService, std::string);
	bool setAllSchedules(int, ChangeService, std::string);

	std::vector<WirelessSocketDto> getSocketList();
	std::string getJsonStringSockets();

	bool setSocket(std::string, int, ChangeService, std::string);
	bool addSocket(std::vector<std::string>, ChangeService, std::string);
	bool updateSocket(std::vector<std::string>, ChangeService, std::string);
	bool deleteSocket(int, ChangeService, std::string);
	bool setAllSockets(int, ChangeService, std::string);

	std::vector<WirelessSwitchDto> getSwitchList();
	std::string getJsonStringSwitches();

	bool toggleSwitch(std::string, ChangeService, std::string);
	bool addSwitch(std::vector<std::string>, ChangeService, std::string);
	bool updateSwitch(std::vector<std::string>, ChangeService, std::string);
	bool deleteSwitch(int, ChangeService, std::string);
	bool toggleAllSwitches(ChangeService, std::string);

public:
	RemoteService();
	~RemoteService();

	void Initialize(FileController, std::string);

	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);

	bool ActivateSockets(std::vector<std::string>, ChangeService, std::string);

	int GetRaspberry();
	int GetPort();

	std::vector<ScheduleDto> GetScheduleList();

	std::string GetArea();
	std::string GetSensor();
	std::string GetUrl();
	std::string GetCameraUrl();
	std::vector<std::string> GetMediaMirrorList();
	std::string GetTemperatureGraphUrl();

	void LoadData();
};

#endif
