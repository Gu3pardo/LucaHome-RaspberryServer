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
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#include "application/services.h"
#include "crosscutting/Constants.h"
#include "crosscutting/crypto.h"
#include "dataaccess/controller.h"
#include "domain/classes.h"

#define BUFFER_LENGTH 512
#define SERVER_PORT 6677
#define TASK_TYPE_SCHEDULE 0
#define TASK_TYPE_TIMER 1

using namespace std;

FileController _fileController = FileController();
MailController _mailController = MailController();
PathController _pathController = PathController();

ApplicationInformationService _applicationInformationService = ApplicationInformationService();
BirthdayService _birthdayService = BirthdayService();
ChangeService _changeService = ChangeService();
CoinService _coinService = CoinService();
MapContentService _mapContentService = MapContentService();
MealService _mealService = MealService();
MediaServerService _mediaServerService = MediaServerService();
MeterLogService _meterLogService = MeterLogService();
MoneyLogService _moneyLogService = MoneyLogService();
MovieService _movieService = MovieService();
PuckJsService _puckJsService = PuckJsService();
RadioStreamService _radioStreamService = RadioStreamService();
RoomService _roomService = RoomService();
RssFeedService _rssFeedService = RssFeedService();
SecurityService _securityService = SecurityService();
ShoppingItemService _shoppingItemService = ShoppingItemService();
SuggestedMealService _suggestedMealService = SuggestedMealService();
SuggestedShoppingItemService _suggestedShoppingItemService = SuggestedShoppingItemService();
TemperatureService _temperatureService = TemperatureService();
UserService _userService = UserService();
WirelessScheduleService _wirelessScheduleService = WirelessScheduleService();
WirelessSocketService _wirelessSocketService = WirelessSocketService();
WirelessSwitchService _wirelessSwitchService = WirelessSwitchService();
WirelessTimerService _wirelessTimerService = WirelessTimerService();
YoutubeVideoService _youtubeVideoService = YoutubeVideoService();

vector<WirelessTask> _wirelessTaskList;

pthread_mutex_t _lucaHomeMutex = PTHREAD_MUTEX_INITIALIZER;

string executeCommand(string encryptedCmd, int source)
{
	char key[]{};

	if (source != CMD_SOURCE_EXTERNAL && source != CMD_SOURCE_SCHEDULER) {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_INVALID_SOURCE);
	}

	if (encryptedCmd.length() < CMD_MIN_LENGTH) {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_SHORT_STATEMENT);
	}

	string cmd;
	if (source == CMD_SOURCE_SCHEDULER) {
		cmd = Decrypter::Decrypt(key, encryptedCmd);
	}
	else {
		cmd = encryptedCmd;
	}

	vector <string> data = Tools::Explode(":", cmd);
	if (data.size() < 1 || data[USER_NAME_INDEX] == "") {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_NO_USERNAME);
	}
	if (data.size() < 2 || data[PASSWORD_INDEX] == "") {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_NO_PASSWORD);
	}
	if (data.size() < 3 || data[CATEGORY_INDEX] == "") {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_NO_CATEGORY);
	}
	if (data.size() < 4 || data[ACTION_INDEX] == "") {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_NO_ACTION);
	}
	if (data.size() < 5 || data[ACTION_PARAMETER_INDEX] == "") {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_NO_PARAMETER);
	}

	string username = data[USER_NAME_INDEX];
	if (username == SCHEDULER && source != CMD_SOURCE_SCHEDULER) {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_SCHEDULER_EXTERNAL_NOT_ALLOWED);
	}

	//---------------Authentificate user--------------
	if (!_userService.AuthentificateUser(username, data[PASSWORD_INDEX])) {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_FAILED);
	}
	if (!_userService.AuthentificateUserAction(username, data[PASSWORD_INDEX], data[ACTION_INDEX])) {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_NO_RIGHTS);
	}

	string category = data[CATEGORY_INDEX];
	string commandAnswer = "";

	//-------------ApplicationInformation-------------
	if (category == APPLICATIONINFORMATION) {
		_changeService.UpdateChange("ApplicationInformation", username);
		commandAnswer = _applicationInformationService.PerformAction(data);
	}
	//--------------------Birthday--------------------
	else if (category == BIRTHDAY) {
		_changeService.UpdateChange("Birthday", username);
		commandAnswer = _birthdayService.PerformAction(data);
	}
	//---------------------Changes--------------------
	else if (category == CHANGE) {
		commandAnswer = _changeService.PerformAction(data);
	}
	//----------------------Coins---------------------
	else if (category == COIN) {
		_changeService.UpdateChange("Coin", username);
		commandAnswer = _coinService.PerformAction(data);
	}
	//-------------------MapContent-------------------
	else if (category == MAPCONTENT) {
		_changeService.UpdateChange("MapContent", username);
		commandAnswer = _mapContentService.PerformAction(data);
	}
	//----------------------Meal----------------------
	else if (category == MEAL) {
		_changeService.UpdateChange("Meal", username);
		commandAnswer = _mealService.PerformAction(data);
	}
	//-------------------MediaServer------------------
	else if (category == MEDIASERVER) {
		_changeService.UpdateChange("MediaServer", username);
		commandAnswer = _mediaServerService.PerformAction(data);
	}
	//-------------------MeterLogItem-----------------
	else if (category == METERLOGITEM) {
		_changeService.UpdateChange("MeterLogItem", username);
		commandAnswer = _meterLogService.PerformAction(data);
	}
	//-------------------MoneyLogItem-----------------
	else if (category == MONEYLOGITEM) {
		_changeService.UpdateChange("MoneyLogItem", username);
		commandAnswer = _moneyLogService.PerformAction(data);
	}
	//---------------------Movies---------------------
	else if (category == MOVIE) {
		_changeService.UpdateChange("Movie", username);
		commandAnswer = _movieService.PerformAction(data);
	}
	//---------------------PuckJs---------------------
	else if (category == PUCKJS) {
		_changeService.UpdateChange("PuckJs", username);
		commandAnswer = _puckJsService.PerformAction(data);
	}
	//-------------------RadioStream------------------
	else if (category == RADIOSTREAM) {
		_changeService.UpdateChange("RadioStream", username);
		commandAnswer = _radioStreamService.PerformAction(data);
	}
	//-----------------------Room---------------------
	else if (category == ROOM) {
		_changeService.UpdateChange("Room", username);
		commandAnswer = _roomService.PerformAction(data);
	}
	//---------------------RssFeed--------------------
	else if (category == RSSFEED) {
		_changeService.UpdateChange("RssFeed", username);
		commandAnswer = _rssFeedService.PerformAction(data);
	}
	//---------------------Security-------------------
	else if (category == SECURITY) {
		_changeService.UpdateChange("Security", username);
		commandAnswer = _securityService.PerformAction(data);
	}
	//------------------ShoppingItem------------------
	if (category == SHOPPINGITEM) {
		_changeService.UpdateChange("ShoppingItem", username);
		commandAnswer = _shoppingItemService.PerformAction(data);
	}
	//-----------------SuggestedMeal------------------
	else if (category == SUGGESTEDMEAL) {
		_changeService.UpdateChange("SuggestedMeal", username);
		commandAnswer = _suggestedMealService.PerformAction(data);
	}
	//-------------SuggestedShoppingItem--------------
	else if (category == SUGGESTEDSHOPPINGITEM) {
		_changeService.UpdateChange("SuggestedShoppingItem", username);
		commandAnswer = _suggestedShoppingItemService.PerformAction(data);
	}
	//--------------------Temperature-----------------
	else if (category == TEMPERATURE) {
		_changeService.UpdateChange("Temperature", username);
		commandAnswer = _temperatureService.PerformAction(data);
	}
	//----------------------User----------------------
	else if (category == USER) {
		_changeService.UpdateChange("User", username);
		commandAnswer = _userService.PerformAction(data);
	}
	//----------------WirelessSchedule----------------
	else if (category == WIRELESSSCHEDULE) {
		_changeService.UpdateChange("WirelessSchedule", username);
		commandAnswer = _wirelessScheduleService.PerformAction(data);
	}
	//-----------------WirelessSocket-----------------
	else if (category == WIRELESSSOCKET) {
		_changeService.UpdateChange("WirelessSocket", username);
		commandAnswer = _wirelessSocketService.PerformAction(data);
	}
	//-----------------WirelessSwitch-----------------
	else if (category == WIRELESSSWITCH) {
		_changeService.UpdateChange("WirelessSwitch", username);
		commandAnswer = _wirelessSwitchService.PerformAction(data);
	}
	//-----------------WirelessTimer------------------
	else if (category == WIRELESSTIMER) {
		_changeService.UpdateChange("WirelessTimer", username);
		commandAnswer = _wirelessTimerService.PerformAction(data);
	}
	//------------------YoutubeVideo------------------
	else if (category == YOUTUBEVIDEO) {
		_changeService.UpdateChange("YoutubeVideo", username);
		commandAnswer = _youtubeVideoService.PerformAction(data);
	}

	// Check if command was performed
	if (commandAnswer == "") {
		commandAnswer = COMMAND_ERROR_NO_ACTION_FOUND;
	}

	return Encrypter::Encrypt(source, key, commandAnswer);
}

void *server(void *arg) {
	syslog(LOG_INFO, "Server started!");

	int socketResult, connection, answer, clientLength;
	struct sockaddr_in clientAddress, serverAddress;
	char message[BUFFER_LENGTH];

	int port = SERVER_PORT;

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
		memset(message, 0x0, BUFFER_LENGTH);
		clientLength = sizeof(clientAddress);

		answer = recvfrom(socketResult, message, BUFFER_LENGTH, 0, (struct sockaddr *) &clientAddress, (socklen_t*)&clientLength);

		if (answer < 0) {
			syslog(LOG_ERR, "Can't receive data");
			continue;
		}
		else {
			syslog(LOG_INFO, "Received: %s", message);

			pthread_mutex_lock(&_lucaHomeMutex);
			string response = executeCommand(message, CMD_SOURCE_EXTERNAL);
			pthread_mutex_unlock(&_lucaHomeMutex);

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

		pthread_mutex_lock(&_lucaHomeMutex);

		vector<WirelessSchedule> wirelessScheduleList = _wirelessScheduleService.GetWirelessScheduleList();
		vector<WirelessTimer> wirelessTimerList = _wirelessTimerService.GetWirelessTimerList();

		// Search for done, deleted and inactive Schedules
		vector<WirelessTask>::iterator it = _wirelessTaskList.begin();
		while (it != _wirelessTaskList.end()) {
			int found = 0;
			int done = 0;
			int active = 1;

			if ((*it).GetParentType() == TASK_TYPE_SCHEDULE) {
				for (int scheduleIndex = 0; scheduleIndex < wirelessScheduleList.size(); scheduleIndex++) {
					if (wirelessScheduleList[scheduleIndex].GetUuid() == (*it).GetParentUuid()) {
						found = 1;
						if (!wirelessScheduleList[scheduleIndex].IsActive()) {
							active = 0;
						}
					}
				}
			}
			else if ((*it).GetParentType() == TASK_TYPE_TIMER) {
				for (int timerIndex = 0; timerIndex < wirelessTimerList.size(); timerIndex++) {
					if (wirelessTimerList[timerIndex].GetUuid() == (*it).GetParentUuid()) {
						found = 1;
					}
				}
			}
			else {
				active = 0;
			}

			if ((*it).IsDone()) {
				double deltaTime = difftime((*it).GetTime(), now);
				if (deltaTime < -61) {
					done = 1;
				}
			}

			if (!found || !active || done) {
				syslog(LOG_INFO, "Removing Task '%s'", (*it).GetParentUuid().c_str());
				it = _wirelessTaskList.erase(it);
			}
			else {
				++it;
			}
		}

		// Add Schedules to Tasklist
		for (int scheduleIndex = 0; scheduleIndex < wirelessScheduleList.size(); scheduleIndex++) {
			int found = 0;
			WirelessSchedule wirelessSchedule = wirelessScheduleList[scheduleIndex];

			for (int scheduleTaskIndex = 0; scheduleTaskIndex < _wirelessTaskList.size(); scheduleTaskIndex++) {
				if (wirelessSchedule.GetUuid() == _wirelessTaskList[scheduleTaskIndex].GetParentUuid()) {
					found = 1;
				}
			}

			if (!found && wirelessSchedule.IsActive()) {
				time_t newtime = time(0);
				struct tm tasktime;
				localtime_r(&newtime, &tasktime);
				tasktime.tm_hour = wirelessSchedule.GetHour();
				tasktime.tm_min = wirelessSchedule.GetMinute();
				tasktime.tm_sec = 0;
				newtime = mktime(&tasktime);

				WirelessTask wirelessTask(wirelessSchedule.GetUuid(), TASK_TYPE_SCHEDULE, newtime, wirelessSchedule.GetWeekday());
				_wirelessTaskList.push_back(wirelessTask);

				syslog(LOG_INFO, "Adding Schedule Task '%s'", wirelessSchedule.GetName().c_str());
			}
		}

		// Add Timer to Tasklist
		for (int timerIndex = 0; timerIndex < wirelessTimerList.size(); timerIndex++) {
			int found = 0;
			WirelessTimer wirelessTimer = wirelessTimerList[timerIndex];

			for (int scheduleTaskIndex = 0; scheduleTaskIndex < _wirelessTaskList.size(); scheduleTaskIndex++) {
				if (wirelessTimer.GetUuid() == _wirelessTaskList[scheduleTaskIndex].GetParentUuid()) {
					found = 1;
				}
			}

			if (!found) {
				time_t newtime = time(0);
				struct tm tasktime;
				localtime_r(&newtime, &tasktime);
				tasktime.tm_hour = wirelessTimer.GetHour();
				tasktime.tm_min = wirelessTimer.GetMinute();
				tasktime.tm_sec = 0;
				newtime = mktime(&tasktime);

				WirelessTask wirelessTask(wirelessTimer.GetUuid(), TASK_TYPE_TIMER, newtime, wirelessTimer.GetWeekday());
				_wirelessTaskList.push_back(wirelessTask);

				syslog(LOG_INFO, "Adding Timer Task '%s'", wirelessTimer.GetName().c_str());
			}
		}

		// Execute Tasks
		for (int taskIndex = 0; taskIndex < _wirelessTaskList.size(); taskIndex++) {
			time_t tasktime = _wirelessTaskList[taskIndex].GetTime();
			struct tm tasktime_info;
			localtime_r(&tasktime, &tasktime_info);

			if (_wirelessTaskList[taskIndex].IsDone() == 0
				&& _wirelessTaskList[taskIndex].GetWeekday() == weekday
				&& tasktime_info.tm_hour == now_info.tm_hour
				&& tasktime_info.tm_min == now_info.tm_min) {

				string uuid = _wirelessTaskList[taskIndex].GetParentUuid();
				syslog(LOG_INFO, "Executing Task '%s'", uuid.c_str());

				if (_wirelessTaskList[taskIndex].GetParentType() == TASK_TYPE_SCHEDULE) {
					for (int scheduleIndex = 0; scheduleIndex < wirelessScheduleList.size(); scheduleIndex++) {
						WirelessSchedule wirelessSchedule = wirelessScheduleList[scheduleIndex];
						if (uuid == wirelessSchedule.GetUuid()) {
							if (wirelessSchedule.IsActive()) {
								string wirelessSocketUuid = wirelessSchedule.GetWirelessSocketUuid();
								if (wirelessSocketUuid != "") {
									stringstream socket_out;
									socket_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:SET:SOCKET:" << wirelessSocketUuid << ":" << Tools::ConvertBoolToStr(wirelessSchedule.GetWirelessSocketAction());
									string response = executeCommand(socket_out.str(), CMD_SOURCE_SCHEDULER);
									if (response != WIRELESS_SOCKET_SET_SUCCESS) {
										syslog(LOG_INFO, "Setting wireless socket %s by scheduler failed!", wirelessSocketUuid.c_str());
									}
								}

								string wirelessSwitchUuid = wirelessSchedule.GetWirelessSwitchUuid();
								if (wirelessSwitchUuid != "") {
									stringstream switch_out;
									switch_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:TOGGLE:SWITCH:" << wirelessSwitchUuid;
									string response = executeCommand(switch_out.str(), CMD_SOURCE_SCHEDULER);
									if (response != WIRELESS_SWITCH_TOGGLE_SUCCESS) {
										syslog(LOG_INFO, "Toggling wireless switch %s by scheduler failed!", wirelessSwitchUuid.c_str());
									}
								}
							}
						}
					}
				}
				else if (_wirelessTaskList[taskIndex].GetParentType() == TASK_TYPE_TIMER) {
					for (int timerIndex = 0; timerIndex < wirelessTimerList.size(); timerIndex++) {
						WirelessTimer wirelessTimer = wirelessTimerList[timerIndex];
						if (uuid == wirelessTimer.GetUuid()) {
							string wirelessSocketUuid = wirelessTimer.GetWirelessSocketUuid();
							if (wirelessSocketUuid != "") {
								stringstream socket_out;
								socket_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:SET:SOCKET:" << wirelessSocketUuid << ":" << Tools::ConvertBoolToStr(wirelessTimer.GetWirelessSocketAction());
								string response = executeCommand(socket_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != WIRELESS_SOCKET_SET_SUCCESS) {
									syslog(LOG_INFO, "Setting wireless socket %s by scheduler failed!", wirelessSocketUuid.c_str());
								}
							}

							string wirelessSwitchUuid = wirelessTimer.GetWirelessSwitchUuid();
							if (wirelessSwitchUuid != "") {
								stringstream switch_out;
								switch_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:TOGGLE:SWITCH:" << wirelessSwitchUuid;
								string response = executeCommand(switch_out.str(), CMD_SOURCE_SCHEDULER);
								if (response != WIRELESS_SWITCH_TOGGLE_SUCCESS) {
									syslog(LOG_INFO, "Toggling wireless switch %s by scheduler failed!", wirelessSwitchUuid.c_str());
								}
							}

							stringstream timer_delete_out;
							timer_delete_out << SCHEDULER << ":" << SCHEDULER_PASSWORD << ":REMOTE:DELETE:TIMER:" << wirelessTimer.GetUuid();
							string response = executeCommand(timer_delete_out.str(), CMD_SOURCE_SCHEDULER);
							if (response != WIRELESS_TIMER_DELETE_SUCCESS) {
								syslog(LOG_INFO, "Deleting timer %s by scheduler failed!", wirelessTimer.GetUuid().c_str());
							}
						}
					}
				}

				_wirelessTaskList[taskIndex].SetDone(1);
			}
		}

		pthread_mutex_unlock(&_lucaHomeMutex);
		sleep(SCHEDULE_CONTROL_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *scheduler");
	pthread_exit(NULL);
}

void *birthdayControl(void *arg) {
	syslog(LOG_INFO, "BirthdayControl started!");
	while (1) {
		_birthdayService.CheckBirthdayList(_mailController);
		sleep(BIRTHDAY_CHECK_TIMEOUT);
	}
	syslog(LOG_INFO, "Exiting *birthdayControl");
	pthread_exit(NULL);
}

void *motionStartControl(void *arg) {
	syslog(LOG_INFO, "MotionStartControl started!");
	while (1) {
		if (_securityService.GetFlagMotionStart() && !_securityService.GetFlagMotionStop()) {
			_securityService.StartMotion();
		}
		sleep(1);
	}
	syslog(LOG_INFO, "Exiting *cameraStartControl");
	pthread_exit(NULL);
}

void *motionStopControl(void *arg) {
	syslog(LOG_INFO, "MotionStopControl started!");
	while (1) {
		if (!_securityService.GetFlagMotionStart() && _securityService.GetFlagMotionStop()) {
			_securityService.StopMotion();
		}
		sleep(1);
	}
	syslog(LOG_INFO, "Exiting *cameraStopControl");
	pthread_exit(NULL);
}

void *motionControl(void *arg) {
	syslog(LOG_INFO, "MotionControl started!");
	while (1) {
		_securityService.CheckMotionEvents();
		sleep(MOTION_CONTROL_TIMEOUT);
	}
	syslog(LOG_INFO, "Exiting *motionControl");
	pthread_exit(NULL);
}

void *temperatureControl(void *arg) {
	syslog(LOG_INFO, "TemperatureControl started!");
	while (1) {
		_temperatureService.CheckTemperature(_mailController);
		sleep(TEMPERATURE_CONTROL_TIMEOUT);
	}
	syslog(LOG_INFO, "Exiting *temperatureControl");
	pthread_exit(NULL);
}

int main(void) {
	openlog("lucahome", LOG_PID | LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "Starting LucaHome!");

	time_t now = time(0);
	syslog(LOG_INFO, "Current Scheduler-Time: %s", ctime(&now));

	std::ostringstream startMessage;
	startMessage << "Starting LucaHome";
	_mailController.SendMail(startMessage.str());

	_applicationInformationService.Initialize("ApplicationInformation.db");
	_birthdayService.Initialize("Birthday.db");
	_changeService.Initialize("Change.db");
	_coinService.Initialize("Coin.db");
	_mapContentService.Initialize("MapContent.db");
	_mealService.Initialize("Meal.db");
	_mediaServerService.Initialize("MediaServer.db");
	_meterLogService.Initialize("MeterLog.db");
	_moneyLogService.Initialize("MoneyLog.db");
	_movieService.Initialize(_fileController, _pathController);
	_puckJsService.Initialize("PuckJs.db");
	_radioStreamService.Initialize("RadioStream.db");
	_roomService.Initialize("Room.db");
	_rssFeedService.Initialize("RssFeed.db");
	_securityService.Initialize("http://192.168.178.25:8081");
	_shoppingItemService.Initialize("ShoppinItem.db");
	_suggestedMealService.Initialize("SuggestedMeal.db");
	_suggestedShoppingItemService.Initialize("SuggestedShoppinItem.db");
	_temperatureService.Initialize(Room("72B08CD8-54A2-4959-9BFE-26C4C9D876BF", "Living Room", 0), "28-000006f437d1", "http://192.168.178.25/cgi-bin/webgui.py", 15, 35);
	_userService.Initialize("User.db");
	_wirelessScheduleService.Initialize("WirelessSchedule.db");
	_wirelessSocketService.Initialize("WirelessSocket.db");
	_wirelessSwitchService.Initialize("WirelessSwitch.db");
	_wirelessTimerService.Initialize("WirelessTimer.db");
	_youtubeVideoService.Initialize("YoutubeVideo.db");

	pthread_t serverThread, scheduleThread, birthdayThread, motionStartThread, motionStopThread, motionThread, temperatureThread;

	pthread_create(&serverThread, NULL, server, NULL);
	pthread_create(&scheduleThread, NULL, scheduler, NULL);
	pthread_create(&birthdayThread, NULL, birthdayControl, NULL);
	pthread_create(&motionStartThread, NULL, motionStartControl, NULL);
	pthread_create(&motionStopThread, NULL, motionStopControl, NULL);
	pthread_create(&motionThread, NULL, motionControl, NULL);
	pthread_create(&temperatureThread, NULL, temperatureControl, NULL);

	pthread_join(serverThread, NULL);
	pthread_join(scheduleThread, NULL);
	pthread_join(birthdayThread, NULL);
	pthread_join(motionStartThread, NULL);
	pthread_join(motionStopThread, NULL);
	pthread_join(motionThread, NULL);
	pthread_join(temperatureThread, NULL);

	pthread_mutex_destroy(&_lucaHomeMutex);

	std::ostringstream stopMessage;
	stopMessage << "Stopping LucaHome";
	_mailController.SendMail(stopMessage.str());

	_applicationInformationService.Dispose();
	_birthdayService.Dispose();
	_changeService.Dispose();
	_coinService.Dispose();
	_mapContentService.Dispose();
	_mealService.Dispose();
	_mediaServerService.Dispose();
	_meterLogService.Dispose();
	_moneyLogService.Dispose();
	_puckJsService.Dispose();
	_radioStreamService.Dispose();
	_roomService.Dispose();
	_rssFeedService.Dispose();
	_securityService.Dispose();
	_shoppingItemService.Dispose();
	_suggestedMealService.Dispose();
	_suggestedShoppingItemService.Dispose();
	_userService.Dispose();
	_wirelessScheduleService.Dispose();
	_wirelessSocketService.Dispose();
	_wirelessSwitchService.Dispose();
	_wirelessTimerService.Dispose();
	_youtubeVideoService.Dispose();

	closelog();
}
