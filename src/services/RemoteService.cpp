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
	LoadData();
}

std::string RemoteService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	//--------------------GET--------------------
	if (action == GET)
	{
		if (actionParameter == RASPBERRY)
		{
			return Tools::ConvertIntToStr(GetRaspberry());
		}
		else if (actionParameter == AREA)
		{
			return GetArea();
		}
		else if (actionParameter == SENSOR)
		{
			return GetSensor();
		}
		else if (actionParameter == URL)
		{
			if (data[REMOTE_PARAMETER_INDEX] == MAIN)
			{
				return GetUrl();
			}
			else if (data[REMOTE_PARAMETER_INDEX] == CAMERA)
			{
				return GetCameraUrl();
			}
			else if (data[REMOTE_PARAMETER_INDEX] == TEMPERATURE)
			{
				return GetTemperatureGraphUrl();
			}
			return REMOTE_ERROR_NR_120;
		}
		else if (actionParameter == GPIO)
		{
			return getJsonStringGpios();
		}
		else if (actionParameter == SCHEDULE)
		{
			return getJsonStringSchedules();
		}
		else if (actionParameter == SOCKET)
		{
			return getJsonStringSockets();
		}
		else if (actionParameter == SWITCH)
		{
			return getJsonStringSwitches();
		}
		return REMOTE_ERROR_NR_120;
	}

	//--------------------ADD--------------------
	else if (action == ADD)
	{
		if (actionParameter == GPIO)
		{
			if (data.size() == GPIO_DATA_SIZE)
			{
				if (addGpio(data, changeService, username))
				{
					return GPIO_ADD_SUCCESS;
				}
				return GPIO_ERROR_NR_51;
			}
			return GPIO_ERROR_NR_55;
		}
		else if (actionParameter == SCHEDULE)
		{
			if (data.size() == SCHEDULE_DATA_SIZE)
			{
				if (addSchedule(data, changeService, username))
				{
					return SCHEDULE_ADD_SUCCESS;
				}
				return SCHEDULE_ERROR_NR_61;
			}
			return SCHEDULE_ERROR_NR_65;
		}
		else if (actionParameter == SOCKET)
		{
			if (data.size() == SOCKET_DATA_SIZE)
			{
				if (addSocket(data, changeService, username))
				{
					return SOCKET_ADD_SUCCESS;
				}
				return SOCKET_ERROR_NR_71;
			}
			return SOCKET_ERROR_NR_75;
		}
		else if (actionParameter == SWITCH)
		{
			if (data.size() == SWITCH_DATA_SIZE)
			{
				if (addSwitch(data, changeService, username))
				{
					return SWITCH_ADD_SUCCESS;
				}
				return SWITCH_ERROR_NR_81;
			}
			return SWITCH_ERROR_NR_85;
		}
		return REMOTE_ERROR_NR_120;
	}

	//-------------------UPDATE------------------
	else if (action == UPDATE)
	{
		if (actionParameter == GPIO)
		{
			if (data.size() == GPIO_DATA_SIZE)
			{
				if (updateGpio(data, changeService, username))
				{
					return GPIO_UPDATE_SUCCESS;
				}
				return GPIO_ERROR_NR_52;
			}
			return GPIO_ERROR_NR_55;
		}
		else if (actionParameter == SCHEDULE)
		{
			if (data.size() == SCHEDULE_DATA_SIZE)
			{
				if (updateSchedule(data, changeService, username))
				{
					return SCHEDULE_UPDATE_SUCCESS;
				}
				return SCHEDULE_ERROR_NR_62;
			}
			return SCHEDULE_ERROR_NR_65;
		}
		else if (actionParameter == SOCKET)
		{
			if (data.size() == SOCKET_DATA_SIZE)
			{
				if (updateSocket(data, changeService, username))
				{
					return SOCKET_UPDATE_SUCCESS;
				}
				return SOCKET_ERROR_NR_72;
			}
			return SOCKET_ERROR_NR_75;
		}
		else if (actionParameter == SWITCH)
		{
			if (data.size() == SWITCH_DATA_SIZE)
			{
				if (updateSwitch(data, changeService, username))
				{
					return SWITCH_UPDATE_SUCCESS;
				}
				return SWITCH_ERROR_NR_82;
			}
			return SWITCH_ERROR_NR_85;
		}
		return REMOTE_ERROR_NR_120;
	}

	//-------------------DELETE------------------
	else if (action == DELETE)
	{
		if (actionParameter == GPIO)
		{
			if (deleteGpio(Tools::ConvertStrToInt(data[GPIO_TYPE_ID_INDEX].c_str()), changeService, username))
			{
				return GPIO_DELETE_SUCCESS;
			}
			return GPIO_ERROR_NR_53;
		}
		else if (actionParameter == SCHEDULE)
		{
			if (deleteSchedule(Tools::ConvertStrToInt(data[SCHEDULE_ID_INDEX].c_str()), changeService, username))
			{
				return SCHEDULE_DELETE_SUCCESS;
			}
			return SCHEDULE_ERROR_NR_63;
		}
		else if (actionParameter == SOCKET)
		{
			if (deleteSocket(atoi(data[SOCKET_TYPE_ID_INDEX].c_str()), changeService, username))
			{
				return SOCKET_DELETE_SUCCESS;
			}
			return SOCKET_ERROR_NR_73;
		}
		else if (actionParameter == SWITCH)
		{
			if (deleteSwitch(atoi(data[SWITCH_TYPE_ID_INDEX].c_str()), changeService, username))
			{
				return SWITCH_DELETE_SUCCESS;
			}
			return SWITCH_ERROR_NR_83;
		}
		return REMOTE_ERROR_NR_120;
	}

	//--------------------SET--------------------
	else if (action == SET)
	{
		if (actionParameter == GPIO)
		{
			if (data.size() == GPIO_SET_SIZE)
			{
				int newState = atoi(data[GPIO_SET_STATE_INDEX].c_str());

				if (data[REMOTE_PARAMETER_INDEX] == ALL)
				{
					if (newState == 1)
					{
						if (setAllGpios(1, changeService, username))
						{
							return GPIO_ACTIVATE_ALL_SUCCESS;
						}
						return GPIO_ERROR_NR_54;
					}
					else if (newState == 0)
					{
						if (setAllGpios(0, changeService, username))
						{
							return GPIO_DEACTIVATE_ALL_SUCCESS;
						}
						return GPIO_ERROR_NR_56;
					}
					return GPIO_ERROR_NR_57;
				}
				else
				{
					if (setGpio(data[GPIO_NAME_INDEX], newState, changeService, username))
					{
						return GPIO_SET_SUCCESS;
					}
					return GPIO_ERROR_NR_50;
				}
			}
			return GPIO_ERROR_NR_55;
		}

		else if (actionParameter == SCHEDULE)
		{
			if (data.size() == SCHEDULE_SET_SIZE)
			{
				int newState = atoi(data[SCHEDULE_SET_STATE_INDEX].c_str());

				if (data[REMOTE_PARAMETER_INDEX] == ALL)
				{
					if (newState == 1)
					{
						if (setAllSchedules(1, changeService, username))
						{
							return SCHEDULE_ACTIVATE_ALL_SUCCESS;
						}
						return SCHEDULE_ERROR_NR_64;
					}
					else if (newState == 0)
					{
						if (setAllSchedules(0, changeService, username))
						{
							return SCHEDULE_DEACTIVATE_ALL_SUCCESS;
						}
						return SCHEDULE_ERROR_NR_66;
					}
					return SCHEDULE_ERROR_NR_67;
				}
				else
				{
					if (setSchedule(Tools::ConvertStrToInt(data[SCHEDULE_ID_INDEX].c_str()), newState, changeService, username))
					{
						return SCHEDULE_SET_SUCCESS;
					}
					return SCHEDULE_ERROR_NR_60;
				}
			}
			return SCHEDULE_ERROR_NR_65;
		}

		else if (actionParameter == SOCKET)
		{
			if (data.size() == SOCKET_SET_SIZE)
			{
				int newState = atoi(data[SOCKET_SET_STATE_INDEX].c_str());

				if (data[REMOTE_PARAMETER_INDEX] == ALL)
				{
					if (newState == 1)
					{
						if (setAllSockets(1, changeService, username))
						{
							return SOCKET_ACTIVATE_ALL_SUCCESS;
						}
						return SOCKET_ERROR_NR_74;
					}
					else if (newState == 0)
					{
						if (setAllSockets(0, changeService, username))
						{
							return SOCKET_DEACTIVATE_ALL_SUCCESS;
						}
						return SOCKET_ERROR_NR_76;
					}
					return SOCKET_ERROR_NR_77;
				}
				else
				{
					if (setSocket(data[SOCKET_NAME_INDEX], newState, changeService, username))
					{
						return SOCKET_SET_SUCCESS;
					}
					return SOCKET_ERROR_NR_70;
				}
			}
			return SOCKET_ERROR_NR_75;
		}
		return REMOTE_ERROR_NR_120;
	}

	//--------------------TOGGLE--------------------
	else if (action == TOGGLE)
	{
		if (actionParameter == SWITCH)
		{
			if (data.size() == SWITCH_TOGGLE_SIZE)
			{
				if (data[REMOTE_PARAMETER_INDEX] == ALL)
				{
					if (toggleAllSwitches(changeService, username))
					{
						return SWITCH_TOGGLE_ALL_SUCCESS;
					}
					return SWITCH_ERROR_NR_84;
				}
				else
				{
					if (toggleSwitch(data[SOCKET_NAME_INDEX], changeService, username))
					{
						return SWITCH_TOGGLE_SUCCESS;
					}
					return SWITCH_ERROR_NR_80;
				}
			}
		}
	}

	//-------------------ERROR-------------------
	return REMOTE_ERROR_NR_120;
}

bool RemoteService::ActivateSockets(std::vector<std::string> socketList, ChangeService changeService, std::string username)
{
	if (socketList.size() == 1)
	{
		if (socketList[0] == SOCKET_ERROR_NR_78)
		{
			return false;
		}
	}

	bool success = true;

	for (int socketIndex = 0; socketIndex < socketList.size(); socketIndex++)
	{
		std::string socketName = socketList[socketIndex];

		for (int index = 0; index < _socketList.size(); index++)
		{
			if (_socketList[index].GetName() == socketName)
			{
				success &= setSocket(socketName, 1, changeService, username);
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

void RemoteService::LoadData()
{
	std::string settingsFileContent = _fileController.ReadFile(_settingsFile);

	_port = _xmlService.GetPort(settingsFileContent);
	_datagpio = _xmlService.GetDatagpio(settingsFileContent);
	_raspberry = _xmlService.GetRaspberry(settingsFileContent);

	_areaList = _xmlService.GetAreaList(settingsFileContent);
	_area = _areaList.at(_raspberry - 1);

	_sensorList = _xmlService.GetSensorList(settingsFileContent);
	_sensor = _sensorList.at(_raspberry - 1);

	_urlList = _xmlService.GetUrlList(settingsFileContent);
	_url = _urlList.at(_raspberry - 1);

	_mediaMirrorList = _xmlService.GetMediaMirrorList(settingsFileContent);

	_gpioList = _xmlService.GetGpioList(settingsFileContent);
	_scheduleList = _xmlService.GetScheduleList(settingsFileContent);
	_socketList = _xmlService.GetSocketList(settingsFileContent);
	_switchList = _xmlService.GetSwitchList(settingsFileContent);
}

/*==============PRIVATE==============*/

void RemoteService::saveSettings(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateSettingsXml(
		_port,
		_datagpio,
		_raspberry,
		_areaList,
		_sensorList,
		_urlList,
		_mediaMirrorList,
		_socketList,
		_gpioList,
		_scheduleList,
		_switchList);
	_fileController.SaveFile(_settingsFile, xmldata);
	changeService.UpdateChange("Settings", username);
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

std::vector<GpioDto> RemoteService::getGpioList()
{
	return _gpioList;
}

std::string RemoteService::getJsonStringGpios()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _gpioList.size(); index++)
	{
		GpioDto gpio = _gpioList[index];
		data << gpio.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

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
			LoadData();

			break;
		}
	}

	return success;
}

bool RemoteService::addGpio(std::vector<std::string> newGpioData, ChangeService changeService, std::string username)
{
	GpioDto newGpio(
		atoi(newGpioData[GPIO_TYPE_ID_INDEX].c_str()),
		newGpioData[GPIO_NAME_INDEX],
		atoi(newGpioData[GPIO_GPIO_INDEX].c_str()),
		atoi(newGpioData[GPIO_STATE_INDEX].c_str()));
	_gpioList.push_back(newGpio);

	saveSettings(changeService, username);
	LoadData();

	return true;
}

bool RemoteService::updateGpio(std::vector<std::string> updateGpioData, ChangeService changeService, std::string username)
{
	int typeId = Tools::ConvertStrToInt(updateGpioData[GPIO_TYPE_ID_INDEX].c_str());

	for (int index = 0; index < _gpioList.size(); index++)
	{
		if (_gpioList[index].GetTypeId() == typeId)
		{
			_gpioList[index].SetName(updateGpioData[GPIO_NAME_INDEX]);
			_gpioList[index].SetGpio(atoi(updateGpioData[GPIO_GPIO_INDEX].c_str()));
			_gpioList[index].SetState(atoi(updateGpioData[GPIO_STATE_INDEX].c_str()));

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteGpio(int typeId, ChangeService changeService, std::string username)
{
	std::vector<GpioDto>::iterator it = _gpioList.begin();

	while (it != _gpioList.end())
	{
		if ((*it).GetTypeId() == typeId)
		{
			it = _gpioList.erase(it);

			saveSettings(changeService, username);
			LoadData();

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
	LoadData();

	return success;
}

//-----------------------Schedules-----------------------//

std::string RemoteService::getJsonStringSchedules()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _scheduleList.size(); index++)
	{
		ScheduleDto schedule = _scheduleList[index];
		data << schedule.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::setSchedule(int id, bool isActice, ChangeService changeService, std::string username)
{
	bool success = false;

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		if (_scheduleList[index].GetId() == id)
		{
			_scheduleList[index].SetIsActive(isActice);
			success = true;

			saveSettings(changeService, username);
			LoadData();

			break;
		}
	}

	return success;
}

bool RemoteService::addSchedule(std::vector<std::string> newScheduleData, ChangeService changeService, std::string username)
{
	ScheduleDto newSchedule(
		atoi(newScheduleData[SCHEDULE_ID_INDEX].c_str()),
		newScheduleData[SCHEDULE_NAME_INDEX],
		newScheduleData[SCHEDULE_SOCKET_INDEX],
		newScheduleData[SCHEDULE_GPIO_INDEX],
		newScheduleData[SCHEDULE_SWITCH_INDEX],
		atoi(newScheduleData[SCHEDULE_WEEKDAY_INDEX].c_str()),
		atoi(newScheduleData[SCHEDULE_HOUR_INDEX].c_str()),
		atoi(newScheduleData[SCHEDULE_MINUTE_INDEX].c_str()),
		Tools::ConvertStrToBool(newScheduleData[SCHEDULE_ACTION_INDEX].c_str()),
		Tools::ConvertStrToBool(newScheduleData[SCHEDULE_ISTIMER_INDEX].c_str()),
		Tools::ConvertStrToBool(newScheduleData[SCHEDULE_ISACTIVE_INDEX].c_str()));

	_scheduleList.push_back(newSchedule);

	saveSettings(changeService, username);
	LoadData();

	return true;
}

bool RemoteService::updateSchedule(std::vector<std::string> updateScheduleData, ChangeService changeService, std::string username)
{
	int id = atoi(updateScheduleData[SCHEDULE_ID_INDEX].c_str());

	for (int index = 0; index < _scheduleList.size(); index++)
	{
		if (_scheduleList[index].GetId() == id)
		{
			_scheduleList[index].SetSocket(updateScheduleData[SCHEDULE_SOCKET_INDEX]);
			_scheduleList[index].SetGpio(updateScheduleData[SCHEDULE_GPIO_INDEX]);
			_scheduleList[index].SetSwitch(updateScheduleData[SCHEDULE_SWITCH_INDEX]);
			_scheduleList[index].SetWeekday(atoi(updateScheduleData[SCHEDULE_WEEKDAY_INDEX].c_str()));
			_scheduleList[index].SetHour(atoi(updateScheduleData[SCHEDULE_HOUR_INDEX].c_str()));
			_scheduleList[index].SetMinute(atoi(updateScheduleData[SCHEDULE_MINUTE_INDEX].c_str()));
			_scheduleList[index].SetAction(Tools::ConvertStrToBool(updateScheduleData[SCHEDULE_ACTION_INDEX].c_str()));
			_scheduleList[index].SetIsTimer(Tools::ConvertStrToBool(updateScheduleData[SCHEDULE_ISTIMER_INDEX].c_str()));
			_scheduleList[index].SetIsActive(Tools::ConvertStrToBool(updateScheduleData[SCHEDULE_ISACTIVE_INDEX].c_str()));

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteSchedule(int id, ChangeService changeService, std::string username)
{
	std::vector<ScheduleDto>::iterator it = _scheduleList.begin();

	while (it != _scheduleList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _scheduleList.erase(it);

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}

bool RemoteService::setAllSchedules(bool isActive, ChangeService changeService, std::string username)
{
	for (int index = 0; index < _scheduleList.size(); index++)
	{
		_scheduleList[index].SetIsActive(isActive);
	}

	saveSettings(changeService, username);
	LoadData();

	return true;
}

//------------------------Sockets------------------------//

std::vector<WirelessSocketDto> RemoteService::getSocketList()
{
	return _socketList;
}

std::string RemoteService::getJsonStringSockets()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _socketList.size(); index++)
	{
		WirelessSocketDto wirelessSocket = _socketList[index];
		data << wirelessSocket.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::setSocket(std::string name, int state, ChangeService changeService, std::string username)
{
	for (int index = 0; index < _socketList.size(); index++)
	{
		if (_socketList[index].GetName() == name)
		{

			time_t now;
			struct tm now_info;
			now = time(0);
			localtime_r(&now, &now_info);

			bool success = _socketList[index].SetState(state, _datagpio,
				now_info.tm_hour, now_info.tm_min,
				now_info.tm_mday, (now_info.tm_mon + 1), (now_info.tm_year + 1900),
				username);

			saveSettings(changeService, username);
			LoadData();

			return success;
		}
	}

	return false;
}

bool RemoteService::addSocket(std::vector<std::string> newSocketData, ChangeService changeService, std::string username)
{
	WirelessSocketDto newSocket(
		atoi(newSocketData[SOCKET_TYPE_ID_INDEX].c_str()),
		newSocketData[SOCKET_NAME_INDEX],
		newSocketData[SOCKET_AREA_INDEX],
		newSocketData[SOCKET_CODE_INDEX],
		atoi(newSocketData[SOCKET_STATE_INDEX].c_str()),
		0, 0,
		1, 1, 1970,
		"NULL");

	_socketList.push_back(newSocket);

	saveSettings(changeService, username);
	LoadData();

	return true;
}

bool RemoteService::updateSocket(std::vector<std::string> updateSocketData, ChangeService changeService, std::string username)
{
	int socketTypeId = atoi(updateSocketData[SOCKET_TYPE_ID_INDEX].c_str());

	for (int index = 0; index < _socketList.size(); index++)
	{
		if (_socketList[index].GetTypeId() == socketTypeId)
		{
			_socketList[index].SetName(updateSocketData[SOCKET_NAME_INDEX]);
			_socketList[index].SetArea(updateSocketData[SOCKET_AREA_INDEX]);
			_socketList[index].SetCode(updateSocketData[SOCKET_CODE_INDEX]);
			_socketList[index].SetState(
				atoi(updateSocketData[SOCKET_STATE_INDEX].c_str()), _datagpio,
				_socketList[index].GetLastTriggeredHour(), _socketList[index].GetLastTriggeredMinute(),
				_socketList[index].GetLastTriggeredDay(), _socketList[index].GetLastTriggeredMonth(), _socketList[index].GetLastTriggeredYear(),
				_socketList[index].GetLastTriggeredUserName());

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteSocket(int typeId, ChangeService changeService, std::string username)
{
	std::vector<WirelessSocketDto>::iterator it = _socketList.begin();

	while (it != _socketList.end())
	{
		if ((*it).GetTypeId() == typeId)
		{
			it = _socketList.erase(it);

			saveSettings(changeService, username);
			LoadData();

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
		success &= setSocket(_socketList[index].GetName(), state, changeService, username);
	}

	saveSettings(changeService, username);
	LoadData();

	return success;
}

//------------------------Switches------------------------//

std::vector<WirelessSwitchDto> RemoteService::getSwitchList()
{
	return _switchList;
}

std::string RemoteService::getJsonStringSwitches()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _switchList.size(); index++)
	{
		data << _switchList[index].JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

bool RemoteService::toggleSwitch(std::string name, ChangeService changeService, std::string username)
{
	for (int index = 0; index < _switchList.size(); index++)
	{
		if (_switchList[index].GetName() == name)
		{

			time_t now;
			struct tm now_info;
			now = time(0);
			localtime_r(&now, &now_info);

			bool success = _switchList[index].ToggleSwitch(
				_datagpio,
				now_info.tm_hour, now_info.tm_min,
				now_info.tm_mday, (now_info.tm_mon + 1), (now_info.tm_year + 1900),
				username);

			saveSettings(changeService, username);
			LoadData();

			return success;
		}
	}

	return false;
}

bool RemoteService::addSwitch(std::vector<std::string> newSwitchData, ChangeService changeService, std::string username)
{
	WirelessSwitchDto newSwitch(
		atoi(newSwitchData[SWITCH_TYPE_ID_INDEX].c_str()),
		newSwitchData[SWITCH_NAME_INDEX],
		newSwitchData[SWITCH_AREA_INDEX],
		atoi(newSwitchData[SWITCH_REMOTE_ID_INDEX].c_str()),
		newSwitchData[SWITCH_KEYCODE_INDEX],
		0,
		0, 0,
		1, 1, 1970,
		"NULL");

	_switchList.push_back(newSwitch);

	saveSettings(changeService, username);
	LoadData();

	return true;
}

bool RemoteService::updateSwitch(std::vector<std::string> updateSwitchData, ChangeService changeService, std::string username)
{
	int typeId = atoi(updateSwitchData[SWITCH_TYPE_ID_INDEX].c_str());

	for (int index = 0; index < _switchList.size(); index++)
	{
		if (_switchList[index].GetTypeId() == typeId)
		{
			_switchList[index].SetName(updateSwitchData[SWITCH_NAME_INDEX]);
			_switchList[index].SetArea(updateSwitchData[SWITCH_AREA_INDEX]);
			_switchList[index].SetRemoteId(Tools::ConvertStrToInt(updateSwitchData[SWITCH_REMOTE_ID_INDEX].c_str()));
			_switchList[index].SetKeyCode(Tools::ConvertStrToUnsignedChar(updateSwitchData[SWITCH_KEYCODE_INDEX].c_str()));

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
	}

	return false;
}

bool RemoteService::deleteSwitch(int typeId, ChangeService changeService, std::string username)
{
	std::vector<WirelessSwitchDto>::iterator it = _switchList.begin();

	while (it != _switchList.end())
	{
		if ((*it).GetTypeId() == typeId)
		{
			it = _switchList.erase(it);

			saveSettings(changeService, username);
			LoadData();

			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

bool RemoteService::toggleAllSwitches(ChangeService changeService, std::string username)
{
	bool success = true;

	for (int index = 0; index < _switchList.size(); index++)
	{
		success &= toggleSwitch(_switchList[index].GetName(), changeService, username);
	}

	saveSettings(changeService, username);
	LoadData();

	return success;
}
