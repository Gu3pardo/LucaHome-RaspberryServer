#include <string>
#include <sstream>

namespace patch {
	template<typename T> std::string to_string(const T& n) {
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

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
#include <syslog.h>

#include "common/dto/ScheduleDto.h"
#include "common/dto/ScheduleTaskDto.h"
#include "common/utils/Tools.h"
#include "common/Constants.h"

#include "controller/FileController.h"
#include "controller/MailController.h"
#include "controller/PathController.h"

#include "services/shared/ChangeService.h"

#include "services/AuthentificationService.h"
#include "services/BirthdayService.h"
#include "services/CameraService.h"
#include "services/CoinService.h"
#include "services/InformationService.h"
#include "services/MapContentService.h"
#include "services/MenuService.h"
#include "services/MeterDataService.h"
#include "services/MovieService.h"
#include "services/RemoteService.h"
#include "services/ShoppingListService.h"
#include "services/SystemService.h"
#include "services/TemperatureService.h"

#define BUFLEN 512

using namespace std;

bool _updatedSchedules;
vector<ScheduleDto> _scheduleList;
vector<ScheduleTaskDto> _scheduleTaskList;

MailController _mailController;
FileController _fileController;
PathController _pathController;

AuthentificationService _authentificationService;
BirthdayService _birthdayService;
CameraService _cameraService;
ChangeService _changeService;
CoinService _coinService;
InformationService _informationService;
MenuService _menuService;
MeterDataService _meterDataService;
MapContentService _mapContentService;
MovieService _movieService;
RemoteService _remoteService;
ShoppingListService _shoppingListService;
SystemService _systemService;
TemperatureService _temperatureService;

//TODO reactivate!
//RCSwitch _receiverSwitch;

pthread_mutex_t birthdaysMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t changesMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t gpiosMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t moviesMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t schedulesMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t socketsMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t switchesMutex = PTHREAD_MUTEX_INITIALIZER;

string executeCmd(string cmd, int source) {
	if (cmd.length() < CMD_MIN_LENGTH) {
		return COMMAND_ERROR_NR_21;
	}
	if (source != CMD_SOURCE_EXTERNAL && source != CMD_SOURCE_SCHEDULER) {
		return AUTHENTIFICATION_ERROR_NR_14;
	}

	vector < string > data = Tools::Explode(":", cmd);
	if (data.size() < 1) {
		return AUTHENTIFICATION_ERROR_NR_13;
	}
	if (data.size() < 2) {
		return AUTHENTIFICATION_ERROR_NR_12;
	}
	if (data.size() < 3) {
		return COMMAND_ERROR_NR_24;
	}
	if (data.size() < 4) {
		return COMMAND_ERROR_NR_23;
	}
	if (data.size() < 5) {
		return COMMAND_ERROR_NR_25;
	}

	string username = data[USER_NAME_INDEX];
	string password = data[PASSWORD_INDEX];
	string category = data[CATEGORY_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (username == "") {
		return AUTHENTIFICATION_ERROR_NR_13;
	}
	if (password == "") {
		return AUTHENTIFICATION_ERROR_NR_12;
	}
	if (category == "") {
		return COMMAND_ERROR_NR_24;
	}
	if (action == "") {
		return COMMAND_ERROR_NR_23;
	}
	if (actionParameter == "") {
		return COMMAND_ERROR_NR_25;
	}

	if (username == SCHEDULER && source != CMD_SOURCE_SCHEDULER) {
		return COMMAND_ERROR_NR_26;
	}

	// TODO activate if logger is wished
	//_logger.addLog("DEBUG", data, username);

	//---------------Authentificate user--------------
	if (!_authentificationService.AuthentificateUser(username, password)) {
		return AUTHENTIFICATION_ERROR_NR_10;
	}
	if (!_authentificationService.AuthentificateUserAction(username, password, action)) {
		return AUTHENTIFICATION_ERROR_NR_11;
	}

	//----------------------ALL-----------------------
	if (category == ALL) {
		if (action == RELOAD) {
			_birthdayService.LoadData();
			_changeService.LoadData();
			_coinService.LoadData();
			_informationService.LoadData();
			_mapContentService.LoadData();
			_menuService.LoadData();
			_meterDataService.LoadData();
			_movieService.LoadData();
			_remoteService.LoadData();
			_shoppingListService.LoadData();
			_temperatureService.LoadData();
			return COMMAND_RELOAD_SUCCESS;
		}
	}

	//--------------------Birthday--------------------
	else if (category == BIRTHDAY) {
		return _birthdayService.PerformAction(data, _changeService, username);
	}
	//---------------------Camera---------------------
	else if (category == CAMERA) {
		return _cameraService.PerformAction(data);
	}
	//---------------------Changes--------------------
	else if (category == CHANGE) {
		return _changeService.PerformAction(data);
	}
	//----------------------Coins---------------------
	else if (category == COINS) {
		return _coinService.PerformAction(data, _changeService, username);
	}
	//------------------Informations------------------
	else if (category == INFORMATION) {
		return _informationService.PerformAction(data);
	}
	//-------------------MapContent-------------------
	else if (category == MAPCONTENT) {
		return _mapContentService.PerformAction(data, _changeService, username);
	}
	//----------------------Menu----------------------
	else if (category == MENU) {
		return _menuService.PerformAction(data, _changeService, username);
	}
	//--------------------MeterData-------------------
	else if (category == METERDATA) {
		return _meterDataService.PerformAction(data, _changeService, username);
	}
	//---------------------Movies---------------------
	else if (category == MOVIE) {
		return _movieService.PerformAction(data, username, _remoteService);
	}
	//---------------------Remote---------------------
	else if (category == REMOTE) {
		if (actionParameter == SCHEDULE) {
			if (action == ADD || action == DELETE || action == SET) {
				_updatedSchedules = true;
			}
		}
		return _remoteService.PerformAction(data, _changeService, username);
	}
	//------------------ShoppingList------------------
	if (category == SHOPPINGLIST) {
		return _shoppingListService.PerformAction(data, _changeService, username);
	}
	//---------------------System---------------------
	else if (category == SYSTEM) {
		return _systemService.PerformAction(data);
	}
	//--------------------Temperature-----------------
	else if (category == TEMPERATURE) {
		return _temperatureService.PerformAction(data);
	}
	//----------------------User----------------------
	else if (category == USER) {
		if (action == VALIDATE) {
			return USER_VALIDATE_SUCCESS;
		}
		else if (action == RESETFAILEDLOGIN) {
			return _authentificationService.ResetFailedLogin(username, password, actionParameter);
		}
	}

	return COMMAND_ERROR_NR_20;
}

void *server(void *arg) {
	syslog(LOG_INFO, "Server started!");

	int socketResult, connection, answer, clientLength;
	struct sockaddr_in clientAddress, serverAddress;
	char message[BUFLEN];

	int port = _remoteService.GetPort();

	socketResult = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketResult < 0) {
		syslog(LOG_CRIT, "Cant't open socket");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	connection = bind(socketResult, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	if (connection < 0) {
		syslog(LOG_CRIT, "Can't bind socket to port %d", port);
		exit(1);
	}

	syslog(LOG_INFO, "Server listen on port %u", port);

	while (1) {
		memset(message, 0x0, BUFLEN);
		clientLength = sizeof(clientAddress);

		answer = recvfrom(socketResult, message, BUFLEN, 0, (struct sockaddr *) &clientAddress, (socklen_t*)&clientLength);

		if (answer < 0) {
			syslog(LOG_ERR, "Can't receive data");
			continue;
		}
		else {
			syslog(LOG_INFO, "Received: %s", message);

			pthread_mutex_lock(&changesMutex);
			pthread_mutex_lock(&birthdaysMutex);
			pthread_mutex_lock(&moviesMutex);
			pthread_mutex_lock(&schedulesMutex);
			pthread_mutex_lock(&gpiosMutex);
			pthread_mutex_lock(&socketsMutex);
			pthread_mutex_lock(&switchesMutex);

			// Parse and execute request
			string response = executeCmd(message, CMD_SOURCE_EXTERNAL);

			if (_updatedSchedules) {
				_scheduleList = _remoteService.GetScheduleList();
				_updatedSchedules = false;
			}

			_remoteService.LoadData();
			_changeService.LoadData();

			pthread_mutex_unlock(&switchesMutex);
			pthread_mutex_unlock(&socketsMutex);
			pthread_mutex_unlock(&gpiosMutex);
			pthread_mutex_unlock(&schedulesMutex);
			pthread_mutex_unlock(&moviesMutex);
			pthread_mutex_unlock(&birthdaysMutex);
			pthread_mutex_unlock(&changesMutex);

			int sendResult = sendto(socketResult, response.c_str(), strlen(response.c_str()), 0, (struct sockaddr *) &clientAddress, clientLength);
			if (sendResult < 0) {
				syslog(LOG_ERR, "Can't send data");
			}
		}
	}

	close(socketResult);
	syslog(LOG_INFO, "Exiting *server");
	pthread_exit(NULL);
}

void *scheduler(void *arg) {
	syslog(LOG_INFO, "Scheduler started!");

	time_t now;
	struct tm now_info;
	int weekday;

	while (1) {
		now = time(0);
		localtime_r(&now, &now_info);

		time_t rawtime;
		tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		weekday = timeinfo->tm_wday;

		pthread_mutex_lock(&schedulesMutex);

		// Search for done, deleted and inactive Schedules
		vector<ScheduleTaskDto>::iterator it = _scheduleTaskList.begin();
		while (it != _scheduleTaskList.end()) {
			int found = 0;
			int done = 0;
			int active = 1;

			for (int s = 0; s < _scheduleList.size(); s++) {
				if (_scheduleList[s].GetName() == (*it).GetSchedule()) {
					found = 1;
					if (!_scheduleList[s].GetState()) {
						active = 0;
					}
				}
			}

			if ((*it).IsDone()) {
				double deltaTime = difftime((*it).GetTime(), now);
				if (deltaTime < -61) {
					done = 1;
				}
			}

			if (!found || !active || done) {
				syslog(LOG_INFO, "Removing Task '%s'", (*it).GetSchedule().c_str());
				it = _scheduleTaskList.erase(it);
			}
			else {
				++it;
			}
		}

		// Add Schedules to Tasklist
		for (int s = 0; s < _scheduleList.size(); s++) {
			int found = 0;

			for (int st = 0; st < _scheduleTaskList.size(); st++) {
				if (_scheduleList[s].GetName() == _scheduleTaskList[st].GetSchedule()) {
					found = 1;
				}
			}

			if (!found && _scheduleList[s].GetState()) {
				time_t newtime = time(0);
				struct tm tasktime;
				localtime_r(&newtime, &tasktime);
				tasktime.tm_hour = _scheduleList[s].GetHour();
				tasktime.tm_min = _scheduleList[s].GetMinute();
				tasktime.tm_sec = 0;

				newtime = mktime(&tasktime);
				ScheduleTaskDto task(_scheduleList[s].GetName(), newtime, _scheduleList[s].GetWeekday());
				_scheduleTaskList.push_back(task);
				syslog(LOG_INFO, "Adding Task '%s'", _scheduleList[s].GetName().c_str());
			}
		}

		// Execute Tasks
		for (int st = 0; st < _scheduleTaskList.size(); st++) {
			time_t tasktime = _scheduleTaskList[st].GetTime();
			struct tm tasktime_info;
			localtime_r(&tasktime, &tasktime_info);

			int scheduleWeekday = _scheduleTaskList[st].GetWeekday();
			string schedule = _scheduleTaskList[st].GetSchedule();

			if (_scheduleTaskList[st].IsDone() == 0
				&& scheduleWeekday == weekday
				&& tasktime_info.tm_hour == now_info.tm_hour
				&& tasktime_info.tm_min == now_info.tm_min) {

				syslog(LOG_INFO, "Executing Task '%s'", schedule.c_str());

				for (int s = 0; s < _scheduleList.size(); s++) {
					if (schedule == _scheduleList[s].GetName()) {
						if (_scheduleList[s].GetState()) {
							if (_scheduleList[s].GetSocket() != "") {
								stringstream socket_out;
								socket_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:SET:SOCKET:" << _scheduleList[s].GetSocket() << ":" << _scheduleList[s].GetOnoff();

								pthread_mutex_lock(&socketsMutex);

								string response = executeCmd(socket_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != SOCKET_SET_SUCCESS) {
									syslog(LOG_INFO, "Setting socket %s by scheduler failed!", _scheduleList[s].GetSocket().c_str());
								}

								pthread_mutex_unlock(&socketsMutex);
							}

							if (_scheduleList[s].GetGpio() != "") {
								stringstream gpio_out;
								gpio_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:SET:GPIO:" << _scheduleList[s].GetGpio() << ":" << _scheduleList[s].GetOnoff();

								pthread_mutex_lock(&gpiosMutex);

								string response = executeCmd(gpio_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != GPIO_SET_SUCCESS) {
									syslog(LOG_INFO, "Setting gpio %s by scheduler failed!", _scheduleList[s].GetGpio().c_str());
								}

								pthread_mutex_unlock(&gpiosMutex);
							}

							if (_scheduleList[s].GetSwitch() != "") {
								stringstream switch_out;
								switch_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:TOGGLE:SWITCH:" << _scheduleList[s].GetSwitch();

								pthread_mutex_lock(&switchesMutex);

								string response = executeCmd(switch_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != SWITCH_TOGGLE_SUCCESS) {
									syslog(LOG_INFO, "Toggling switch %s by scheduler failed!", _scheduleList[s].GetSwitch().c_str());
								}

								pthread_mutex_unlock(&switchesMutex);
							}

							if (_scheduleList[s].GetIsTimer() == 1) {
								stringstream schedule_delete_out;
								schedule_delete_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:DELETE:SCHEDULE:" << _scheduleList[s].GetName();

								string response = executeCmd(schedule_delete_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != SCHEDULE_DELETE_SUCCESS) {
									syslog(LOG_INFO, "Deleting schedule %s by scheduler failed!", _scheduleList[s].GetName().c_str());
								}
							}
						}
					}
				}

				_scheduleTaskList[st].SetDone(1);
			}
		}

		pthread_mutex_unlock(&schedulesMutex);
		sleep(SCHEDULE_CONTROL_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *scheduler");
	pthread_exit(NULL);
}

void *birthdayControl(void *arg) {
	syslog(LOG_INFO, "BirthdayControl started!");

	while (1) {
		pthread_mutex_lock(&birthdaysMutex);

		if (_birthdayService.GetBirthdayControlActive()) {
			_birthdayService.CheckBirthdayList();
		}

		pthread_mutex_unlock(&birthdaysMutex);

		sleep(BIRTHDAY_CHECK_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *birthdayControl");
	pthread_exit(NULL);
}

void *cameraStartControl(void *arg) {
	syslog(LOG_INFO, "CameraStartControl started!");

	while (1) {
		if (_cameraService.GetStartCamera() && !_cameraService.GetStopCamera()) {
			_cameraService.StartMotion();
		}

		sleep(1);
	}

	syslog(LOG_INFO, "Exiting *cameraStartControl");
	pthread_exit(NULL);
}

void *cameraStopControl(void *arg) {
	syslog(LOG_INFO, "CameraStopControl started!");

	while (1) {
		if (!_cameraService.GetStartCamera() && _cameraService.GetStopCamera()) {
			_cameraService.StopMotion();
		}

		sleep(1);
	}

	syslog(LOG_INFO, "Exiting *cameraStopControl");
	pthread_exit(NULL);
}

void *motionControl(void *arg) {
	syslog(LOG_INFO, "MotionControl started!");

	while (1) {
		if (_cameraService.GetMotionControlActive()) {
			_cameraService.Check();
		}

		sleep(MOTION_CONTROL_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *motionControl");
	pthread_exit(NULL);
}

void *temperatureControl(void *arg) {
	syslog(LOG_INFO, "TemperatureControl started!");

	while (1) {
		if (_temperatureService.GetTemperatureControlActive()) {
			_temperatureService.ControlTemperature();
		}

		sleep(TEMPERATURE_CONTROL_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *temperatureControl");
	pthread_exit(NULL);
}

void *reloader(void *arg) {
	syslog(LOG_INFO, "Reloader started!");

	while (1) {
		pthread_mutex_lock(&changesMutex);
		pthread_mutex_lock(&birthdaysMutex);
		pthread_mutex_lock(&moviesMutex);
		pthread_mutex_lock(&schedulesMutex);
		pthread_mutex_lock(&gpiosMutex);
		pthread_mutex_lock(&socketsMutex);
		pthread_mutex_lock(&switchesMutex);

		_birthdayService.LoadData();
		_changeService.LoadData();
		_coinService.LoadData();
		_informationService.LoadData();
		_mapContentService.LoadData();
		_menuService.LoadData();
		_meterDataService.LoadData();
		_movieService.LoadData();
		_remoteService.LoadData();
		_shoppingListService.LoadData();
		_temperatureService.LoadData();

		pthread_mutex_unlock(&changesMutex);
		pthread_mutex_unlock(&birthdaysMutex);
		pthread_mutex_unlock(&moviesMutex);
		pthread_mutex_unlock(&schedulesMutex);
		pthread_mutex_unlock(&gpiosMutex);
		pthread_mutex_unlock(&socketsMutex);
		pthread_mutex_unlock(&switchesMutex);

		sleep(RELOAD_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *reloader");
	pthread_exit(NULL);
}

int main(void) {
	openlog("lucahome", LOG_PID | LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "Starting LucaHome!");

	time_t now = time(0);
	syslog(LOG_INFO, "Current Scheduler-Time: %s", ctime(&now));

	_authentificationService.Initialize(_fileController, USER_FILE);
	_birthdayService.Initialize(_fileController, _mailController, BIRTHDAY_FILE);
	_changeService.Initialize(_fileController, CHANGE_FILE);
	_coinService.Initialize(_fileController, COIN_FILE);
	_informationService.Initialize(_fileController, INFORMATION_FILE);
	_mapContentService.Initialize(_fileController, MAP_CONTENT_FILE);
	_menuService.Initialize(_fileController, MENU_FILE, LISTED_MENU_FILE);
	_meterDataService.Initialize(_fileController, METERDATA_FILE);
	_movieService.Initialize(_fileController, _pathController);
	_remoteService.Initialize(_fileController, SETTINGS_FILE);
	_shoppingListService.Initialize(_fileController, SHOPPING_LIST_FILE);

	_cameraService.Initialize(_remoteService.GetCameraUrl(), _mailController, _pathController, _systemService);
	_temperatureService.Initialize(_fileController, _mailController, TEMPERATURE_SETTINGS_FILE, _remoteService.GetSensor(), _remoteService.GetArea(), _remoteService.GetTemperatureGraphUrl());

	std::ostringstream startMessage;
	startMessage << "Starting LucaHome at " << _remoteService.GetArea();
	_mailController.SendMail(startMessage.str());

	_updatedSchedules = false;
	_scheduleList = _remoteService.GetScheduleList();

	pthread_t scheduleThread, serverThread, temperatureThread, birthdayThread, cameraStartThread, cameraStopThread, motionThread, reloadThread;

	pthread_create(&serverThread, NULL, server, NULL);
	pthread_create(&scheduleThread, NULL, scheduler, NULL);
	pthread_create(&temperatureThread, NULL, temperatureControl, NULL);
	pthread_create(&birthdayThread, NULL, birthdayControl, NULL);
	pthread_create(&cameraStartThread, NULL, cameraStartControl, NULL);
	pthread_create(&cameraStopThread, NULL, cameraStopControl, NULL);
	pthread_create(&motionThread, NULL, motionControl, NULL);
	pthread_create(&reloadThread, NULL, reloader, NULL);

	pthread_join(serverThread, NULL);
	pthread_join(scheduleThread, NULL);
	pthread_join(temperatureThread, NULL);
	pthread_join(birthdayThread, NULL);
	pthread_join(cameraStartThread, NULL);
	pthread_join(cameraStopThread, NULL);
	pthread_join(motionThread, NULL);
	pthread_join(reloadThread, NULL);

	pthread_mutex_destroy(&switchesMutex);
	pthread_mutex_destroy(&socketsMutex);
	pthread_mutex_destroy(&gpiosMutex);
	pthread_mutex_destroy(&schedulesMutex);
	pthread_mutex_destroy(&moviesMutex);
	pthread_mutex_destroy(&birthdaysMutex);
	pthread_mutex_destroy(&changesMutex);

	closelog();
}
