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
#include "crosscutting/controller.h"
#include "crosscutting/crypto.h"
#include "domain/classes.h"

using namespace std;

ApplicationInformationService _applicationInformationService = ApplicationInformationService();
ChangeService _changeService = ChangeService();
CoinService _coinService = CoinService();
ContactService _contactService = ContactService();
GpioService _gpioService = GpioService();
HandshakeService _handshakeService = HandshakeService();
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

string executeCommand(string encryptedCmd, int source, string clientAddress)
{
	string key = "";

	if (source == CMD_SOURCE_EXTERNAL) {
		if (!_handshakeService.HandshakePerformed(clientAddress)) {
			string secret = _handshakeService.CreateSecret(clientAddress);
			string str =
				string("{")
				+ string("\"ClientAddress\":\"") + clientAddress + string("\",")
				+ string("\"Secret\":\"") + secret + string("\"")
				+ string("}");
			return str;
		}

		key = _handshakeService.GetSecret(clientAddress);
		if (key.find(AUTHENTIFICATION_ERROR_NO_HANDSHAKE) != std::string::npos) {
			return AUTHENTIFICATION_ERROR_NO_HANDSHAKE;
		}
	}

	if (source != CMD_SOURCE_EXTERNAL && source != CMD_SOURCE_TASKER) {
		return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_INVALID_SOURCE);
	}

	if (encryptedCmd.length() < CMD_MIN_LENGTH) {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_SHORT_STATEMENT);
	}

	string cmd = Decrypter::Decrypt(source, key, encryptedCmd);
	if (cmd.find(DECRYPT_ERROR_KEY_NULL) != std::string::npos) {
		return DECRYPT_ERROR_KEY_NULL;
	}

	vector <string> data = Tools::Explode(COMMAND_SPLITTER, cmd);

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
	if (username == TASKER && source != CMD_SOURCE_TASKER) {
		return Encrypter::Encrypt(source, key, COMMAND_ERROR_SCHEDULER_EXTERNAL_NOT_ALLOWED);
	}

	//--------------Special validate user-------------
	string action = data[ACTION_INDEX];
	if (action == VALIDATE) {
		string commandAnswer = "";

		if (_userService.AuthentificateUser(username, data[PASSWORD_INDEX])) {
			commandAnswer = USER_VALIDATE_SUCCESS;
		}
		else {
			commandAnswer = USER_ERROR_VALIDATE;
		}

		string response = Encrypter::Encrypt(source, key, commandAnswer);
		_handshakeService.RemoveHandshake(clientAddress);
		return response;
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
	//---------------------Changes--------------------
	else if (category == CHANGE) {
		commandAnswer = _changeService.PerformAction(data);
	}
	//----------------------Coins---------------------
	else if (category == COIN) {
		_changeService.UpdateChange("Coin", username);
		commandAnswer = _coinService.PerformAction(data);
	}
	//--------------------Contact--------------------
	else if (category == CONTACT) {
		_changeService.UpdateChange("Contact", username);
		commandAnswer = _contactService.PerformAction(data);
	}
	//--------------------Gpio--------------------
	else if (category == GPIO) {
		_changeService.UpdateChange("Gpio", username);
		commandAnswer = _gpioService.PerformAction(data);
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
		if (!_userService.IsUserAdmin(username)) {
			return Encrypter::Encrypt(source, key, AUTHENTIFICATION_ERROR_FAILED);
		}
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

	string response = Encrypter::Encrypt(source, key, commandAnswer);
	_handshakeService.RemoveHandshake(clientAddress);
	return response;
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

			char clientAddressChar[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(clientAddress.sin_addr), clientAddressChar, INET_ADDRSTRLEN);

			string clientAddressString(clientAddressChar);

			pthread_mutex_lock(&_lucaHomeMutex);
			string response = executeCommand(message, CMD_SOURCE_EXTERNAL, clientAddressString);
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

void *tasker(void *arg) {
	syslog(LOG_INFO, "Tasker started!");

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
								string gpioUuid = wirelessSchedule.GetGpioUuid();
								if (gpioUuid != "") {
									stringstream socket_out;
									socket_out << TASKER << ":" << TASKER_PASSWORD << ":" << GPIO << ":" << SET << ":" << gpioUuid << ":" << Tools::ConvertBoolToStr(wirelessSchedule.GetGpioAction());
									string response = executeCommand(socket_out.str(), CMD_SOURCE_TASKER, "");
									if (response != GPIO_SET_SUCCESS) {
										syslog(LOG_INFO, "Setting gpio %s by tasker failed!", gpioUuid.c_str());
									}
								}

								string wirelessSocketUuid = wirelessSchedule.GetWirelessSocketUuid();
								if (wirelessSocketUuid != "") {
									stringstream wireless_socket_out;
									wireless_socket_out << TASKER << ":" << TASKER_PASSWORD << ":" << WIRELESSSOCKET << ":" << SET << ":" << wirelessSocketUuid << ":" << Tools::ConvertBoolToStr(wirelessSchedule.GetWirelessSocketAction());
									string response = executeCommand(wireless_socket_out.str(), CMD_SOURCE_TASKER, "");
									if (response != WIRELESS_SOCKET_SET_SUCCESS) {
										syslog(LOG_INFO, "Setting wireless socket %s by tasker failed!", wirelessSocketUuid.c_str());
									}
								}

								string wirelessSwitchUuid = wirelessSchedule.GetWirelessSwitchUuid();
								if (wirelessSwitchUuid != "") {
									stringstream wireless_switch_out;
									wireless_switch_out << TASKER << ":" << TASKER_PASSWORD << ":" << WIRELESSSWITCH << ":" << TOGGLE << ":" << wirelessSwitchUuid;
									string response = executeCommand(wireless_switch_out.str(), CMD_SOURCE_TASKER, "");
									if (response != WIRELESS_SWITCH_TOGGLE_SUCCESS) {
										syslog(LOG_INFO, "Toggling wireless switch %s by tasker failed!", wirelessSwitchUuid.c_str());
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
							string gpioUuid = wirelessTimer.GetGpioUuid();
							if (gpioUuid != "") {
								stringstream gpio_out;
								gpio_out << TASKER << ":" << TASKER_PASSWORD << ":" << GPIO << ":" << SET << ":" << gpioUuid << ":" << Tools::ConvertBoolToStr(wirelessTimer.GetGpioAction());
								string response = executeCommand(gpio_out.str(), CMD_SOURCE_TASKER, "");
								if (response != GPIO_SET_SUCCESS) {
									syslog(LOG_INFO, "Setting gpio %s by tasker failed!", gpioUuid.c_str());
								}
							}

							string wirelessSocketUuid = wirelessTimer.GetWirelessSocketUuid();
							if (wirelessSocketUuid != "") {
								stringstream wireless_socket_out;
								wireless_socket_out << TASKER << ":" << TASKER_PASSWORD << ":" << WIRELESSSOCKET << ":" << SET << ":" << wirelessSocketUuid << ":" << Tools::ConvertBoolToStr(wirelessTimer.GetWirelessSocketAction());
								string response = executeCommand(wireless_socket_out.str(), CMD_SOURCE_TASKER, "");
								if (response != WIRELESS_SOCKET_SET_SUCCESS) {
									syslog(LOG_INFO, "Setting wireless socket %s by tasker failed!", wirelessSocketUuid.c_str());
								}
							}

							string wirelessSwitchUuid = wirelessTimer.GetWirelessSwitchUuid();
							if (wirelessSwitchUuid != "") {
								stringstream wireless_switch_out;
								wireless_switch_out << TASKER << ":" << TASKER_PASSWORD << ":" << WIRELESSSWITCH << ":" << TOGGLE << ":" << wirelessSwitchUuid;
								string response = executeCommand(wireless_switch_out.str(), CMD_SOURCE_TASKER, "");
								if (response != WIRELESS_SWITCH_TOGGLE_SUCCESS) {
									syslog(LOG_INFO, "Toggling wireless switch %s by tasker failed!", wirelessSwitchUuid.c_str());
								}
							}

							stringstream wireless_timer_delete_out;
							wireless_timer_delete_out << TASKER << ":" << TASKER_PASSWORD << ":" << WIRELESSTIMER << ":" << DELETE << ":" << wirelessTimer.GetUuid();
							string response = executeCommand(wireless_timer_delete_out.str(), CMD_SOURCE_TASKER, "");
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
		sleep(TASK_CONTROL_TIMEOUT);
	}

	syslog(LOG_INFO, "Exiting *tasker");
	pthread_exit(NULL);
}

void *birthdayControl(void *arg) {
	syslog(LOG_INFO, "BirthdayControl started!");
	while (1) {
		pthread_mutex_lock(&_lucaHomeMutex);
		_contactService.CheckContactBirthdayList();
		pthread_mutex_unlock(&_lucaHomeMutex);
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

void *shoppingItemControl(void *arg) {
	syslog(LOG_INFO, "ShoppingItemControl started!");
	while (1) {
		pthread_mutex_lock(&_lucaHomeMutex);
		_shoppingItemService.CheckShoppingListToRemind();
		pthread_mutex_unlock(&_lucaHomeMutex);
		sleep(SHOPPING_ITEM_CHECK_TIMEOUT);
	}
	syslog(LOG_INFO, "Exiting *shoppingItemControl");
	pthread_exit(NULL);
}

void *temperatureControl(void *arg) {
	syslog(LOG_INFO, "TemperatureControl started!");
	while (1) {
		_temperatureService.CheckTemperature();
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
	MailController::SendMail(RECEIVER_MAIL, 0, startMessage.str());

	_applicationInformationService.Initialize("/etc/default/lucahome/databases/ApplicationInformation.db");
	_changeService.Initialize("/etc/default/lucahome/databases/Change.db");
	_coinService.Initialize("/etc/default/lucahome/databases/Coin.db");
	_contactService.Initialize("/etc/default/lucahome/databases/Contact.db");
	_gpioService.Initialize("/etc/default/lucahome/databases/Gpio.db");
	_mapContentService.Initialize("/etc/default/lucahome/databases/MapContent.db");
	_mealService.Initialize("/etc/default/lucahome/databases/Meal.db");
	_mediaServerService.Initialize("/etc/default/lucahome/databases/MediaServer.db");
	_meterLogService.Initialize("/etc/default/lucahome/databases/MeterLog.db");
	_moneyLogService.Initialize("/etc/default/lucahome/databases/MoneyLog.db");
	_movieService.Initialize();
	_puckJsService.Initialize("/etc/default/lucahome/databases/PuckJs.db");
	_radioStreamService.Initialize("/etc/default/lucahome/databases/RadioStream.db");
	_roomService.Initialize("/etc/default/lucahome/databases/Room.db");
	_rssFeedService.Initialize("/etc/default/lucahome/databases/RssFeed.db");
	_securityService.Initialize("http://192.168.178.25:8081");
	_shoppingItemService.Initialize("/etc/default/lucahome/databases/ShoppingItem.db");
	_suggestedMealService.Initialize("/etc/default/lucahome/databases/SuggestedMeal.db");
	_suggestedShoppingItemService.Initialize("/etc/default/lucahome/databases/SuggestedShoppinItem.db");
	_temperatureService.Initialize(Room("72B08CD8-54A2-4959-9BFE-26C4C9D876BF", "Living Room", 0), "28-000006f437d1", "http://192.168.178.25/cgi-bin/webgui.py", 15, 35);
	_userService.Initialize("/etc/default/lucahome/databases/User.db");
	_wirelessScheduleService.Initialize("/etc/default/lucahome/databases/WirelessSchedule.db");
	_wirelessSocketService.Initialize("/etc/default/lucahome/databases/WirelessSocket.db");
	_wirelessSwitchService.Initialize("/etc/default/lucahome/databases/WirelessSwitch.db");
	_wirelessTimerService.Initialize("/etc/default/lucahome/databases/WirelessTimer.db");
	_youtubeVideoService.Initialize("/etc/default/lucahome/databases/YoutubeVideo.db");

	pthread_t serverThread, taskThread, birthdayThread, motionStartThread, motionStopThread, motionThread, shoppingItemThread, temperatureThread;

	pthread_create(&serverThread, NULL, server, NULL);
	pthread_create(&taskThread, NULL, tasker, NULL);
	pthread_create(&birthdayThread, NULL, birthdayControl, NULL);
	pthread_create(&motionStartThread, NULL, motionStartControl, NULL);
	pthread_create(&motionStopThread, NULL, motionStopControl, NULL);
	pthread_create(&motionThread, NULL, motionControl, NULL);
	pthread_create(&shoppingItemThread, NULL, shoppingItemControl, NULL);
	pthread_create(&temperatureThread, NULL, temperatureControl, NULL);

	pthread_join(serverThread, NULL);
	pthread_join(taskThread, NULL);
	pthread_join(birthdayThread, NULL);
	pthread_join(motionStartThread, NULL);
	pthread_join(motionStopThread, NULL);
	pthread_join(motionThread, NULL);
	pthread_join(shoppingItemThread, NULL);
	pthread_join(temperatureThread, NULL);

	pthread_mutex_destroy(&_lucaHomeMutex);

	std::ostringstream stopMessage;
	stopMessage << "Stopping LucaHome";
	MailController::SendMail(RECEIVER_MAIL, 0, stopMessage.str());

	_applicationInformationService.Dispose();
	_changeService.Dispose();
	_coinService.Dispose();
	_contactService.Dispose();
	_gpioService.Dispose();
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
