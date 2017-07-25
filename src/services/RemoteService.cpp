#include "RemoteService.h"

/*===============PUBLIC==============*/

RemoteService::RemoteService()
{
}

RemoteService::~RemoteService()
{
}

void RemoteService::Initialize(FileController fileController, std::string settingsFile)
{
	_fileController = fileController;
	_settingsFile = settingsFile;
	loadSettings();
}

std::string RemoteService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	//--------------------GET--------------------
	if (action == GET)
	{
		if (data[4] == RASPBERRY)
		{
			return Tools::ConvertIntToStr(GetRaspberry());
		}
		else if (data[4] == AREA)
		{
			return GetArea();
		}
		else if (data[4] == SENSOR)
		{
			return GetSensor();
		}
		else if (data[4] == URL)
		{
			if (data[5] == MAIN)
			{
				return GetUrl();
			}
			else if (data[5] == CAMERA)
			{
				return GetCameraUrl();
			}
			else if (data[5] == TEMPERATURE)
			{
				return GetTemperatureGraphUrl();
			}
			else
			{
				return "Error 120:Action not found for remote";
			}
		}
		else if (data[4] == GPIO)
		{
			if (data.size() == 6)
			{
				if (data[5] == REDUCED)
				{
					return getGpiosReducedString();
				}
			}
			else
			{
				return getGpiosRestString();
			}
		}
		else if (data[4] == SCHEDULE)
		{
			if (data.size() == 6)
			{
				if (data[5] == REDUCED)
				{
					return getSchedulesReducedString();
				}
			}
			else
			{
				return getSchedulesRestString();
			}
		}
		else if (data[4] == SOCKET)
		{
			if (data.size() == 6)
			{
				if (data[5] == REDUCED)
				{
					return getSocketsReducedString();
				}
			}
			else
			{
				return getSocketsRestString();
			}
		}
		else
		{
			return "Error 120:Action not found for remote";
		}
	}
	//--------------------ADD--------------------
	else if (action == ADD)
	{
		if (data[4] == GPIO)
		{
			if (data.size() == 8)
			{
				if (addGpio(data, changeService, username))
				{
					return "addgpio:1";
				}
				else
				{
					return "Error 51:Could not add gpio";
				}
			}
			else
			{
				return "Error 55:Wrong word size for gpio";
			}
		}
		else if (data[4] == SCHEDULE)
		{
			if (data.size() == 16)
			{
				if (addSchedule(data, changeService, username))
				{
					return "addschedule:1";
				}
				else
				{
					return "Error 61:Could not add schedule";
				}
			}
			else
			{
				return "Error 65:Wrong word size for schedule";
			}
		}
		else if (data[4] == SOCKET)
		{
			if (data.size() == 9)
			{
				if (addSocket(data, changeService, username))
				{
					return "addsocket:1";
				}
				else
				{
					return "Error 71:Could not add socket";
				}
			}
			else
			{
				return "Error 75:Wrong word size for socket";
			}
		}
		else
		{
			return "Error 120:Action not found for remote";
		}
	}
	//-------------------UPDATE------------------
	else if (action == UPDATE)
	{
		if (data[4] == GPIO)
		{
			if (data.size() == 8)
			{
				if (updateGpio(data, changeService, username))
				{
					return "updategpio:1";
				}
				else
				{
					return "Error 51:Could not update gpio";
				}
			}
			else
			{
				return "Error 55:Wrong word size for gpio";
			}
		}
		else if (data[4] == SCHEDULE)
		{
			if (data.size() == 16)
			{
				if (updateSchedule(data, changeService, username))
				{
					return "updateschedule:1";
				}
				else
				{
					return "Error 61:Could not update schedule";
				}
			}
			else
			{
				return "Error 65:Wrong word size for schedule";
			}
		}
		else if (data[4] == SOCKET)
		{
			if (data.size() == 9)
			{
				if (updateSocket(data, changeService, username))
				{
					return "updatesocket:1";
				}
				else
				{
					return "Error 71:Could update add socket";
				}
			}
			else
			{
				return "Error 75:Wrong word size for socket";
			}
		}
		else
		{
			return "Error 120:Action not found for remote";
		}
	}
	//-------------------DELETE------------------
	else if (action == DELETE)
	{
		if (data[4] == GPIO)
		{
			if (deleteGpio(data[5], changeService, username))
			{
				return "deletegpio:1";
			}
			else
			{
				return "Error 52:Could not delete gpio";
			}
		}
		else if (data[4] == SCHEDULE)
		{
			if (deleteSchedule(data[5], changeService, username))
			{
				return "deleteschedule:1";
			}
			else
			{
				return "Error 62:Could not delete schedule";
			}
		}
		else if (data[4] == SOCKET)
		{
			if (deleteSocket(data[5], changeService, username))
			{
				return "deletesocket:1";
			}
			else
			{
				return "Error 72:Could not delete socket";
			}
		}
		else
		{
			return "Error 120:Action not found for remote";
		}
	}
	//--------------------SET--------------------
	else if (action == SET)
	{
		if (data[4] == GPIO)
		{
			if (data.size() == 7)
			{
				if (data[5] == ALL)
				{
					if (atoi(data[6].c_str()) == 1)
					{
						if (setAllGpios(1, changeService, username))
						{
							return "activateAllGpios:1";
						}
						else
						{
							return "Error 53:Could not activate all gpios";
						}
					}
					else if (atoi(data[6].c_str()) == 0)
					{
						if (setAllGpios(0, changeService, username))
						{
							return "deactivateAllGpios:1";
						}
						else
						{
							return "Error 54:Could not deactivate all gpios";
						}
					}
					else
					{
						return "Error 56:Invalid state for gpio";
					}
				}
				else
				{
					if (setGpio(data[5], atoi(data[6].c_str()), changeService, username))
					{
						return "setgpio:1";
					}
					else
					{
						return "Error 50:Could not set gpio";
					}
				}
			}
			else
			{
				return "Error 55:Wrong word size for gpio";
			}
		}
		else if (data[4] == SCHEDULE)
		{
			if (data.size() == 7)
			{
				if (data[5] == ALL)
				{
					if (atoi(data[6].c_str()) == 1)
					{
						if (setAllSchedules(1, changeService, username))
						{
							return "activateAllSchedules:1";
						}
						else
						{
							return "Error 63:Could not activate all schedules";
						}
					}
					else if (atoi(data[6].c_str()) == 0)
					{
						if (setAllSchedules(0, changeService, username))
						{
							return "deactivateAllSchedules:1";
						}
						else
						{
							return "Error 64:Could not deactivate all schedules";
						}
					}
					else
					{
						return "Error 56:Invalid state for gpio";
					}
				}
				else
				{
					if (setSchedule(data[5], atoi(data[6].c_str()), changeService, username))
					{
						return "setschedule:1";
					}
					else
					{
						return "Error 60:Could not set schedule";
					}
				}
			}
			else
			{
				return "Error 65:Wrong word size for schedule";
			}
		}
		else if (data[4] == SOCKET)
		{
			if (data.size() == 7)
			{
				if (data[5] == ALL)
				{
					if (atoi(data[6].c_str()) == 1)
					{
						if (setAllSockets(1, changeService, username))
						{
							return "activateAllSockets:1";
						}
						else
						{
							return "Error 73:Could not activate all sockets";
						}
					}
					else if (atoi(data[6].c_str()) == 0)
					{
						if (setAllSockets(0, changeService, username))
						{
							return "deactivateAllSockets:1";
						}
						else
						{
							return "Error 74:Could not deactivate all sockets";
						}
					}
					else
					{
						return "Error 56:Invalid state for gpio";
					}
				}
				else if (data[5] == SOUND)
				{
					if (atoi(data[6].c_str()) == 1)
					{
						if (setSoundSocket(1, changeService, username))
						{
							return "activateSoundSocket:1";
						}
						else
						{
							return "Error 76:Could not activate sound socket";
						}
					}
					else if (atoi(data[6].c_str()) == 0)
					{
						if (setSoundSocket(0, changeService, username))
						{
							return "deactivateSoundSocket:1";
						}
						else
						{
							return "Error 77:Could not deactivate sound socket";
						}
					}
					else
					{
						return "Error 56:Invalid state for gpio";
					}
				}
				else
				{
					if (setSocket(data[5], atoi(data[6].c_str()), changeService, username))
					{
						return "setsocket:1";
					}
					else
					{
						return "Error 70:Could not set socket";
					}
				}
			}
			else
			{
				return "Error 75:Wrong word size for socket";
			}
		}
		else
		{
			return "Error 120:Action not found for remote";
		}
	}
	//-------------------ERROR-------------------
	else
	{
		return "Error 120:Action not found for remote";
	}
}

bool RemoteService::ActivateSockets(std::vector<std::string> socketList, ChangeService changeService, std::string username)
{
	if (socketList.size() == 1)
	{
		if (socketList[0] == "Error 44:No sockets available")
		{
			return false;
		}
	}

	bool success = true;

	for (int socketIndex = 0; socketIndex < socketList.size(); socketIndex++)
	{
		for (int index = 0; index < _socketList.size(); index++)
		{
			if (_socketList[index].GetName() == socketList[socketIndex])
			{
				success &= _socketList[index].SetState(1, _datagpio);

				saveSettings(changeService, username);
				loadSettings();

				break;
			}
		}
	}

	return success;
}

int RemoteService::GetRaspberry()
{
	return _raspberry;
}

int RemoteService::GetPort()
{
	return _port;
}

int RemoteService::GetReceiverGpio()
{
	return _receivergpio;
}

std::vector<ScheduleDto> RemoteService::GetScheduleList()
{
	return _scheduleList;
}

std::string RemoteService::GetArea()
{
	return _area;
}

std::string RemoteService::GetSensor()
{
	return _sensor;
}

std::string RemoteService::GetUrl()
{
	return _url;
}

std::string RemoteService::GetAccessUrl()
{
	return _accessurl;
}

std::string RemoteService::GetCameraUrl()
{
	std::stringstream url;
	url << _url << ":8081";
	return url.str();
}

std::vector<std::string> RemoteService::GetMediaMirrorList()
{
	return _mediaMirrorList;
}

std::string RemoteService::GetTemperatureGraphUrl()
{
	std::stringstream url;
	url << _url << "/cgi-bin/webgui.py";
	return url.str();
}

std::string RemoteService::GetAlarmSound()
{
	return _alarmSound;
}

std::string RemoteService::GetWakeUpSound()
{
	return _wakeUpSound;
}

void RemoteService::ReloadData()
{
	loadSettings();
}

/*==============PRIVATE==============*/

void RemoteService::saveSettings(ChangeService changeService,
								 std::string username)
{
	std::string xmldata = _xmlService.GenerateSettingsXml(
		_port, _datagpio, _receivergpio, _raspberry, _alarmSound, _wakeUpSound, _areaList,
		_sensorList, _urlList, _accessurl, _mediaMirrorList, _socketList, _gpioList, _scheduleList);
	_fileController.SaveFile(_settingsFile, xmldata);
	changeService.UpdateChange("Settings", username);
}

void RemoteService::loadSettings()
{
	std::string settingsFileContent = _fileController.ReadFile(_settingsFile);

	_port = _xmlService.GetPort(settingsFileContent);
	_datagpio = _xmlService.GetDatagpio(settingsFileContent);
	_receivergpio = _xmlService.GetReceivergpio(settingsFileContent);
	_raspberry = _xmlService.GetRaspberry(settingsFileContent);

	_alarmSound = _xmlService.GetAlarmSound(settingsFileContent);
	_wakeUpSound = _xmlService.GetWakeUpSound(settingsFileContent);

	_areaList = _xmlService.GetAreaList(settingsFileContent);
	_area = _areaList.at(_raspberry - 1);

	_sensorList = _xmlService.GetSensorList(settingsFileContent);
	_sensor = _sensorList.at(_raspberry - 1);

	_urlList = _xmlService.GetUrlList(settingsFileContent);
	_url = _urlList.at(_raspberry - 1);

	_accessurl = _xmlService.GetAccessUrl(settingsFileContent);

	_mediaMirrorList = _xmlService.GetMediaMirrorList(settingsFileContent);

	_gpioList = _xmlService.GetGpioList(settingsFileContent);
	_scheduleList = _xmlService.GetScheduleList(settingsFileContent);
	_socketList = _xmlService.GetSocketList(settingsFileContent);
}

//--------------------------Data-------------------------//

int RemoteService::getDataGpio()
{
	return _datagpio;
}

//--------------------------Area-------------------------//

std::vector<std::string> RemoteService::getAreaList()
{
	return _areaList;
}

//-------------------------Sensor------------------------//

std::vector<std::string> RemoteService::getSensorList()
{
	return _sensorList;
}

//---------------------------Url-------------------------//

std::vector<std::string> RemoteService::getUrlList()
{
	return _urlList;
}

//-------------------------Gpios-------------------------//

std::string RemoteService::getGpiosString()
{
	std::stringstream out;
	for (int index = 0; index < _gpioList.size(); index++)
	{
		out << _gpioList[index].ToString();
	}
	return out.str();
}

std::vector<GpioDto> RemoteService::getGpioList()
{
	return _gpioList;
}

std::string RemoteService::getGpiosRestString()
{
	std::stringstream out;

	for (int index = 0; index < _gpioList.size(); index++)
	{
		out << "{gpio:"
			<< "{Name:" << _gpioList[index].GetName() << "};"
			<< "{Gpio:" << Tools::ConvertIntToStr(_gpioList[index].GetGpio()) << "};"
			<< "{State:" << Tools::ConvertIntToStr(_gpioList[index].GetState()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string RemoteService::getGpiosReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _gpioList.size(); index++)
	{
		out << "gpio:"
			<< _gpioList[index].GetName() << "::"
			<< Tools::ConvertIntToStr(_gpioList[index].GetGpio()) << "::"
			<< Tools::ConvertIntToStr(_gpioList[index].GetState()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::setGpio(std::string name, int state, ChangeService changeService, std::string username)
{
	bool success = false;

	for (int index = 0; index < _gpioList.size(); index++)
	{
		if (_gpioList[index].GetName() == name)
		{
			success = _gpioList[index].SetState(state);

			saveSettings(changeService, username);
			loadSettings();

			break;
		}
	}

	return success;
}

bool RemoteService::addGpio(std::vector<std::string> newGpioData, ChangeService changeService, std::string username)
{
	GpioDto newGpio(newGpioData[5], atoi(newGpioData[6].c_str()), atoi(newGpioData[7].c_str()));
	_gpioList.push_back(newGpio);

	saveSettings(changeService, username);
	loadSettings();

	return true;
}

bool RemoteService::updateGpio(std::vector<std::string> updateGpioData, ChangeService changeService, std::string username)
{
	GpioDto updateGpio(updateGpioData[5], atoi(updateGpioData[6].c_str()), atoi(updateGpioData[7].c_str()));

	for (int index = 0; index < _gpioList.size(); index++)
	{
		if (_gpioList[index].GetName() == updateGpio.GetName())
		{
			_gpioList[index] = updateGpio;

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteGpio(std::string name, ChangeService changeService, std::string username)
{
	std::vector<GpioDto>::iterator it = _gpioList.begin();

	while (it != _gpioList.end())
	{
		if ((*it).GetName() == name)
		{
			it = _gpioList.erase(it);

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}

bool RemoteService::setAllGpios(int state, ChangeService changeService, std::string username)
{
	bool success = true;

	for (int index = 0; index < _gpioList.size(); index++)
	{
		success &= _gpioList[index].SetState(state);
	}

	saveSettings(changeService, username);
	loadSettings();

	return success;
}

//-----------------------Schedules-----------------------//

std::string RemoteService::getSchedulesString()
{
	std::stringstream out;
	for (int index = 0; index < _scheduleList.size(); index++)
	{
		out << _scheduleList[index].ToString();
	}
	return out.str();
}

std::string RemoteService::getSchedulesRestString()
{
	std::stringstream out;

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		out << "{schedule:"
			<< "{Name:" << _scheduleList[index].GetName() << "};"
			<< "{Socket:" << _scheduleList[index].GetSocket() << "};"
			<< "{Gpio:" << _scheduleList[index].GetGpio() << "};"
			<< "{Weekday:" << Tools::ConvertIntToStr(_scheduleList[index].GetWeekday()) << "};"
			<< "{Hour:" << Tools::ConvertIntToStr(_scheduleList[index].GetHour()) << "};"
			<< "{Minute:" << Tools::ConvertIntToStr(_scheduleList[index].GetMinute()) << "};"
			<< "{OnOff:" << Tools::ConvertIntToStr(_scheduleList[index].GetOnoff()) << "};"
			<< "{IsTimer:" << Tools::ConvertIntToStr(_scheduleList[index].GetIsTimer()) << "};"
			<< "{PlaySound:" << Tools::ConvertIntToStr(_scheduleList[index].GetPlaySound()) << "};"
			<< "{Raspberry:" << Tools::ConvertIntToStr(_scheduleList[index].GetPlayRaspberry()) << "};"
			<< "{State:" << Tools::ConvertIntToStr(_scheduleList[index].GetStatus()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string RemoteService::getSchedulesReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		out << "schedule:"
			<< _scheduleList[index].GetName() << "::"
			<< _scheduleList[index].GetSocket() << "::"
			<< _scheduleList[index].GetGpio() << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetWeekday()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetHour()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetMinute()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetOnoff()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetIsTimer()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetPlaySound()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetPlayRaspberry()) << "::"
			<< Tools::ConvertIntToStr(_scheduleList[index].GetStatus()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::setSchedule(std::string name, int state, ChangeService changeService, std::string username)
{
	bool success = false;

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		if (_scheduleList[index].GetName() == name)
		{
			_scheduleList[index].SetStatus(state);
			success = true;

			saveSettings(changeService, username);
			loadSettings();

			break;
		}
	}

	return success;
}

bool RemoteService::addSchedule(std::vector<std::string> newScheduleData,
								ChangeService changeService, std::string username)
{
	ScheduleDto newSchedule(
		newScheduleData[5],
		newScheduleData[6],
		newScheduleData[7],
		atoi(newScheduleData[8].c_str()),
		atoi(newScheduleData[9].c_str()),
		atoi(newScheduleData[10].c_str()),
		atoi(newScheduleData[11].c_str()),
		atoi(newScheduleData[12].c_str()),
		atoi(newScheduleData[13].c_str()),
		atoi(newScheduleData[14].c_str()),
		atoi(newScheduleData[15].c_str()));
	_scheduleList.push_back(newSchedule);

	saveSettings(changeService, username);
	loadSettings();

	return true;
}

bool RemoteService::updateSchedule(std::vector<std::string> updateScheduleData, ChangeService changeService, std::string username)
{
	ScheduleDto updateSchedule(
		updateScheduleData[5],
		updateScheduleData[6],
		updateScheduleData[7],
		atoi(updateScheduleData[8].c_str()),
		atoi(updateScheduleData[9].c_str()),
		atoi(updateScheduleData[10].c_str()),
		atoi(updateScheduleData[11].c_str()),
		atoi(updateScheduleData[12].c_str()),
		atoi(updateScheduleData[13].c_str()),
		atoi(updateScheduleData[14].c_str()),
		atoi(updateScheduleData[15].c_str()));

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		if (_scheduleList[index].GetName() == updateSchedule.GetName())
		{
			_scheduleList[index] = updateSchedule;

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteSchedule(std::string name, ChangeService changeService, std::string username)
{
	std::vector<ScheduleDto>::iterator it = _scheduleList.begin();

	while (it != _scheduleList.end())
	{
		if ((*it).GetName() == name)
		{
			it = _scheduleList.erase(it);

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}

bool RemoteService::setAllSchedules(int state, ChangeService changeService, std::string username)
{
	Tools::ConvertIntToStr(state).c_str();
	bool success = true;

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		success &= _scheduleList[index].SetStatus(state);
	}

	saveSettings(changeService, username);
	loadSettings();

	return success;
}

//------------------------Sockets------------------------//

std::string RemoteService::getSocketsString()
{
	std::stringstream out;
	for (int index = 0; index < _socketList.size(); index++)
	{
		out << _socketList[index].ToString();
	}
	return out.str();
}

std::vector<WirelessSocketDto> RemoteService::getSocketList()
{
	return _socketList;
}

std::string RemoteService::getSocketsRestString()
{
	std::stringstream out;

	for (int index = 0; index < _socketList.size(); index++)
	{
		out << "{socket:"
			<< "{Name:" << _socketList[index].GetName() << "};"
			<< "{Area:" << _socketList[index].GetArea() << "};"
			<< "{Code:" << _socketList[index].GetCode() << "};"
			<< "{State:" << Tools::ConvertIntToStr(_socketList[index].GetState()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string RemoteService::getSocketsReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _socketList.size(); index++)
	{
		out << "socket:"
			<< _socketList[index].GetName() << "::"
			<< _socketList[index].GetArea() << "::"
			<< _socketList[index].GetCode() << "::"
			<< Tools::ConvertIntToStr(_socketList[index].GetState()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::setSocket(std::string name, int state, ChangeService changeService, std::string username)
{
	bool success = false;
	bool foundSocket = false;

	for (int index = 0; index < _socketList.size(); index++)
	{
		if (_socketList[index].GetName() == name)
		{
			success = _socketList[index].SetState(state, _datagpio);
			foundSocket = true;

			saveSettings(changeService, username);
			loadSettings();

			break;
		}
	}

	return success && foundSocket;
}

bool RemoteService::addSocket(std::vector<std::string> newSocketData, ChangeService changeService, std::string username)
{
	WirelessSocketDto newSocket(newSocketData[5], newSocketData[6], newSocketData[7], atoi(newSocketData[8].c_str()));
	_socketList.push_back(newSocket);

	saveSettings(changeService, username);
	loadSettings();

	return true;
}

bool RemoteService::updateSocket(std::vector<std::string> updateSocketData, ChangeService changeService, std::string username)
{
	WirelessSocketDto updateSocket(updateSocketData[5], updateSocketData[6], updateSocketData[7], atoi(updateSocketData[8].c_str()));

	for (int index = 0; index < _socketList.size(); index++)
	{
		if (_socketList[index].GetName() == updateSocket.GetName())
		{
			_socketList[index] = updateSocket;

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteSocket(std::string name, ChangeService changeService, std::string username)
{
	std::vector<WirelessSocketDto>::iterator it = _socketList.begin();

	while (it != _socketList.end())
	{
		if ((*it).GetName() == name)
		{
			it = _socketList.erase(it);

			saveSettings(changeService, username);
			loadSettings();

			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

bool RemoteService::setAllSockets(int state, ChangeService changeService, std::string username)
{
	bool success = true;

	for (int index = 0; index < _socketList.size(); index++)
	{
		success &= _socketList[index].SetState(state, _datagpio);
	}

	saveSettings(changeService, username);
	loadSettings();

	return success;
}

bool RemoteService::setSoundSocket(int state, ChangeService changeService, std::string username)
{
	bool success = true;
	bool foundSocket = false;

	for (int index = 0; index < _socketList.size(); index++)
	{
		if (_socketList[index].GetArea() == _area)
		{
			if (_socketList[index].GetName().find("Sound") != std::string::npos)
			{
				success = _socketList[index].SetState(state, _datagpio);
				foundSocket = true;

				saveSettings(changeService, username);
				loadSettings();

				break;
			}
		}
	}

	return success && foundSocket;
}
