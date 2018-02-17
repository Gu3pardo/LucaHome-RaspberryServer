#include "CommandHandler.h"

/*===============PUBLIC==============*/

CommandHandler * CommandHandler::getInstance()
{
	return instance;
}

CommandHandler::CommandHandler() {}

string CommandHandler::ExecuteCommand(string cmd, int source)
{
	if (cmd.length() < CMD_MIN_LENGTH) {
		return COMMAND_ERROR_SHORT_STATEMENT;
	}
	if (source != CMD_SOURCE_EXTERNAL && source != CMD_SOURCE_SCHEDULER) {
		return AUTHENTIFICATION_ERROR_INVALID_SOURCE;
	}

	vector < string > data = Tools::Explode(":", cmd);
	if (data.size() < 1) {
		return AUTHENTIFICATION_ERROR_NO_USERNAME;
	}
	if (data.size() < 2) {
		return AUTHENTIFICATION_ERROR_NO_PASSWORD;
	}
	if (data.size() < 3) {
		return COMMAND_ERROR_NO_CATEGORY;
	}
	if (data.size() < 4) {
		return COMMAND_ERROR_NO_ACTION;
	}
	if (data.size() < 5) {
		return COMMAND_ERROR_NO_PARAMETER;
	}

	string username = data[USER_NAME_INDEX];
	string password = data[PASSWORD_INDEX];
	string category = data[CATEGORY_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (username == "") {
		return AUTHENTIFICATION_ERROR_NO_USERNAME;
	}
	if (password == "") {
		return AUTHENTIFICATION_ERROR_NO_PASSWORD;
	}
	if (category == "") {
		return COMMAND_ERROR_NO_CATEGORY;
	}
	if (action == "") {
		return COMMAND_ERROR_NO_ACTION;
	}
	if (actionParameter == "") {
		return COMMAND_ERROR_NO_PARAMETER;
	}

	if (username == SCHEDULER && source != CMD_SOURCE_SCHEDULER) {
		return COMMAND_ERROR_SCHEDULER_EXTERNAL_NOT_ALLOWED;
	}

	// TODO activate if logger is wished
	//_logger.addLog("DEBUG", data, username);

	//---------------Authentificate user--------------
	if (!_userService.AuthentificateUser(username, password)) {
		return AUTHENTIFICATION_ERROR_FAILED;
	}
	if (!_userService.AuthentificateUserAction(username, password, action)) {
		return AUTHENTIFICATION_ERROR_NO_RIGHTS;
	}

	//-------------ApplicationInformation-------------
	if (category == APPLICATIONINFORMATION) {
		return _applicationInformationService.PerformAction(data);
	}
	//--------------------Birthday--------------------
	else if (category == BIRTHDAY) {
		return _birthdayService.PerformAction(data);
	}
	//---------------------Changes--------------------
	else if (category == CHANGE) {
		return _changeService.PerformAction(data);
	}
	//----------------------Coins---------------------
	else if (category == COIN) {
		return _coinService.PerformAction(data);
	}
	//-------------------MapContent-------------------
	else if (category == MAPCONTENT) {
		return _mapContentService.PerformAction(data);
	}
	//----------------------Meal----------------------
	else if (category == MEAL) {
		return _mealService.PerformAction(data);
	}
	//-------------------MediaServer------------------
	else if (category == MEDIASERVER) {
		return _mediaServerService.PerformAction(data);
	}
	//-------------------MeterLogItem-----------------
	else if (category == METERLOGITEM) {
		return _meterLogService.PerformAction(data);
	}
	//-------------------MoneyLogItem-----------------
	else if (category == MONEYLOGITEM) {
		return _moneyLogService.PerformAction(data);
	}
	//---------------------Movies---------------------
	else if (category == MOVIE) {
		return _movieService.PerformAction(data);
	}
	//---------------------PuckJs---------------------
	else if (category == PUCKJS) {
		return _puckJsService.PerformAction(data);
	}
	//-------------------RadioStream------------------
	else if (category == RADIOSTREAM) {
		return _radioStreamService.PerformAction(data);
	}
	//-----------------------Room---------------------
	else if (category == ROOM) {
		return _roomService.PerformAction(data);
	}
	//---------------------RssFeed--------------------
	else if (category == RSSFEED) {
		return _rssFeedService.PerformAction(data);
	}
	//---------------------Security-------------------
	else if (category == SECURITY) {
		return _securityService.PerformAction(data);
	}
	//------------------ShoppingItem------------------
	if (category == SHOPPINGITEM) {
		return _shoppingItemService.PerformAction(data);
	}
	//-----------------SuggestedMeal------------------
	else if (category == SUGGESTEDMEAL) {
		return _suggestedMealService.PerformAction(data);
	}
	//-------------SuggestedShoppingItem--------------
	if (category == SUGGESTEDSHOPPINGITEM) {
		return _suggestedShoppingItemService.PerformAction(data);
	}
	//--------------------Temperature-----------------
	else if (category == TEMPERATURE) {
		return _temperatureService.PerformAction(data);
	}
	//----------------------User----------------------
	else if (category == USER) {
		return _userService.PerformAction(data);
	}
	//----------------WirelessSchedule----------------
	else if (category == WIRELESSSCHEDULE) {
		return _wirelessScheduleService.PerformAction(data);
	}
	//-----------------WirelessSocket-----------------
	else if (category == WIRELESSSOCKET) {
		return _wirelessSocketService.PerformAction(data);
	}
	//-----------------WirelessSwitch-----------------
	else if (category == WIRELESSSWITCH) {
		return _wirelessSwitchService.PerformAction(data);
	}
	//------------------YoutubeVideo------------------
	else if (category == YOUTUBEVIDEO) {
		return _youtubeVideoService.PerformAction(data);
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}
