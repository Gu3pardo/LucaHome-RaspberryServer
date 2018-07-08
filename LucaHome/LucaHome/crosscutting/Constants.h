/**********************************************************************************************/
/*************************************** USER DEFINITIONS *************************************/
/**********************************************************************************************/

#define MAX_INVALID_LOGIN_COUNT								5
#define DEFAULT_PASSWORD									"0000"
#define NO_PASSWORD											"NO_PASSWORD"
#define DUMMY												"DUMMY"
#define TASKER												"Tasker"
#define TASKER_PASSWORD										"435435"

#define RECEIVER_MAIL										"TODO_PUT_HERE_YOUR_RECEIVER_MAIL"

/**********************************************************************************************/
/************************************* SUCCESS DEFINITIONS ************************************/
/**********************************************************************************************/

#define AUTHENTIFICATION_RESET_FAILED_LOGIN_COUNT_SUCCESS	"{\"Category\":\"Authentification\",\"Action\":\"ResetFailedLoginCount\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define APPLICATION_INFORMATION_ADD_SUCCESS					"{\"Category\":\"ApplicationInformation\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define APPLICATION_INFORMATION_UPDATE_SUCCESS				"{\"Category\":\"ApplicationInformation\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define APPLICATION_INFORMATION_DELETE_SUCCESS				"{\"Category\":\"ApplicationInformation\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define CHANGE_ADD_SUCCESS									"{\"Category\":\"Change\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define CHANGE_UPDATE_SUCCESS								"{\"Category\":\"Change\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define CHANGE_DELETE_SUCCESS								"{\"Category\":\"Change\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define COIN_ADD_SUCCESS									"{\"Category\":\"Coin\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define COIN_UPDATE_SUCCESS									"{\"Category\":\"Coin\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define COIN_DELETE_SUCCESS									"{\"Category\":\"Coin\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define CONTACT_ADD_SUCCESS									"{\"Category\":\"Contact\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define CONTACT_UPDATE_SUCCESS								"{\"Category\":\"Contact\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define CONTACT_DELETE_SUCCESS								"{\"Category\":\"Contact\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define CONTACT_MAIL_SUCCESS								"{\"Category\":\"Contact\",\"Action\":\"Mail\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define COMMAND_RELOAD_SUCCESS								"{\"Category\":\"Common\",\"Action\":\"Reload\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define GPIO_ADD_SUCCESS									"{\"Category\":\"Gpio\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define GPIO_UPDATE_SUCCESS									"{\"Category\":\"Gpio\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define GPIO_DELETE_SUCCESS									"{\"Category\":\"Gpio\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define GPIO_SET_SUCCESS									"{\"Category\":\"Gpio\",\"Action\":\"Set\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define MAP_CONTENT_ADD_SUCCESS								"{\"Category\":\"MapContent\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MAP_CONTENT_UPDATE_SUCCESS							"{\"Category\":\"MapContent\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MAP_CONTENT_DELETE_SUCCESS							"{\"Category\":\"MapContent\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define MEAL_ADD_SUCCESS									"{\"Category\":\"Meal\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MEAL_UPDATE_SUCCESS									"{\"Category\":\"Meal\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MEAL_DELETE_SUCCESS									"{\"Category\":\"Meal\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define MEDIA_SERVER_ADD_SUCCESS							"{\"Category\":\"MediaServer\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MEDIA_SERVER_UPDATE_SUCCESS							"{\"Category\":\"MediaServer\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MEDIA_SERVER_DELETE_SUCCESS							"{\"Category\":\"MediaServer\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define METER_LOG_ITEM_ADD_SUCCESS							"{\"Category\":\"MeterLogItem\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define METER_LOG_ITEM_UPDATE_SUCCESS						"{\"Category\":\"MeterLogItem\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define METER_LOG_ITEM_DELETE_SUCCESS						"{\"Category\":\"MeterLogItem\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define MONEY_LOG_ITEM_ADD_SUCCESS							"{\"Category\":\"MoneyLogItem\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MONEY_LOG_ITEM_UPDATE_SUCCESS						"{\"Category\":\"MoneyLogItem\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MONEY_LOG_ITEM_DELETE_SUCCESS						"{\"Category\":\"MoneyLogItem\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define MOVIE_UPDATE_SUCCESS								"{\"Category\":\"Movie\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define MOVIE_LOAD_SUCCESS									"{\"Category\":\"Movie\",\"Action\":\"Load\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define PUCK_JS_ADD_SUCCESS									"{\"Category\":\"PuckJs\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define PUCK_JS_UPDATE_SUCCESS								"{\"Category\":\"PuckJs\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define PUCK_JS_DELETE_SUCCESS								"{\"Category\":\"PuckJs\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define RADIO_STREAM_ADD_SUCCESS							"{\"Category\":\"RadioStream\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define RADIO_STREAM_UPDATE_SUCCESS							"{\"Category\":\"RadioStream\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define RADIO_STREAM_DELETE_SUCCESS							"{\"Category\":\"RadioStream\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define ROOM_ADD_SUCCESS									"{\"Category\":\"Room\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define ROOM_UPDATE_SUCCESS									"{\"Category\":\"Room\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define ROOM_DELETE_SUCCESS									"{\"Category\":\"Room\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define RSS_FEED_ADD_SUCCESS								"{\"Category\":\"RssFeed\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define RSS_FEED_UPDATE_SUCCESS								"{\"Category\":\"RssFeed\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define RSS_FEED_DELETE_SUCCESS								"{\"Category\":\"RssFeed\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define SECURITY_START_MOTION_SUCCESS						"{\"Category\":\"Securitz\",\"Action\":\"StartMotion\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SECURITY_STOP_MOTION_SUCCESS						"{\"Category\":\"Securitz\",\"Action\":\"StopMotion\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define SHOPPING_ITEM_ADD_SUCCESS							"{\"Category\":\"ShoppingItem\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SHOPPING_ITEM_UPDATE_SUCCESS						"{\"Category\":\"ShoppingItem\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SHOPPING_ITEM_DELETE_SUCCESS						"{\"Category\":\"ShoppingItem\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define SUGGESTED_MEAL_ADD_SUCCESS							"{\"Category\":\"SuggestedMeal\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SUGGESTED_MEAL_UPDATE_SUCCESS						"{\"Category\":\"SuggestedMeal\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SUGGESTED_MEAL_DELETE_SUCCESS						"{\"Category\":\"SuggestedMeal\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define SUGGESTED_SHOPPING_ITEM_ADD_SUCCESS					"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SUGGESTED_SHOPPING_ITEM_UPDATE_SUCCESS				"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define SUGGESTED_SHOPPING_ITEM_DELETE_SUCCESS				"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define USER_VALIDATE_SUCCESS								"{\"Category\":\"User\",\"Action\":\"Validate\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define USER_ADD_SUCCESS									"{\"Category\":\"User\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define USER_UPDATE_SUCCESS									"{\"Category\":\"User\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define USER_DELETE_SUCCESS									"{\"Category\":\"User\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define WIRELESS_SCHEDULE_ADD_SUCCESS						"{\"Category\":\"WirelessSchedule\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SCHEDULE_UPDATE_SUCCESS					"{\"Category\":\"WirelessSchedule\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SCHEDULE_DELETE_SUCCESS					"{\"Category\":\"WirelessSchedule\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SCHEDULE_SET_SUCCESS						"{\"Category\":\"WirelessSchedule\",\"Action\":\"Set\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define WIRELESS_SOCKET_ADD_SUCCESS							"{\"Category\":\"WirelessSocket\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SOCKET_UPDATE_SUCCESS						"{\"Category\":\"WirelessSocket\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SOCKET_DELETE_SUCCESS						"{\"Category\":\"WirelessSocket\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SOCKET_SET_SUCCESS							"{\"Category\":\"WirelessSocket\",\"Action\":\"Set\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define WIRELESS_SWITCH_ADD_SUCCESS							"{\"Category\":\"WirelessSwitch\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SWITCH_UPDATE_SUCCESS						"{\"Category\":\"WirelessSwitch\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SWITCH_DELETE_SUCCESS						"{\"Category\":\"WirelessSwitch\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_SWITCH_TOGGLE_SUCCESS						"{\"Category\":\"WirelessSwitch\",\"Action\":\"Toggle\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define WIRELESS_TIMER_ADD_SUCCESS							"{\"Category\":\"WirelessTimer\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_TIMER_UPDATE_SUCCESS						"{\"Category\":\"WirelessTimer\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_TIMER_DELETE_SUCCESS						"{\"Category\":\"WirelessTimer\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define WIRELESS_TIMER_SET_SUCCESS							"{\"Category\":\"WirelessTimer\",\"Action\":\"Set\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

#define YOUTUBE_VIDEO_ADD_SUCCESS							"{\"Category\":\"YoutubeVideo\",\"Action\":\"Add\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define YOUTUBE_VIDEO_UPDATE_SUCCESS						"{\"Category\":\"YoutubeVideo\",\"Action\":\"Update\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"
#define YOUTUBE_VIDEO_DELETE_SUCCESS						"{\"Category\":\"YoutubeVideo\",\"Action\":\"Delete\",\"Error\":0,\"Success\":true,\"Data\":\"\"}"

/**********************************************************************************************/
/************************************** ERROR DEFINITIONS *************************************/
/**********************************************************************************************/

#define AUTHENTIFICATION_ERROR_FAILED						"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":10,\"Success\":false,\"Data\":\"Authentification failed!\"}"
#define AUTHENTIFICATION_ERROR_NO_RIGHTS					"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":11,\"Success\":false,\"Data\":\"UserAction cannot be performed! No rights!\"}"
#define AUTHENTIFICATION_ERROR_NO_PASSWORD					"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":12,\"Success\":false,\"Data\":\"No password!\"}"
#define AUTHENTIFICATION_ERROR_NO_USERNAME					"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":13,\"Success\":false,\"Data\":\"No username!\"}"
#define AUTHENTIFICATION_ERROR_INVALID_SOURCE				"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":14,\"Success\":false,\"Data\":\"Invalid source!\"}"
#define AUTHENTIFICATION_ERROR_RESET_FAILED					"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":16,\"Success\":false,\"Data\":\"Could not reset invalid login count!\"}"
#define AUTHENTIFICATION_ERROR_NO_ADMIN						"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":17,\"Success\":false,\"Data\":\"Permitted! User is no admin!\"}"
#define AUTHENTIFICATION_ERROR_NO_HANDSHAKE					"{\"Category\":\"Authentification\",\"Action\":\"\",\"Error\":18,\"Success\":false,\"Data\":\"No handshake performed!\"}"

#define COMMAND_ERROR_NO_ACTION_FOUND						"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":20,\"Success\":false,\"Data\":\"Action not found!\"}"
#define COMMAND_ERROR_NO_PARAMETER_FOUND					"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":21,\"Success\":false,\"Data\":\"Parameter not found!\"}"
#define COMMAND_ERROR_SHORT_STATEMENT						"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":22,\"Success\":false,\"Data\":\"Statement too short!\"}"
#define COMMAND_ERROR_NO_ACTION								"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":23,\"Success\":false,\"Data\":\"No action!\"}"
#define COMMAND_ERROR_NO_CATEGORY							"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":24,\"Success\":false,\"Data\":\"No category!\"}"
#define COMMAND_ERROR_NO_PARAMETER							"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":25,\"Success\":false,\"Data\":\"Not action parameter!\"}"
#define COMMAND_ERROR_SCHEDULER_EXTERNAL_NOT_ALLOWED		"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":26,\"Success\":false,\"Data\":\"Tasker not allowed from external source!\"}"
#define COMMAND_ERROR_HANDLER_NOT_INITIALIZED				"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":27,\"Success\":false,\"Data\":\"Handler is not initialized! Restart server!\"}"
#define COMMAND_ERROR_PIPE_ERROR							"{\"Category\":\"Command\",\"Action\":\"\",\"Error\":28,\"Success\":false,\"Data\":\"System command error. Pipe Error!\"}"

#define APPLICATION_INFORMATION_ERROR_ADD					"{\"Category\":\"ApplicationInformation\",\"Action\":\"\",\"Error\":261,\"Success\":false,\"Data\":\"Could not add application information!\"}"
#define APPLICATION_INFORMATION_ERROR_UPDATE				"{\"Category\":\"ApplicationInformation\",\"Action\":\"\",\"Error\":262,\"Success\":false,\"Data\":\"Could not update application information!\"}"
#define APPLICATION_INFORMATION_ERROR_DELETE				"{\"Category\":\"ApplicationInformation\",\"Action\":\"\",\"Error\":263,\"Success\":false,\"Data\":\"Could not delete application information!\"}"
#define APPLICATION_INFORMATION_ERROR_WRONG_WORD_SIZE		"{\"Category\":\"ApplicationInformation\",\"Action\":\"\",\"Error\":264,\"Success\":false,\"Data\":\"Wrong word size for application information!\"}"

#define CHANGE_ERROR_ADD									"{\"Category\":\"Change\",\"Action\":\"\",\"Error\":271,\"Success\":false,\"Data\":\"Could not add change!\"}"
#define CHANGE_ERROR_UPDATE									"{\"Category\":\"Change\",\"Action\":\"\",\"Error\":272,\"Success\":false,\"Data\":\"Could not update change!\"}"
#define CHANGE_ERROR_DELETE									"{\"Category\":\"Change\",\"Action\":\"\",\"Error\":273,\"Success\":false,\"Data\":\"Could not delete change!\"}"
#define CHANGE_ERROR_WRONG_WORD_SIZE						"{\"Category\":\"Change\",\"Action\":\"\",\"Error\":274,\"Success\":false,\"Data\":\"Wrong word size for change!\"}"

#define COIN_ERROR_ADD										"{\"Category\":\"Coin\",\"Action\":\"\",\"Error\":171,\"Success\":false,\"Data\":\"Could not add coin!\"}"
#define COIN_ERROR_UPDATE									"{\"Category\":\"Coin\",\"Action\":\"\",\"Error\":172,\"Success\":false,\"Data\":\"Could not update coin!\"}"
#define COIN_ERROR_DELETE									"{\"Category\":\"Coin\",\"Action\":\"\",\"Error\":173,\"Success\":false,\"Data\":\"Could not delete coin!\"}"
#define COIN_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"Coin\",\"Action\":\"\",\"Error\":174,\"Success\":false,\"Data\":\"Wrong word size for coin!\"}"

#define CONTACT_ERROR_ADD									"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":31,\"Success\":false,\"Data\":\"Could not add contact!\"}"
#define CONTACT_ERROR_UPDATE								"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":32,\"Success\":false,\"Data\":\"Could not update contact!\"}"
#define CONTACT_ERROR_DELETE								"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":33,\"Success\":false,\"Data\":\"Could not delete contact!\"}"
#define CONTACT_ERROR_MAIL									"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":34,\"Success\":false,\"Data\":\"Could not send mail!\"}"
#define CONTACT_ERROR_WRONG_WORD_SIZE						"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":35,\"Success\":false,\"Data\":\"Wrong word size for contact!\"}"
#define CONTACT_ERROR_INVALID_DATA							"{\"Category\":\"Contact\",\"Action\":\"\",\"Error\":39,\"Success\":false,\"Data\":\"Invalid data for contact!\"}"

#define DECRYPT_ERROR_KEY_NULL								"{\"Category\":\"Crypto\",\"Action\":\"\",\"Error\":300,\"Success\":false,\"Data\":\"Failed to decrypt! Key is null!\"}"
#define ENCRYPT_ERROR_KEY_NULL								"{\"Category\":\"Crypto\",\"Action\":\"\",\"Error\":301,\"Success\":false,\"Data\":\"Failed to encrypt! Key is null!\"}"

#define GPIO_ERROR_SET										"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":290,\"Success\":false,\"Data\":\"Could not set gpio!\"}"
#define GPIO_ERROR_ADD										"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":291,\"Success\":false,\"Data\":\"Could not add gpio!\"}"
#define GPIO_ERROR_UPDATE									"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":292,\"Success\":false,\"Data\":\"Could not update gpio!\"}"
#define GPIO_ERROR_DELETE									"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":293,\"Success\":false,\"Data\":\"Could not delete gpio!\"}"
#define GPIO_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":294,\"Success\":false,\"Data\":\"Wrong word size for gpio!\"}"
#define GPIO_ERROR_INVALID_STATE							"{\"Category\":\"Gpio\",\"Action\":\"\",\"Error\":299,\"Success\":false,\"Data\":\"Invalid state for gpio!\"}"

#define MAP_CONTENT_ERROR_ADD								"{\"Category\":\"MapContent\",\"Action\":\"\",\"Error\":101,\"Success\":false,\"Data\":\"Could not add mapcontent!\"}"
#define MAP_CONTENT_ERROR_UPDATE							"{\"Category\":\"MapContent\",\"Action\":\"\",\"Error\":102,\"Success\":false,\"Data\":\"Could not update mapcontent!\"}"
#define MAP_CONTENT_ERROR_DELETE							"{\"Category\":\"MapContent\",\"Action\":\"\",\"Error\":103,\"Success\":false,\"Data\":\"Could not delete mapcontent!\"}"
#define MAP_CONTENT_ERROR_WRONG_WORD_SIZE					"{\"Category\":\"MapContent\",\"Action\":\"\",\"Error\":104,\"Success\":false,\"Data\":\"Wrong word size for mapcontent!\"}"

#define MEAL_ERROR_ADD										"{\"Category\":\"Meal\",\"Action\":\"\",\"Error\":131,\"Success\":false,\"Data\":\"Could not add meal!\"}"
#define MEAL_ERROR_UPDATE									"{\"Category\":\"Meal\",\"Action\":\"\",\"Error\":132,\"Success\":false,\"Data\":\"Could not update meal!\"}"
#define MEAL_ERROR_DELETE									"{\"Category\":\"Meal\",\"Action\":\"\",\"Error\":133,\"Success\":false,\"Data\":\"Could not delete meal!\"}"
#define MEAL_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"Meal\",\"Action\":\"\",\"Error\":134,\"Success\":false,\"Data\":\"Wrong word size for meal!\"}"
#define MEAL_ERROR_INVALID_DATA								"{\"Category\":\"Meal\",\"Action\":\"\",\"Error\":139,\"Success\":false,\"Data\":\"Invalid data for meal!\"}"

#define MEDIA_SERVER_ERROR_ADD								"{\"Category\":\"MediaServer\",\"Action\":\"\",\"Error\":211,\"Success\":false,\"Data\":\"Could not add mediaserver!\"}"
#define MEDIA_SERVER_ERROR_UPDATE							"{\"Category\":\"MediaServer\",\"Action\":\"\",\"Error\":212,\"Success\":false,\"Data\":\"Could not update mediaserver!\"}"
#define MEDIA_SERVER_ERROR_DELETE							"{\"Category\":\"MediaServer\",\"Action\":\"\",\"Error\":213,\"Success\":false,\"Data\":\"Could not delete mediaserver!\"}"
#define MEDIA_SERVER_ERROR_WRONG_WORD_SIZE					"{\"Category\":\"MediaServer\",\"Action\":\"\",\"Error\":214,\"Success\":false,\"Data\":\"Wrong word size for mediaserver!\"}"

#define METER_LOG_ITEM_ERROR_ADD							"{\"Category\":\"MeterLogItem\",\"Action\":\"\",\"Error\":161,\"Success\":false,\"Data\":\"Could not add meter log item!\"}"
#define METER_LOG_ITEM_ERROR_UPDATE							"{\"Category\":\"MeterLogItem\",\"Action\":\"\",\"Error\":162,\"Success\":false,\"Data\":\"Could not update meter log item!\"}"
#define METER_LOG_ITEM_ERROR_DELETE							"{\"Category\":\"MeterLogItem\",\"Action\":\"\",\"Error\":163,\"Success\":false,\"Data\":\"Could not delete meter log item!\"}"
#define METER_LOG_ITEM_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"MeterLogItem\",\"Action\":\"\",\"Error\":164,\"Success\":false,\"Data\":\"Wrong word size for meter log item!\"}"
#define METER_LOG_ITEM_ERROR_INVALID_DATA					"{\"Category\":\"MeterLogItem\",\"Action\":\"\",\"Error\":169,\"Success\":false,\"Data\":\"Invalid data for meter log item!\"}"

#define MONEY_LOG_ITEM_ERROR_ADD							"{\"Category\":\"MoneyLogItem\",\"Action\":\"\",\"Error\":181,\"Success\":false,\"Data\":\"Could not add money log item!\"}"
#define MONEY_LOG_ITEM_ERROR_UPDATE							"{\"Category\":\"MoneyLogItem\",\"Action\":\"\",\"Error\":182,\"Success\":false,\"Data\":\"Could not update money log item!\"}"
#define MONEY_LOG_ITEM_ERROR_DELETE							"{\"Category\":\"MoneyLogItem\",\"Action\":\"\",\"Error\":183,\"Success\":false,\"Data\":\"Could not delete money log item!\"}"
#define MONEY_LOG_ITEM_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"MoneyLogItem\",\"Action\":\"\",\"Error\":184,\"Success\":false,\"Data\":\"Wrong word size for money log item!\"}"
#define MONEY_LOG_ITEM_ERROR_INVALID_DATA					"{\"Category\":\"MoneyLogItem\",\"Action\":\"\",\"Error\":189,\"Success\":false,\"Data\":\"Invalid data for money log item!\"}"

#define MOVIE_ERROR_UPDATE									"{\"Category\":\"Movie\",\"Action\":\"\",\"Error\":42,\"Success\":false,\"Data\":\"Could not update movie!\"}"
#define MOVIE_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"Movie\",\"Action\":\"\",\"Error\":44,\"Success\":false,\"Data\":\"Wrong word size for movie!\"}"
#define MOVIE_ERROR_INVALID_INDEX							"{\"Category\":\"Movie\",\"Action\":\"\",\"Error\":49,\"Success\":false,\"Data\":\"Start index higher then last index value!\"}"

#define PUCK_JS_ERROR_ADD									"{\"Category\":\"PuckJs\",\"Action\":\"\",\"Error\":191,\"Success\":false,\"Data\":\"Could not add puckjs!\"}"
#define PUCK_JS_ERROR_UPDATE								"{\"Category\":\"PuckJs\",\"Action\":\"\",\"Error\":192,\"Success\":false,\"Data\":\"Could not update puckjs!\"}"
#define PUCK_JS_ERROR_DELETE								"{\"Category\":\"PuckJs\",\"Action\":\"\",\"Error\":193,\"Success\":false,\"Data\":\"Could not delete puckjs!\"}"
#define PUCK_JS_ERROR_WRONG_WORD_SIZE						"{\"Category\":\"PuckJs\",\"Action\":\"\",\"Error\":194,\"Success\":false,\"Data\":\"Wrong word size for puckjs!\"}"

#define RADIO_STREAM_ERROR_ADD								"{\"Category\":\"RadioStream\",\"Action\":\"\",\"Error\":231,\"Success\":false,\"Data\":\"Could not add radio stream!\"}"
#define RADIO_STREAM_ERROR_UPDATE							"{\"Category\":\"RadioStream\",\"Action\":\"\",\"Error\":232,\"Success\":false,\"Data\":\"Could not update radio stream!\"}"
#define RADIO_STREAM_ERROR_DELETE							"{\"Category\":\"RadioStream\",\"Action\":\"\",\"Error\":233,\"Success\":false,\"Data\":\"Could not delete radio stream!\"}"
#define RADIO_STREAM_ERROR_WRONG_WORD_SIZE					"{\"Category\":\"RadioStream\",\"Action\":\"\",\"Error\":234,\"Success\":false,\"Data\":\"Wrong word size for radio stream!\"}"

#define ROOM_ERROR_ADD										"{\"Category\":\"Room\",\"Action\":\"\",\"Error\":201,\"Success\":false,\"Data\":\"Could not add room!\"}"
#define ROOM_ERROR_UPDATE									"{\"Category\":\"Room\",\"Action\":\"\",\"Error\":202,\"Success\":false,\"Data\":\"Could not update room!\"}"
#define ROOM_ERROR_DELETE									"{\"Category\":\"Room\",\"Action\":\"\",\"Error\":203,\"Success\":false,\"Data\":\"Could not delete room!\"}"
#define ROOM_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"Room\",\"Action\":\"\",\"Error\":204,\"Success\":false,\"Data\":\"Wrong word size for room!\"}"

#define RSS_FEED_ERROR_ADD									"{\"Category\":\"RssFeed\",\"Action\":\"\",\"Error\":241,\"Success\":false,\"Data\":\"Could not add rss feed!\"}"
#define RSS_FEED_ERROR_UPDATE								"{\"Category\":\"RssFeed\",\"Action\":\"\",\"Error\":242,\"Success\":false,\"Data\":\"Could not update rss feed!\"}"
#define RSS_FEED_ERROR_DELETE								"{\"Category\":\"RssFeed\",\"Action\":\"\",\"Error\":243,\"Success\":false,\"Data\":\"Could not delete rss feed!\"}"
#define RSS_FEED_ERROR_WRONG_WORD_SIZE						"{\"Category\":\"RssFeed\",\"Action\":\"\",\"Error\":244,\"Success\":false,\"Data\":\"Wrong word size for rss feed!\"}"

#define SECURITY_ERROR_MOTION_IS_RUNNING					"{\"Category\":\"Securitz\",\"Action\":\"\",\"Error\":156,\"Success\":false,\"Data\":\"Security motion already running!\"}"
#define SECURITY_ERROR_MOTION_NOT_RUNNING					"{\"Category\":\"Securitz\",\"Action\":\"\",\"Error\":157,\"Success\":false,\"Data\":\"Security motion not running!\"}"
#define SECURITY_ERROR_INVALID_INDEX_5_DATA					"{\"Category\":\"Securitz\",\"Action\":\"\",\"Error\":158,\"Success\":false,\"Data\":\"Invalid data at index 5 for security!\"}"
#define SECURITY_ERROR_INVALID_DATA							"{\"Category\":\"Securitz\",\"Action\":\"\",\"Error\":159,\"Success\":false,\"Data\":\"Invalid data for security!\"}"

#define SHOPPING_ITEM_ERROR_ADD								"{\"Category\":\"ShoppingItem\",\"Action\":\"\",\"Error\":111,\"Success\":false,\"Data\":\"Could not add shopping item!\"}"
#define SHOPPING_ITEM_ERROR_UPDATE							"{\"Category\":\"ShoppingItem\",\"Action\":\"\",\"Error\":112,\"Success\":false,\"Data\":\"Could not update shopping item!\"}"
#define SHOPPING_ITEM_ERROR_DELETE							"{\"Category\":\"ShoppingItem\",\"Action\":\"\",\"Error\":113,\"Success\":false,\"Data\":\"Could not delete shopping item!\"}"
#define SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE					"{\"Category\":\"ShoppingItem\",\"Action\":\"\",\"Error\":114,\"Success\":false,\"Data\":\"Wrong word size for shopping item!\"}"

#define SUGGESTED_MEAL_ERROR_ADD							"{\"Category\":\"SuggestedMeal\",\"Action\":\"\",\"Error\":141,\"Success\":false,\"Data\":\"Could not add suggested meal!\"}"
#define SUGGESTED_MEAL_ERROR_UPDATE							"{\"Category\":\"SuggestedMeal\",\"Action\":\"\",\"Error\":142,\"Success\":false,\"Data\":\"Could not update suggested meal!\"}"
#define SUGGESTED_MEAL_ERROR_DELETE							"{\"Category\":\"SuggestedMeal\",\"Action\":\"\",\"Error\":143,\"Success\":false,\"Data\":\"Could not delete suggested meal!\"}"
#define SUGGESTED_MEAL_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"SuggestedMeal\",\"Action\":\"\",\"Error\":144,\"Success\":false,\"Data\":\"Wrong word size for suggested meal!\"}"

#define SUGGESTED_SHOPPING_ITEM_ERROR_ADD					"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"\",\"Error\":121,\"Success\":false,\"Data\":\"Could not add suggested shopping item!\"}"
#define SUGGESTED_SHOPPING_ITEM_ERROR_UPDATE				"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"\",\"Error\":122,\"Success\":false,\"Data\":\"Could not update suggested shopping item!\"}"
#define SUGGESTED_SHOPPING_ITEM_ERROR_DELETE				"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"\",\"Error\":123,\"Success\":false,\"Data\":\"Could not delete suggested shopping item!\"}"
#define SUGGESTED_SHOPPING_ITEM_ERROR_WRONG_WORD_SIZE		"{\"Category\":\"SuggestedShoppingItem\",\"Action\":\"\",\"Error\":124,\"Success\":false,\"Data\":\"Wrong word size for suggested shopping item!\"}"

#define TEMPERATURE_ERROR_NOT_INITIALIZED					"{\"Category\":\"Temperature\",\"Action\":\"\",\"Error\":98,\"Success\":false,\"Data\":\"Temperature is not initialized!\"}"
#define TEMPERATURE_ERROR_INVALID_DATA						"{\"Category\":\"Temperature\",\"Action\":\"\",\"Error\":99,\"Success\":false,\"Data\":\"Invalid data for temperature!\"}"

#define USER_ERROR_VALIDATE									"{\"Category\":\"User\",\"Action\":\"\",\"Error\":250,\"Success\":false,\"Data\":\"Failed to validate user!\"}"
#define USER_ERROR_ADD										"{\"Category\":\"User\",\"Action\":\"\",\"Error\":251,\"Success\":false,\"Data\":\"Could not add user!\"}"
#define USER_ERROR_UPDATE									"{\"Category\":\"User\",\"Action\":\"\",\"Error\":252,\"Success\":false,\"Data\":\"Could not update user!\"}"
#define USER_ERROR_DELETE									"{\"Category\":\"User\",\"Action\":\"\",\"Error\":253,\"Success\":false,\"Data\":\"Could not delete user!\"}"
#define USER_ERROR_WRONG_WORD_SIZE							"{\"Category\":\"User\",\"Action\":\"\",\"Error\":254,\"Success\":false,\"Data\":\"Wrong word size for user!\"}"

#define WIRELESS_SCHEDULE_ERROR_SET							"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":60,\"Success\":false,\"Data\":\"Could not set wireless schedule!\"}"
#define WIRELESS_SCHEDULE_ERROR_ADD							"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":61,\"Success\":false,\"Data\":\"Could not add wireless schedule!\"}"
#define WIRELESS_SCHEDULE_ERROR_UPDATE						"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":62,\"Success\":false,\"Data\":\"Could not update wireless schedule!\"}"
#define WIRELESS_SCHEDULE_ERROR_DELETE						"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":63,\"Success\":false,\"Data\":\"Could not delete wireless schedule!\"}"
#define WIRELESS_SCHEDULE_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":64,\"Success\":false,\"Data\":\"Wrong word size for wireless schedule!\"}"
#define WIRELESS_SCHEDULE_ERROR_INVALID_STATE				"{\"Category\":\"WirelessSchedule\",\"Action\":\"\",\"Error\":69,\"Success\":false,\"Data\":\"Invalid state for wireless schedule!\"}"

#define WIRELESS_SOCKET_ERROR_SET							"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":70,\"Success\":false,\"Data\":\"Could not set wireless socket!\"}"
#define WIRELESS_SOCKET_ERROR_ADD							"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":71,\"Success\":false,\"Data\":\"Could not add wireless socket!\"}"
#define WIRELESS_SOCKET_ERROR_UPDATE						"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":72,\"Success\":false,\"Data\":\"Could not update wireless socket!\"}"
#define WIRELESS_SOCKET_ERROR_DELETE						"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":73,\"Success\":false,\"Data\":\"Could not delete wireless socket!\"}"
#define WIRELESS_SOCKET_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":74,\"Success\":false,\"Data\":\"Wrong word size for wireless socket!\"}"
#define WIRELESS_SOCKET_ERROR_INVALID_STATE					"{\"Category\":\"WirelessSocket\",\"Action\":\"\",\"Error\":79,\"Success\":false,\"Data\":\"Invalid state for wireless socket!\"}"

#define WIRELESS_SWITCH_ERROR_TOGGLE						"{\"Category\":\"WirelessSwitch\",\"Action\":\"\",\"Error\":80,\"Success\":false,\"Data\":\"Could not set wireless switch!\"}"
#define WIRELESS_SWITCH_ERROR_ADD							"{\"Category\":\"WirelessSwitch\",\"Action\":\"\",\"Error\":81,\"Success\":false,\"Data\":\"Could not add wireless switch!\"}"
#define WIRELESS_SWITCH_ERROR_UPDATE						"{\"Category\":\"WirelessSwitch\",\"Action\":\"\",\"Error\":82,\"Success\":false,\"Data\":\"Could not update wireless switch!\"}"
#define WIRELESS_SWITCH_ERROR_DELETE						"{\"Category\":\"WirelessSwitch\",\"Action\":\"\",\"Error\":83,\"Success\":false,\"Data\":\"Could not delete wireless switch!\"}"
#define WIRELESS_SWITCH_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"WirelessSwitch\",\"Action\":\"\",\"Error\":84,\"Success\":false,\"Data\":\"Wrong word size for wireless switch!\"}"

#define WIRELESS_TIMER_ERROR_ADD							"{\"Category\":\"WirelessTimer\",\"Action\":\"\",\"Error\":280,\"Success\":false,\"Data\":\"Could not add wireless timer!\"}"
#define WIRELESS_TIMER_ERROR_UPDATE							"{\"Category\":\"WirelessTimer\",\"Action\":\"\",\"Error\":281,\"Success\":false,\"Data\":\"Could not update wireless timer!\"}"
#define WIRELESS_TIMER_ERROR_DELETE							"{\"Category\":\"WirelessTimer\",\"Action\":\"\",\"Error\":282,\"Success\":false,\"Data\":\"Could not delete wireless timer!\"}"
#define WIRELESS_TIMER_ERROR_WRONG_WORD_SIZE				"{\"Category\":\"WirelessTimer\",\"Action\":\"\",\"Error\":283,\"Success\":false,\"Data\":\"Wrong word size for wireless timer!\"}"
#define WIRELESS_TIMER_ERROR_INVALID_STATE					"{\"Category\":\"WirelessTimer\",\"Action\":\"\",\"Error\":289,\"Success\":false,\"Data\":\"Invalid state for wireless timer!\"}"

#define YOUTUBE_VIDEO_ERROR_ADD								"{\"Category\":\"YoutubeVideo\",\"Action\":\"\",\"Error\":221,\"Success\":false,\"Data\":\"Could not add youtube video!\"}"
#define YOUTUBE_VIDEO_ERROR_UPDATE							"{\"Category\":\"YoutubeVideo\",\"Action\":\"\",\"Error\":222,\"Success\":false,\"Data\":\"Could not update youtube video!\"}"
#define YOUTUBE_VIDEO_ERROR_DELETE							"{\"Category\":\"YoutubeVideo\",\"Action\":\"\",\"Error\":223,\"Success\":false,\"Data\":\"Could not delete youtube video!\"}"
#define YOUTUBE_VIDEO_ERROR_WRONG_WORD_SIZE					"{\"Category\":\"YoutubeVideo\",\"Action\":\"\",\"Error\":224,\"Success\":false,\"Data\":\"Wrong word size for youtube video!\"}"

/**********************************************************************************************/
/************************************* COMMAND DEFINITIONS ************************************/
/**********************************************************************************************/

#define COMMAND_SPLITTER "::"

#define ACTIVATE "ACTIVATE"
#define DEACTIVATE "DEACTIVATE"
#define TOGGLE "TOGGLE"

#define SET "SET"
#define ADD "ADD"
#define CLEAR "CLEAR"
#define DELETE "DELETE"
#define UPDATE "UPDATE"
#define MAIL "MAIL"

#define ON "ON"
#define OFF "OFF"
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"

#define ALL "ALL"
#define FOR_USER "FOR_USER"

#define AVAILABILITY "AVAILABILITY"
#define CHECK "CHECK"
#define CONTROL "CONTROL"
#define COUNT "COUNT"
#define DATA "DATA"
#define GET "GET"
#define INDEX "INDEX"
#define LOAD "LOAD"
#define MAIN "MAIN"
#define MOTION "MOTION"
#define PHP "PHP"
#define PLAY "PLAY"
#define RESETFAILEDLOGIN "RESETFAILEDLOGIN"
#define SENSOR "SENSOR"
#define START "START"
#define STATE "STATE"
#define STOP "STOP"
#define URL "URL"
#define VALIDATE "VALIDATE"

#define MOTION_EVENTS_MAX_COUNT 100
#define MOTION_IMAGES_TO_SEND 10

#define MAIL_MIN_ADDRESS_LENGTH 9
#define MAIL_MAX_DATA_LENGTH 4096

#define APPLICATIONINFORMATION "APPLICATIONINFORMATION"
#define CHANGE "CHANGE"
#define COIN "COIN"
#define CONTACT "CONTACT"
#define GPIO "GPIO"
#define MAPCONTENT "MAPCONTENT"
#define MEAL "MEAL"
#define MEDIASERVER "MEDIASERVER"
#define METERLOGITEM "METERLOGITEM"
#define MONEYLOGITEM "MONEYLOGITEM"
#define MOVIE "MOVIE"
#define PUCKJS "PUCKJS"
#define RADIOSTREAM "RADIOSTREAM"
#define ROOM "ROOM"
#define RSSFEED "RSSFEED"
#define SECURITY "SECURITY"
#define SHOPPINGITEM "SHOPPINGITEM"
#define SUGGESTEDMEAL "SUGGESTEDMEAL"
#define SUGGESTEDSHOPPINGITEM "SUGGESTEDSHOPPINGITEM"
#define TEMPERATURE "TEMPERATURE"
#define USER "USER"
#define WIRELESSSCHEDULE "WIRELESSSCHEDULE"
#define WIRELESSSOCKET "WIRELESSSOCKET"
#define WIRELESSSWITCH "WIRELESSSWITCH"
#define WIRELESSTIMER "WIRELESSTIMER"
#define YOUTUBEVIDEO "YOUTUBEVIDEO"

#define ACTION_LEVEL_ERROR -1
#define ACTION_LEVEL_LOW 1
#define ACTION_LEVEL_MEDIUM 2
#define ACTION_LEVEL_NORMAL 3
#define ACTION_LEVEL_CRIT 4
#define ACTION_LEVEL_SYSTEM 5

#define CMD_MIN_LENGTH 25
#define CMD_MAX_LENGTH 4096
#define CMD_SOURCE_EXTERNAL 1
#define CMD_SOURCE_TASKER 2

#define CMD_SUDO_MOTION "sudo motion"
#define CMD_SUDO_KILLALL_MOTION "sudo killall motion"
#define CMD_SUDO_REBOOT "sudo shutdown -r now"
#define CMD_SUDO_SHUTDOWN "sudo shutdown -h now"

#define CMD_SEND_MAIL "python /etc/default/lucahome/mail.py"

/**********************************************************************************************/
/************************************** INDEX DEFINITIONS *************************************/
/**********************************************************************************************/

#define USER_NAME_INDEX 0
#define PASSWORD_INDEX 1
#define CATEGORY_INDEX 2
#define ACTION_INDEX 3
#define ACTION_PARAMETER_INDEX 4

#define APPLICATION_INFORMATION_KEY_INDEX 4
#define APPLICATION_INFORMATION_VALUE_INDEX 5
#define APPLICATION_INFORMATION_DATA_SIZE 6

#define CAMERA_CMD_PARAMETER_INDEX 5
#define CAMERA_DATA_SIZE 6

#define CHANGE_DATA_SIZE 5

#define COIN_UUID_INDEX 4
#define COIN_USER_UUID_INDEX 5
#define COIN_TYPE_INDEX 6
#define COIN_AMOUNT_INDEX 7
#define COIN_DATA_SIZE 8

#define CONTACT_UUID_INDEX 4
#define CONTACT_NAME_INDEX 5
#define CONTACT_GROUP_INDEX 6
#define CONTACT_ADDRESS_INDEX 7
#define CONTACT_PHONE_HOME_INDEX 8
#define CONTACT_PHONE_MOBILE_INDEX 9
#define CONTACT_EMAIL_INDEX 10
#define CONTACT_BIRTHDAY_DAY_INDEX 11
#define CONTACT_BIRTHDAY_MONTH_INDEX 12
#define CONTACT_BIRTHDAY_YEAR_INDEX 13
#define CONTACT_BIRTHDAY_REMINDME_INDEX 14
#define CONTACT_DATA_SIZE 15
#define CONTACT_MAIL_MESSAGE_INDEX 5
#define CONTACT_MAIL_MESSAGE_DATA_SIZE 15

#define GPIO_UUID_INDEX 4
#define GPIO_NAME_INDEX 5
#define GPIO_PIN_INDEX 6
#define GPIO_STATE_INDEX 7
#define GPIO_DATA_SIZE 8

#define GPIO_SET_STATE_INDEX 5
#define GPIO_SET_DATA_SIZE 6

#define MAP_CONTENT_UUID_INDEX 4
#define MAP_CONTENT_TYPE_UUID_INDEX 5
#define MAP_CONTENT_TYPE_INDEX 6
#define MAP_CONTENT_COORDINATES_X_INDEX 7
#define MAP_CONTENT_COORDINATES_Y_INDEX 8
#define MAP_CONTENT_NAME_INDEX 9
#define MAP_CONTENT_SHORT_NAME_INDEX 10
#define MAP_CONTENT_VISIBILITY_INDEX 11
#define MAP_CONTENT_DATA_SIZE 12

#define MEAL_UUID_INDEX 4
#define MEAL_TITLE_INDEX 5
#define MEAL_DESCRIPTION_INDEX 6
#define MEAL_WEEKDAY_INDEX 7
#define MEAL_DAY_INDEX 8
#define MEAL_MONTH_INDEX 9
#define MEAL_YEAR_INDEX 10
#define MEAL_SHOPPING_UUID_LIST_INDEX 11
#define MEAL_DATA_SIZE 12

#define MEDIA_SERVER_UUID_INDEX 4
#define MEDIA_SERVER_ROOM_UUID_INDEX 5
#define MEDIA_SERVER_IP_INDEX 6
#define MEDIA_SERVER_IS_SLEEPING_SERVER_INDEX 7
#define MEDIA_SERVER_WIRELESS_SOCKET_UUID 8
#define MEDIA_SERVER_DATA_SIZE 9

#define METER_LOG_ITEM_UUID_INDEX 4
#define METER_LOG_ITEM_ROOM_UUID_INDEX 5
#define METER_LOG_ITEM_TYPE_UUID_INDEX 6
#define METER_LOG_ITEM_TYPE_INDEX 7
#define METER_LOG_ITEM_METER_ID_INDEX 8
#define METER_LOG_ITEM_VALUE_INDEX 9
#define METER_LOG_ITEM_IMAGE_NAME_INDEX 10
#define METER_LOG_ITEM_SAVE_DATE_TIME_INDEX 11
#define METER_LOG_ITEM_DATA_SIZE 12

#define MONEY_LOG_ITEM_UUID_INDEX 4
#define MONEY_LOG_ITEM_TYPE_UUID_INDEX 5
#define MONEY_LOG_ITEM_BANK_INDEX 6
#define MONEY_LOG_ITEM_PLAN_INDEX 7
#define MONEY_LOG_ITEM_AMOUNT_INDEX 8
#define MONEY_LOG_ITEM_UNIT_INDEX 9
#define MONEY_LOG_ITEM_USER_UUID_INDEX 10
#define METER_LOG_ITEM_SAVE_DATE_INDEX 11
#define MONEY_LOG_ITEM_DATA_SIZE 12

#define MONEY_LOG_ITEM_GET_USER_UUID_INDEX 5

#define MOVIE_UUID_INDEX 4
#define MOVIE_TITLE_INDEX 5
#define MOVIE_GENRE_INDEX 6
#define MOVIE_DESCRIPTION_INDEX 7
#define MOVIE_RATING_INDEX 8
#define MOVIE_WATCH_COUNT_INDEX 9
#define MOVIE_DATA_SIZE 10

#define MOVIE_LOW_INDEX 5
#define MOVIE_HIGH_INDEX 6
#define MOVIE_ADDITIONAL_INDEX 7
#define MOVIE_INDEX_DATA_SIZE 8

#define PUCK_JS_UUID_INDEX 4
#define PUCK_JS_ROOM_UUID_INDEX 5
#define PUCK_JS_NAME_INDEX 6
#define PUCK_JS_MAC_INDEX 7
#define PUCK_JS_DATA_SIZE 8

#define RADIO_STREAM_UUID_INDEX 4
#define RADIO_STREAM_TITLE_INDEX 5
#define RADIO_STREAM_URL_INDEX 6
#define RADIO_STREAM_PLAY_COUNT_INDEX 7
#define RADIO_STREAM_DATA_SIZE 8

#define ROOM_UUID_INDEX 4
#define ROOM_NAME_INDEX 5
#define ROOM_TYPE_INDEX 6
#define ROOM_DATA_SIZE 7

#define RSS_FEED_UUID_INDEX 4
#define RSS_FEED_TITLE_INDEX 5
#define RSS_FEED_URL_INDEX 6
#define RSS_FEED_PLAY_COUNT_INDEX 7
#define RSS_FEED_DATA_SIZE 8

#define SHOPPING_ITEM_UUID_INDEX 4
#define SHOPPING_ITEM_NAME_INDEX 5
#define SHOPPING_ITEM_TYPE_INDEX 6
#define SHOPPING_ITEM_QUANTITY_INDEX 7
#define SHOPPING_ITEM_UNIT_INDEX 8
#define SHOPPING_ITEM_DATA_SIZE 9

#define SUGGESTED_MEAL_UUID_INDEX 4
#define SUGGESTED_MEAL_TITLE_INDEX 5
#define SUGGESTED_MEAL_DESCRIPTION_INDEX 6
#define SUGGESTED_MEAL_RATING_INDEX 7
#define SUGGESTED_MEAL_USE_COUNTER_INDEX 8
#define SUGGESTED_MEAL_SHOPPING_UUID_LIST_INDEX 9
#define SUGGESTED_MEAL_DATA_SIZE 10

#define SUGGESTED_SHOPPING_ITEM_UUID_INDEX 4
#define SUGGESTED_SHOPPING_ITEM_NAME_INDEX 5
#define SUGGESTED_SHOPPING_ITEM_TYPE_INDEX 6
#define SUGGESTED_SHOPPING_ITEM_QUANTITY_INDEX 7
#define SUGGESTED_SHOPPING_ITEM_UNIT_INDEX 8
#define SUGGESTED_SHOPPING_ITEM_DATA_SIZE 9

#define USER_UUID_INDEX 4
#define USER_DATA_NAME_INDEX 5
#define USER_PASSPHRASE_INDEX 6
#define USER_ROLE_INDEX 7
#define USER_DATA_SIZE 8

#define WIRELESS_SCHEDULE_UUID_INDEX 4
#define WIRELESS_SCHEDULE_NAME_INDEX 5
#define WIRELESS_SCHEDULE_WEEKDAY_INDEX 6
#define WIRELESS_SCHEDULE_HOUR_INDEX 7
#define WIRELESS_SCHEDULE_MINUTE_INDEX 8
#define WIRELESS_SCHEDULE_GPIO_UUID_INDEX 9
#define WIRELESS_SCHEDULE_GPIO_ACTION_INDEX 10
#define WIRELESS_SCHEDULE_WIRELESS_SOCKET_UUID_INDEX 11
#define WIRELESS_SCHEDULE_WIRELESS_SOCKET_ACTION_INDEX 12
#define WIRELESS_SCHEDULE_WIRELESS_SWITCH_UUID_INDEX 13
#define WIRELESS_SCHEDULE_DATA_SIZE 14

#define WIRELESS_SCHEDULE_SET_STATE_INDEX 5
#define WIRELESS_SCHEDULE_SET_DATA_SIZE 6

#define WIRELESS_SOCKET_UUID_INDEX 4
#define WIRELESS_SOCKET_ROOM_UUID_INDEX 5
#define WIRELESS_SOCKET_NAME_INDEX 6
#define WIRELESS_SOCKET_CODE_INDEX 7
#define WIRELESS_SOCKET_DATA_SIZE 8

#define WIRELESS_SOCKET_SET_STATE_INDEX 5
#define WIRELESS_SOCKET_SET_DATA_SIZE 6

#define WIRELESS_SWITCH_UUID_INDEX 4
#define WIRELESS_SWITCH_ROOM_UUID_INDEX 5
#define WIRELESS_SWITCH_NAME_INDEX 6
#define WIRELESS_SWITCH_REMOTE_ID_INDEX 7
#define WIRELESS_SWITCH_KEY_CODE_INDEX 8
#define WIRELESS_SWITCH_ACTION_INDEX 9
#define WIRELESS_SWITCH_DATA_SIZE 10

#define WIRELESS_SWITCH_TOGGLE_DATA_SIZE 5

#define WIRELESS_TIMER_UUID_INDEX 4
#define WIRELESS_TIMER_NAME_INDEX 5
#define WIRELESS_TIMER_WEEKDAY_INDEX 6
#define WIRELESS_TIMER_HOUR_INDEX 7
#define WIRELESS_TIMER_MINUTE_INDEX 8
#define WIRELESS_TIMER_GPIO_UUID_INDEX 9
#define WIRELESS_TIMER_GPIO_ACTION_INDEX 10
#define WIRELESS_TIMER_WIRELESS_SOCKET_UUID_INDEX 11
#define WIRELESS_TIMER_WIRELESS_SOCKET_ACTION_INDEX 12
#define WIRELESS_TIMER_WIRELESS_SWITCH_UUID_INDEX 13
#define WIRELESS_TIMER_DATA_SIZE 14

#define YOUTUBE_VIDEO_UUID_INDEX 4
#define YOUTUBE_VIDEO_TITLE_INDEX 5
#define YOUTUBE_VIDEO_ID_INDEX 6
#define YOUTUBE_VIDEO_PLAY_COUNT_INDEX 7
#define YOUTUBE_VIDEO_DESCRIPTION_INDEX 8
#define YOUTUBE_VIDEO_MEDIUM_IMAGE_URL_INDEX 9
#define YOUTUBE_VIDEO_DATA_SIZE 10

/**********************************************************************************************/
/************************************* TIMEOUT DEFINITIONS ************************************/
/**********************************************************************************************/

#define BIRTHDAY_CHECK_TIMEOUT 2 * 60 * 60
#define MOTION_CONTROL_TIMEOUT 15
#define SHOPPING_ITEM_CHECK_TIMEOUT 2 * 60 * 60
#define TASK_CONTROL_TIMEOUT 10
#define TEMPERATURE_CONTROL_TIMEOUT 60

/**********************************************************************************************/
/*************************************** PATH DEFINITIONS *************************************/
/**********************************************************************************************/

#define NAS_PATH_CAMERA "/mnt/NAS/Camera/"
#define NAS_PATH_LUCAHOME "/mnt/NAS/LucaHome/"
#define NAS_PATH_METER_LOG "/mnt/NAS/MeterLog/"
#define NAS_PATH_MOVIE "/mnt/NAS/Movies/"
#define NAS_PATH_MUSIC "/mnt/NAS/Music/"
#define NAS_PATH_SERIES "/mnt/NAS/Series/"

/**********************************************************************************************/
/*************************************** FILE DEFINITIONS *************************************/
/**********************************************************************************************/

#define IS_FOLDER 0x4
#define IS_FILE 0x8

#define JPG_ENDING ".jpg"
#define SWF_ENDING ".swf"

#define NFO_LUCA_FILE "NFO.luca"

/**********************************************************************************************/
/************************************** OTHER DEFINITIONS *************************************/
/**********************************************************************************************/

#define DATA_GPIO 17
#define SECONDS_OF_7_DAYS 7 * 24 * 60 * 60

#define BUFFER_LENGTH 512
#define SERVER_PORT 6677
#define TASK_TYPE_SCHEDULE 0
#define TASK_TYPE_TIMER 1
