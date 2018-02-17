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

#include "../../crosscutting/Constants.h"
#include "../services.h"

using namespace std;

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

class CommandHandler
{
private:
	static CommandHandler* instance;
	CommandHandler();

	ApplicationInformationService _applicationInformationService;
	BirthdayService _birthdayService;
	ChangeService _changeService;
	CoinService _coinService;
	MapContentService _mapContentService;
	MealService _mealService;
	MediaServerService _mediaServerService;
	MeterLogService _meterLogService;
	MoneyLogService _moneyLogService;
	MovieService _movieService;
	PuckJsService _puckJsService;
	RadioStreamService _radioStreamService;
	RoomService _roomService;
	RssFeedService _rssFeedService;
	SecrityService _securityService;
	ShoppingItemService _shoppingItemService;
	SuggestedMealService _suggestedMealService;
	SuggestedShoppingItemService _suggestedShoppingItemService;
	TemperatureService _temperatureService;
	UserService _userService;
	WirelessScheduleService _wirelessScheduleService;
	WirelessSocketService _wirelessSocketService;
	WirelessSwitchService _wirelessSwitchService;
	YoutubeVideoService _youtubeVideoService;

public:
	static CommandHandler* getInstance();

	CommandHandler(CommandHandler const&) = delete;
	void operator=(CommandHandler const&) = delete;

	string ExecuteCommand(string, int);
};

#endif
