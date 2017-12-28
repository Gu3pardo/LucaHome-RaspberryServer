/***********************************************/
/*************** USER DEFINITIONS **************/
/***********************************************/

#define DEFAULT_PASSWORD "0000"
#define MAX_INVALID_LOGIN_COUNT 5
#define NO_PASSWORD "NO_PASSWORD"
#define DUMMY "DUMMY"
#define SCHEDULER "Scheduler"
#define SCHEDULER_PASSWORD "435435"

/***********************************************/
/************* SUCCESS DEFINITIONS *************/
/***********************************************/

#define AUTHENTIFICATION_RESET_FAILED_LOGIN_COUNT_SUCCESS "AUTHENTIFICATION:RESET_FAILED_LOGIN_COUNT:SUCCESS"

#define BIRTHDAY_ADD_SUCCESS "BIRTHDAY:ADD:SUCCESS"
#define BIRTHDAY_UPDATE_SUCCESS "BIRTHDAY:UPDATE:SUCCESS"
#define BIRTHDAY_DELETE_SUCCESS "BIRTHDAY:DELETE:SUCCESS"
#define BIRTHDAY_ACTIVATE_CONTROL_SUCCESS "BIRTHDAY:SET_CONTROL_ON:SUCCESS"
#define BIRTHDAY_DEACTIVATE_CONTROL_SUCCESS "BIRTHDAY:SET_CONTROL_OFF:SUCCESS"

#define CAMERA_START_CAMERA_SUCCESS "CAMERA:START_CAMERA:SUCCESS"
#define CAMERA_STOP_CAMERA_SUCCESS "CAMERA:STOP_CAMERA:SUCCESS"
#define CAMERA_START_MOTION_SUCCESS "CAMERA:START_MOTION:SUCCESS"
#define CAMERA_STOP_MOTION_SUCCESS "CAMERA:STOP_MOTION:SUCCESS"
#define CAMERA_ACTIVATE_MOTION_CONTROL_SUCCESS "CAMERA:SET_MOTION_CONTROL_ON:SUCCESS"
#define CAMERA_DEACTIVATE_MOTION_CONTROL_SUCCESS "CAMERA:SET_MOTION_CONTROL_OFF:SUCCESS"

#define COIN_ADD_SUCCESS "COIN:ADD:SUCCESS"
#define COIN_UPDATE_SUCCESS "COIN:UPDATE:SUCCESS"
#define COIN_DELETE_SUCCESS "COIN:DELETE:SUCCESS"

#define COMMAND_RELOAD_SUCCESS "COMMAND:RELOAD:SUCCESS"

#define GPIO_ADD_SUCCESS "GPIO:ADD:SUCCESS"
#define GPIO_UPDATE_SUCCESS "GPIO:UPDATE:SUCCESS"
#define GPIO_DELETE_SUCCESS "GPIO:DELETE:SUCCESS"
#define GPIO_ACTIVATE_ALL_SUCCESS "GPIO:ACTIVATE_ALL:SUCCESS"
#define GPIO_DEACTIVATE_ALL_SUCCESS "GPIO:DEACTIVATE_ALL:SUCCESS"
#define GPIO_SET_SUCCESS "GPIO:SET:SUCCESS"

#define MAP_CONTENT_ADD_SUCCESS "MAP_CONTENT:ADD:SUCCESS"
#define MAP_CONTENT_UPDATE_SUCCESS "MAP_CONTENT:UPDATE:SUCCESS"
#define MAP_CONTENT_DELETE_SUCCESS "MAP_CONTENT:DELETE:SUCCESS"

#define LISTED_MENU_ADD_SUCCESS "LISTED_MENU:ADD:SUCCESS"
#define LISTED_MENU_UPDATE_SUCCESS "LISTED_MENU:UPDATE:SUCCESS"
#define LISTED_MENU_DELETE_SUCCESS "LISTED_MENU:DELETE:SUCCESS"
#define MENU_UPDATE_SUCCESS "MENU:UPDATE:SUCCESS"
#define MENU_CLEAR_SUCCESS "MENU:CLEAR:SUCCESS"

#define METER_DATA_ADD_SUCCESS "METER_DATA:ADD:SUCCESS"
#define METER_DATA_UPDATE_SUCCESS "METER_DATA:UPDATE:SUCCESS"
#define METER_DATA_DELETE_SUCCESS "METER_DATA:DELETE:SUCCESS"

#define MONEY_METER_DATA_ADD_SUCCESS "MONEY_METER_DATA:ADD:SUCCESS"
#define MONEY_METER_DATA_UPDATE_SUCCESS "MONEY_METER_DATA:UPDATE:SUCCESS"
#define MONEY_METER_DATA_DELETE_SUCCESS "MONEY_METER_DATA:DELETE:SUCCESS"

#define MOVIE_UPDATE_SUCCESS "MOVIE:UPDATE:SUCCESS"
#define MOVIE_LOAD_SUCCESS "MOVIE:LOAD:SUCCESS"

#define SCHEDULE_ADD_SUCCESS "SCHEDULE:ADD:SUCCESS"
#define SCHEDULE_UPDATE_SUCCESS "SCHEDULE:UPDATE:SUCCESS"
#define SCHEDULE_DELETE_SUCCESS "SCHEDULE:DELETE:SUCCESS"
#define SCHEDULE_ACTIVATE_ALL_SUCCESS "SCHEDULE:ACTIVATE_ALL:SUCCESS"
#define SCHEDULE_DEACTIVATE_ALL_SUCCESS "SCHEDULE:DEACTIVATE_ALL:SUCCESS"
#define SCHEDULE_SET_SUCCESS "SCHEDULE:SET:SUCCESS"

#define SHOPPING_ADD_SUCCESS "SHOPPING:ADD:SUCCESS"
#define SHOPPING_UPDATE_SUCCESS "SHOPPING:UPDATE:SUCCESS"
#define SHOPPING_DELETE_SUCCESS "SHOPPING:DELETE:SUCCESS"

#define SOCKET_ADD_SUCCESS "SOCKET:ADD:SUCCESS"
#define SOCKET_UPDATE_SUCCESS "SOCKET:UPDATE:SUCCESS"
#define SOCKET_DELETE_SUCCESS "SOCKET:DELETE:SUCCESS"
#define SOCKET_ACTIVATE_ALL_SUCCESS "SOCKET:ACTIVATE_ALL:SUCCESS"
#define SOCKET_DEACTIVATE_ALL_SUCCESS "SOCKET:DEACTIVATE_ALL:SUCCESS"
#define SOCKET_SET_SUCCESS "SOCKET:SET:SUCCESS"

#define SWITCH_ADD_SUCCESS "SWITCH:ADD:SUCCESS"
#define SWITCH_UPDATE_SUCCESS "SWITCH:UPDATE:SUCCESS"
#define SWITCH_DELETE_SUCCESS "SWITCH:DELETE:SUCCESS"
#define SWITCH_TOGGLE_ALL_SUCCESS "SWITCH:TOGGLE_ALL:SUCCESS"
#define SWITCH_TOGGLE_SUCCESS "SOCKET:TOGGLE:SUCCESS"

#define SYSTEM_REBOOT_SUCCESS "SYSTEM:REBOOT:SUCCESS"
#define SYSTEM_SHUTDOWN_SUCCESS "SYSTEM:SHUTDOWN:SUCCESS"

#define TEMPERATURE_ACTIVATE_CONTROL_SUCCESS "TEMPERATURE:SET_CONTROL_ON:SUCCESS"
#define TEMPERATURE_DEACTIVATE_CONTROL_SUCCESS "TEMPERATURE:SET_CONTROL_OFF:SUCCESS"

#define USER_VALIDATE_SUCCESS "USER:VALIDATE:SUCCESS"

/***********************************************/
/************** ERROR DEFINITIONS **************/
/***********************************************/

#define AUTHENTIFICATION_ERROR_NR_10 "Error 10:Authentification failed"
#define AUTHENTIFICATION_ERROR_NR_11 "Error 11:UserAction cannot be performed! No rights"
#define AUTHENTIFICATION_ERROR_NR_12 "Error 12:No password"
#define AUTHENTIFICATION_ERROR_NR_13 "Error 13:No username"
#define AUTHENTIFICATION_ERROR_NR_14 "Error 14:Invalid source"
#define AUTHENTIFICATION_ERROR_NR_15 "Error 15:Could not reset invalid login count"

#define COMMAND_ERROR_NR_20 "Error 20:action not found"
#define COMMAND_ERROR_NR_21 "Error 21:statement too short"
#define COMMAND_ERROR_NR_23 "Error 23:No action"
#define COMMAND_ERROR_NR_24 "Error 24:No category"
#define COMMAND_ERROR_NR_25 "Error 25:No action parameter"
#define COMMAND_ERROR_NR_26 "Error 26:scheduler not allowed from external source"

#define BIRTHDAY_ERROR_NR_30 "Error 30:Failed to add birthday"
#define BIRTHDAY_ERROR_NR_31 "Error 31:Failed to update birthday"
#define BIRTHDAY_ERROR_NR_32 "Error 32:Failed to delete birthday"
#define BIRTHDAY_ERROR_NR_33 "Error 33:Wrong word size for birthday"
#define BIRTHDAY_ERROR_NR_34 "Error 34:Action not found for birthday"
#define BIRTHDAY_ERROR_NR_36 "Error 36:Invalid data for birthday"
#define BIRTHDAY_ERROR_NR_37 "Error 37:Wrong action parameter for birthday"

#define MOVIE_ERROR_NR_42 "Error 42:Could not update movie"
#define MOVIE_ERROR_NR_45 "Error 45:Start index higher then last index value"
#define MOVIE_ERROR_NR_47 "Error 47:Wrong word size for movie"
#define MOVIE_ERROR_NR_48 "Error 48:Action not found for movie"
#define MOVIE_ERROR_NR_400 "Error 400:Parameter not found for movie"

#define GPIO_ERROR_NR_50 "Error 50:Could not set gpio"
#define GPIO_ERROR_NR_51 "Error 51:Could not add gpio"
#define GPIO_ERROR_NR_52 "Error 52:Could not update gpio"
#define GPIO_ERROR_NR_53 "Error 53:Could not delete gpio"
#define GPIO_ERROR_NR_54 "Error 54:Could not activate all gpios"
#define GPIO_ERROR_NR_55 "Error 55:Wrong word size for gpio"
#define GPIO_ERROR_NR_56 "Error 56:Could not deactivate all gpios"
#define GPIO_ERROR_NR_57 "Error 57:Invalid state for gpio"

#define SCHEDULE_ERROR_NR_60 "Error 60:Could not set schedule"
#define SCHEDULE_ERROR_NR_61 "Error 61:Could not add schedule"
#define SCHEDULE_ERROR_NR_62 "Error 62:Could not update schedule"
#define SCHEDULE_ERROR_NR_63 "Error 63:Could not delete schedule"
#define SCHEDULE_ERROR_NR_64 "Error 64:Could not activate all schedules"
#define SCHEDULE_ERROR_NR_65 "Error 65:Wrong word size for schedule"
#define SCHEDULE_ERROR_NR_66 "Error 66:Could not deactivate all schedules"
#define SCHEDULE_ERROR_NR_67 "Error 67:Invalid state for schedule"

#define SOCKET_ERROR_NR_70 "Error 70:Could not set socket"
#define SOCKET_ERROR_NR_71 "Error 71:Could not add socket"
#define SOCKET_ERROR_NR_72 "Error 72:Could not update socket"
#define SOCKET_ERROR_NR_73 "Error 73:Could not delete socket"
#define SOCKET_ERROR_NR_74 "Error 74:Could not activate all sockets"
#define SOCKET_ERROR_NR_75 "Error 75:Wrong word size for socket"
#define SOCKET_ERROR_NR_76 "Error 76:Could not deactivate all sockets"
#define SOCKET_ERROR_NR_77 "Error 77:Invalid state for socket"
#define SOCKET_ERROR_NR_78 "Error 78:No sockets available"

#define SWITCH_ERROR_NR_80 "Error 80:Could not toggle switch"
#define SWITCH_ERROR_NR_81 "Error 81:Could not add switch"
#define SWITCH_ERROR_NR_82 "Error 82:Could not update switch"
#define SWITCH_ERROR_NR_83 "Error 83:Could not delete switch"
#define SWITCH_ERROR_NR_84 "Error 84:Could not toggle all switch"
#define SWITCH_ERROR_NR_85 "Error 85:Wrong word size for switch"
#define SWITCH_ERROR_NR_86 "Error 86:No switches available"

#define CHANGE_ERROR_NR_100 "Error 100:Action not found for change"
#define CHANGE_ERROR_NR_101 "Error 101:Wrong action parameter for change"

#define INFORMATION_ERROR_NR_110 "Error 110:Action not found for information"
#define INFORMATION_ERROR_NR_111 "Error 111:Wrong action parameter for information"

#define REMOTE_ERROR_NR_120 "Error 120:Action not found for remote"

#define TEMPERATURE_ERROR_NR_130 "Error 130:Action not found for temperature"
#define TEMPERATURE_ERROR_NR_132 "Error 132:Wrong action parameter for temperature"
#define TEMPERATURE_ERROR_NR_133 "Error 133:Invalid data for temperature"
#define TEMPERATURE_ERROR_NR_134 "Error 134:TemperatureService not initialized"

#define MAP_CONTENT_ERROR_NR_140 "Error 140:Could not add mapcontent"
#define MAP_CONTENT_ERROR_NR_141 "Error 141:Wrong word size for mapcontent"
#define MAP_CONTENT_ERROR_NR_142 "Error 142:Could not update mapcontent"
#define MAP_CONTENT_ERROR_NR_143 "Error 143:Could not delete mapcontent"
#define MAP_CONTENT_ERROR_NR_144 "Error 144:Action not found for mapcontent"
#define MAP_CONTENT_ERROR_NR_146 "Error 146:Wrong action parameter for mapcontent"

#define SHOPPING_ERROR_NR_150 "Error 150:Could not add shopping entry"
#define SHOPPING_ERROR_NR_151 "Error 151:Wrong word size for shopping entry"
#define SHOPPING_ERROR_NR_152 "Error 152:Could not update shopping entry"
#define SHOPPING_ERROR_NR_153 "Error 153:Could not delete shopping entry"
#define SHOPPING_ERROR_NR_154 "Error 154:Action not found action for shopping entry"
#define SHOPPING_ERROR_NR_156 "Error 156:Wrong action parameter for shopping entry"

#define MENU_ERROR_NR_160 "Error 160:Wrong word size for menu"
#define MENU_ERROR_NR_161 "Error 161:Could not update menu"
#define MENU_ERROR_NR_162 "Error 162:Could not clear menu"
#define MENU_ERROR_NR_163 "Error 163:Action not found for menu"
#define MENU_ERROR_NR_165 "Error 165:Invalid data for menu"
#define LISTED_MENU_ERROR_NR_166 "Error 166:Could not update listedmenu"
#define LISTED_MENU_ERROR_NR_167 "Error 167:Wrong word size for listedmenu"
#define LISTED_MENU_ERROR_NR_168 "Error 168:Could not delete listedmenu"
#define LISTED_MENU_ERROR_NR_169 "Error 169:Could not add listedmenu"

#define CAMERA_ERROR_NR_170 "Error 170:Action not found for camera"
#define CAMERA_ERROR_NR_171 "Error 171:Invalid data for camera"
#define CAMERA_ERROR_NR_172 "Error 172:Invalid data at index 5 for camera"
#define CAMERA_ERROR_NR_173 "Error 173:Camera motion already running"
#define CAMERA_ERROR_NR_174 "Error 174:Camera motion not running"

#define SYSTEM_ERROR_NR_180 "Error 180:Action not found for system"
#define SYSTEM_ERROR_NR_181 "Error 181:Invalid data for system"

#define METER_DATA_ERROR_NR_190 "Error 190:Wrong word size for meterdata"
#define METER_DATA_ERROR_NR_191 "Error 191:Could not add meterdata"
#define METER_DATA_ERROR_NR_192 "Error 192:Could not update meterdata"
#define METER_DATA_ERROR_NR_193 "Error 193:Could not delete meterdata"
#define METER_DATA_ERROR_NR_194 "Error 194:Action not found for meterdata"
#define METER_DATA_ERROR_NR_195 "Error 195:Invalid data for meterdata"
#define METER_DATA_ERROR_NR_196 "Error 196:Wrong action parameter for meterdata"

#define COIN_ERROR_NR_200 "Error 200:Action not found for coin"
#define COIN_ERROR_NR_201 "Error 201:Wrong data size for birthday"
#define COIN_ERROR_NR_202 "Error 202:Wrong action parameter for coin"
#define COIN_ERROR_NR_203 "Error 203:Could not add coin"
#define COIN_ERROR_NR_204 "Error 204:Could not update coin"
#define COIN_ERROR_NR_205 "Error 205:Could not delete coin"
#define COIN_ERROR_NR_207 "Error 207:Access permitted!User is no admin"

#define MONEY_METER_DATA_ERROR_NR_210 "Error 210:Wrong word size for moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_211 "Error 211:Could not add moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_212 "Error 212:Could not update moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_213 "Error 213:Could not delete moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_214 "Error 214:Action not found for moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_215 "Error 215:Invalid data for moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_216 "Error 216:Wrong action parameter for moneymeterdata"
#define MONEY_METER_DATA_ERROR_NR_218 "Error 218:Access permitted!User is no admin"

/***********************************************/
/************* COMMAND DEFINITIONS *************/
/***********************************************/

#define ACTIVATE "ACTIVATE"
#define ADD "ADD"
#define ALL "ALL"
#define AVAILABILITY "AVAILABILITY"
#define CHECK "CHECK"
#define CLEAR "CLEAR"
#define CONTROL "CONTROL"
#define COUNT "COUNT"
#define DATA "DATA"
#define DEACTIVATE "DEACTIVATE"
#define DELETE "DELETE"
#define FOR_USER "FOR_USER"
#define GET "GET"
#define INDEX "INDEX"
#define LOAD "LOAD"
#define MAIN "MAIN"
#define MOTION "MOTION"
#define PHP "PHP"
#define PLAY "PLAY"
#define RELOAD "RELOAD"
#define RESETFAILEDLOGIN "RESETFAILEDLOGIN"
#define SENSOR "SENSOR"
#define SET "SET"
#define SETCONTROLTASK "SETCONTROLTASK"
#define START "START"
#define STATE "STATE"
#define STOP "STOP"
#define SYSTEM "SYSTEM"
#define TOGGLE "TOGGLE"
#define UPDATE "UPDATE"
#define URL "URL"
#define VALIDATE "VALIDATE"

#define ON "ON"
#define OFF "OFF"
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"

#define MENU "MENU"
#define MENU_PHP "MENU_PHP"
#define LISTEDMENU "LISTEDMENU"
#define LISTEDMENU_PHP "LISTEDMENU_PHP"

#define CAMERA_EVENTS_MAX_COUNT 25
#define CAMERA_IMAGES_TO_SEND 10

#define MAIL_MAX_MESSAGE_LENGTH 2048

#define AREA "AREA"
#define BIRTHDAY "BIRTHDAY"
#define CAMERA "CAMERA"
#define CHANGE "CHANGE"
#define COINS "COINS"
#define GPIO "GPIO"
#define INFORMATION "INFORMATION"
#define MAPCONTENT "MAPCONTENT"
#define METERDATA "METERDATA"
#define MONEYMETERDATA "MONEYMETERDATA"
#define MOVIE "MOVIE"
#define RASPBERRY "RASPBERRY"
#define REMOTE "REMOTE"
#define SCHEDULE "SCHEDULE"
#define SHOPPINGLIST "SHOPPINGLIST"
#define SOCKET "SOCKET"
#define SWITCH "SWITCH"
#define SYSTEM "SYSTEM"
#define TEMPERATURE "TEMPERATURE"
#define USER "USER"

#define REBOOT "REBOOT"
#define SHUTDOWN "SHUTDOWN"

#define ACTION_LEVEL_ERROR -1
#define ACTION_LEVEL_LOW 1
#define ACTION_LEVEL_MEDIUM 2
#define ACTION_LEVEL_NORMAL 3
#define ACTION_LEVEL_CRIT 4
#define ACTION_LEVEL_SYSTEM 5

#define CMD_MIN_LENGTH 25
#define CMD_SOURCE_EXTERNAL 1
#define CMD_SOURCE_SCHEDULER 2

#define CMD_SUDO_MOTION "sudo motion"
#define CMD_SUDO_KILLALL_MOTION "sudo killall motion"
#define CMD_SUDO_REBOOT "sudo shutdown -r now"
#define CMD_SUDO_SHUTDOWN "sudo shutdown -h now"

#define CMD_SEND_SIMPLE_MAIL "python /etc/default/lucahome/mail.py"
#define CMD_SEND_IMAGE_MAIL "python /etc/default/lucahome/mailWithImage.py"

/***********************************************/
/************** INDEX DEFINITIONS **************/
/***********************************************/

#define USER_NAME_INDEX 0
#define PASSWORD_INDEX 1
#define CATEGORY_INDEX 2
#define ACTION_INDEX 3
#define ACTION_PARAMETER_INDEX 4

#define BIRTHDAY_ID_INDEX 4
#define BIRTHDAY_NAME_INDEX 5
#define BIRTHDAY_DAY_INDEX 6
#define BIRTHDAY_MONTH_INDEX 7
#define BIRTHDAY_YEAR_INDEX 8
#define BIRTHDAY_GROUP_INDEX 9
#define BIRTHDAY_REMINDME_INDEX 10
#define BIRTHDAY_DATA_SIZE 11

#define CAMERA_CMD_PARAMETER_INDEX 5

#define CHANGE_DATA_SIZE 5

#define COIN_ID_INDEX 4
#define COIN_NAME_INDEX 5
#define COIN_TYPE_INDEX 6
#define COIN_AMOUNT_INDEX 7
#define COIN_DATA_SIZE 8

#define GPIO_TYPE_ID_INDEX 5
#define GPIO_NAME_INDEX 6
#define GPIO_GPIO_INDEX 7
#define GPIO_STATE_INDEX 8
#define GPIO_DATA_SIZE 9
#define GPIO_SET_STATE_INDEX 6
#define GPIO_SET_SIZE 7

#define LISTEDMENU_ID_INDEX 5
#define LISTEDMENU_TITLE_INDEX 6
#define LISTEDMENU_DESCRIPTION_INDEX 7
#define LISTEDMENU_RATING_INDEX 8
#define LISTEDMENU_USE_COUNTER_INDEX 9
#define LISTEDMENU_DATA_SIZE 10

#define MAP_CONTENT_ID_INDEX 4
#define MAP_CONTENT_TYPE_INDEX 5
#define MAP_CONTENT_TYPE_ID_INDEX 6
#define MAP_CONTENT_COORDINATES_INDEX 7
#define MAP_CONTENT_COORDINATES_X_INDEX 0
#define MAP_CONTENT_COORDINATES_Y_INDEX 1
#define MAP_CONTENT_NAME_INDEX 8
#define MAP_CONTENT_SHORT_NAME_INDEX 9
#define MAP_CONTENT_AREA_INDEX 10
#define MAP_CONTENT_VISIBILITY_INDEX 11
#define MAP_CONTENT_DATA_SIZE 12

#define MENU_WEEKDAY_INDEX 5
#define MENU_DAY_INDEX 6
#define MENU_MONTH_INDEX 7
#define MENU_YEAR_INDEX 8
#define MENU_TITLE_INDEX 9
#define MENU_DESCRIPTION_INDEX 10
#define MENU_DATA_SIZE 11

#define METER_DATA_ID_INDEX 4
#define METER_DATA_TYPE_INDEX 5
#define METER_DATA_TYPE_ID_INDEX 6
#define METER_DATA_DAY_INDEX 7
#define METER_DATA_MONTH_INDEX 8
#define METER_DATA_YEAR_INDEX 9
#define METER_DATA_HOUR_INDEX 10
#define METER_DATA_MINUTE_INDEX 11
#define METER_DATA_METER_ID_INDEX 12
#define METER_DATA_AREA_INDEX 13
#define METER_DATA_VALUE_INDEX 14
#define METER_DATA_IMAGE_NAME_INDEX 15
#define METER_DATA_SIZE 16

#define MONEY_METER_DATA_ID_INDEX 4
#define MONEY_METER_DATA_TYPE_ID_INDEX 5
#define MONEY_METER_DATA_BANK_INDEX 6
#define MONEY_METER_DATA_PLAN_INDEX 7
#define MONEY_METER_DATA_AMOUNT_INDEX 8
#define MONEY_METER_DATA_UNIT_INDEX 9
#define MONEY_METER_DATA_DAY_INDEX 10
#define MONEY_METER_DATA_MONTH_INDEX 11
#define MONEY_METER_DATA_YEAR_INDEX 12
#define MONEY_METER_DATA_USER_INDEX 13
#define MONEY_METER_DATA_SIZE 14

#define MOVIE_DATA_ID_INDEX 4
#define MOVIE_DATA_TITLE_INDEX 5
#define MOVIE_DATA_GENRE_INDEX 6
#define MOVIE_DATA_DESCRIPTION_INDEX 7
#define MOVIE_DATA_RATING_INDEX 8
#define MOVIE_DATA_WATCHED_INDEX 9
#define MOVIE_DATA_SIZE 10
#define MOVIE_DATA_LOW_INDEX 5
#define MOVIE_DATA_HIGH_INDEX 6
#define MOVIE_DATA_ADDITIONAL_INDEX 7
#define MOVIE_DATA_INDEX_SIZE 8

#define REMOTE_PARAMETER_INDEX 5

#define SCHEDULE_ID_INDEX 5
#define SCHEDULE_NAME_INDEX 6
#define SCHEDULE_SOCKET_INDEX 7
#define SCHEDULE_GPIO_INDEX 8
#define SCHEDULE_SWITCH_INDEX 9
#define SCHEDULE_WEEKDAY_INDEX 10
#define SCHEDULE_HOUR_INDEX 11
#define SCHEDULE_MINUTE_INDEX 12
#define SCHEDULE_ACTION_INDEX 13
#define SCHEDULE_ISTIMER_INDEX 14
#define SCHEDULE_ISACTIVE_INDEX 15
#define SCHEDULE_DATA_SIZE 16
#define SCHEDULE_SET_STATE_INDEX 6
#define SCHEDULE_SET_SIZE 7

#define SHOPPING_ENTRY_ID_INDEX 4
#define SHOPPING_ENTRY_NAME_INDEX 5
#define SHOPPING_ENTRY_GROUP_INDEX 6
#define SHOPPING_ENTRY_QUANTITY_INDEX 7
#define SHOPPING_ENTRY_UNIT_INDEX 8
#define SHOPPING_ENTRY_DATA_SIZE 9

#define SOCKET_TYPE_ID_INDEX 5
#define SOCKET_NAME_INDEX 6
#define SOCKET_AREA_INDEX 7
#define SOCKET_CODE_INDEX 8
#define SOCKET_STATE_INDEX 9
#define SOCKET_DATA_SIZE 10
#define SOCKET_SET_STATE_INDEX 6
#define SOCKET_SET_SIZE 7

#define SWITCH_TYPE_ID_INDEX 5
#define SWITCH_NAME_INDEX 6
#define SWITCH_AREA_INDEX 7
#define SWITCH_REMOTE_ID_INDEX 8
#define SWITCH_KEYCODE_INDEX 9
#define SWITCH_DATA_SIZE 10
#define SWITCH_TOGGLE_SIZE 6

/***********************************************/
/************** TIMEOUT DEFINITIONS ************/
/***********************************************/

#define BIRTHDAY_CHECK_TIMEOUT 2 * 60 * 60
#define MOTION_CONTROL_TIMEOUT 15
#define SCHEDULE_CONTROL_TIMEOUT 10
#define TEMPERATURE_CONTROL_TIMEOUT 60
#define RELOAD_TIMEOUT 30 * 60

/***********************************************/
/*************** PATH DEFINITIONS **************/
/***********************************************/

#define NAS_PATH_CAMERA "/mnt/NAS/Camera/"
#define NAS_PATH_LUCAHOME "/mnt/NAS/LucaHome/"
#define NAS_PATH_METER_LOG "/mnt/NAS/MeterLog/"
#define NAS_PATH_MOVIE "/mnt/NAS/Movies/"
#define NAS_PATH_MUSIC "/mnt/NAS/Music/"
#define NAS_PATH_SERIES "/mnt/NAS/Series/"

/***********************************************/
/************* FILE PATH DEFINITIONS ***********/
/***********************************************/

#define BIRTHDAY_FILE "/etc/default/lucahome/birthdays"
#define CHANGE_FILE "/etc/default/lucahome/changes"
#define COIN_FILE "/etc/default/lucahome/coins"
#define INFORMATION_FILE "/etc/default/lucahome/infos"
#define MAP_CONTENT_FILE "/etc/default/lucahome/mapcontent"
#define MENU_FILE "/etc/default/lucahome/menu"
#define METERDATA_FILE "/etc/default/lucahome/meterdata"
#define MONEY_METERDATA_FILE "/etc/default/lucahome/moneymeterdata"
#define LISTED_MENU_FILE "/etc/default/lucahome/listedmenu"
#define SETTINGS_FILE "/etc/default/lucahome/settings"
#define SHOPPING_LIST_FILE "/etc/default/lucahome/shoppinglist"
#define TEMPERATURE_SETTINGS_FILE "/etc/default/lucahome/temperaturesettings"
#define USER_FILE "/etc/default/lucahome/users"

/***********************************************/
/**************** FILE DEFINITIONS *************/
/***********************************************/

#define IS_FOLDER 0x4
#define IS_FILE 0x8

#define JPG_ENDING ".jpg"
#define SWF_ENDING ".swf"

#define NFO_LUCA_FILE "NFO.luca"
