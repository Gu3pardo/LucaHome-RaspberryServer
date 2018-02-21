<?php

/* ===================================================== */
/* =================== DEFINITIONS ===================== */
/* ===================================================== */

define ( 'LUCAHOMEPORT', 6677 );

define ( 'AUTHENTIFICATION_ERROR_PARAM', "Error 15:Parameter not found for authentification");
define ( 'APPLICATION_INFORMATION_ERROR_PARAM', "Error 265:Parameter not found for application information");
define ( 'CHANGE_ERROR_PARAM', "Error 275:Parameter not found for change");
define ( 'COIN_ERROR_PARAM', "Error 175:Parameter not found for coin");
define ( 'CONTACT_ERROR_PARAM', "Error 35:Parameter not found for contact");
define ( 'GPIO_ERROR_PARAM', "Error 295:Parameter not found for gpio");
define ( 'MAP_CONTENT_ERROR_PARAM', "Error 105:Parameter not found for mapcontent");
define ( 'MEAL_ERROR_PARAM', "Error 135:Parameter not found for meal");
define ( 'MEDIA_SERVER_ERROR_PARAM', "Error 215:Parameter not found for mediaserver");
define ( 'METER_LOG_ITEM_ERROR_PARAM', "Error 155:Parameter not found for meter log item");
define ( 'MONEY_LOG_ITEM_ERROR_PARAM', "Error 185:Parameter not found for money log item");
define ( 'MOVIE_ERROR_PARAM', "Error 45:Parameter not found for movie");
define ( 'PUCK_JS_ERROR_PARAM', "Error 195:Parameter not found for puckjs");
define ( 'RADIO_STREAM_ERROR_PARAM', "Error 235:Parameter not found for radio stream");
define ( 'ROOM_ERROR_PARAM', "Error 205:Parameter not found for room");
define ( 'RSS_FEED_ERROR_PARAM', "Error 245:Parameter not found for rss feed");
define ( 'SECURITY_ERROR_PARAM', "Error 155:Parameter not found for security");
define ( 'SHOPPING_ITEM_ERROR_PARAM', "Error 115:Parameter not found for shopping item");
define ( 'SUGGESTED_MEAL_ERROR_PARAM', "Error 145:Parameter not found for suggested meal");
define ( 'SUGGESTED_SHOPPING_ITEM_ERROR_PARAM', "Error 125:Parameter not found for suggested shopping item");
define ( 'TEMPERATURE_ERROR_PARAM', "Error 95:Parameter not found for temperature");
define ( 'USER_ERROR_PARAM', "Error 255:Parameter not found for user");
define ( 'WIRELESS_SCHEDULE_ERROR_PARAM', "Error 65:Parameter not found for wireless schedule");
define ( 'WIRELESS_SOCKET_ERROR_PARAM', "Error 75:Parameter not found for wireless socket");
define ( 'WIRELESS_SWITCH_ERROR_PARAM', "Error 85:Parameter not found for wireless switch");
define ( 'YOUTUBE_VIDEO_ERROR_PARAM', "Error 225:Parameter not found for youtube video");

/* ===================================================== */
/* ================= MAIN API METHOD =================== */
/* ===================================================== */

$user = Get ( 'user' );
$password = Get ( 'password' );
$action = Get ( 'action' );

if ($user == '' || $password == '' || $action == '') {
	echo AUTHENTIFICATION_ERROR_PARAM;
	return;
}

$login = "$user::$password";

switch ($action) {
	/* ------------------- ApplicationInformation -------------------- */
	case 'getApplicationInformation':
		echo Send ( "$login::APPLICATIONINFORMATION::GET::ALL" );
		break;
	case 'addApplicationInformation':
		$key = Get ( 'key' );
		$value = Get ( 'value' );
		if ($key != '' && $value != '') {
			echo Send ( "$login::APPLICATIONINFORMATION::ADD::$key::$value" );
		} else {
			echo APPLICATION_INFORMATION_ERROR_PARAM;
		}
		break;
	case 'updateApplicationInformation':
		$key = Get ( 'key' );
		$value = Get ( 'value' );
		if ($key != '' && $value != '') {
			echo Send ( "$login::APPLICATIONINFORMATION::UPDATE::$key::$value" );
		} else {
			echo APPLICATION_INFORMATION_ERROR_PARAM;
		}
		break;
	case 'deleteApplicationInformation':
		$key = Get ( 'key' );
		if ($key != '') {
			echo Send ( "$login::APPLICATIONINFORMATION::DELETE::$key" );
		} else {
			echo APPLICATION_INFORMATION_ERROR_PARAM;
		}
		break;
		
	/* ------------------- Change -------------------- */
	case 'getChange':
		echo Send ( "$login::CHANGE::GET::ALL" );
		break;
		
	/* ------------------- Coin -------------------- */
	case 'getCoinsAll' :
		echo Send ( "$login::COINS::GET::ALL" );
		break;
	case 'getCoinsUser' :
		echo Send ( "$login::COINS::GET::FOR_USER" );
		break;
	case 'addCoin' :
		$uuid = Get ( 'uuid' );
		$useruuid = Get ( 'useruuid' );
		$type = Get ( 'type' );
		$amount = Get ( 'amount' );
		if ($uuid != '' && $useruuid != '' && $type != '' && $amount != '') {
			echo Send ( "$login::COINS::ADD::$uuid::$useruuid::$type::$amount" );
		} else {
			echo COIN_ERROR_PARAM;
		}
		break;
	case 'updateCoin' :
		$uuid = Get ( 'uuid' );
		$useruuid = Get ( 'useruuid' );
		$type = Get ( 'type' );
		$amount = Get ( 'amount' );
		if ($uuid != '' && $useruuid != '' && $type != '' && $amount != '') {
			echo Send ( "$login::COINS::UPDATE::$uuid::$useruuid::$type::$amount" );
		} else {
			echo COIN_ERROR_PARAM;
		}
		break;
	case 'deleteCoin' :
		$uuid = Get ( 'uuid' );
		if ($uuid != '') {
			echo Send ( "$login::COINS::DELETE::$uuid" );
		} else {
			echo COIN_ERROR_PARAM;
		}
		break;
		
	/* ------------------- Contact -------------------- */
	case 'getContact':
		echo Send ( "$login::CONTACT::GET::ALL" );
		break;
	case 'addContact':
		$uuid = Get ( 'uuid' );
		$name = Get ( 'name' );
		$group = Get ( 'group' );
		$address = Get ( 'address' );
		$phoneHome = Get ( 'phoneHome' );
		$phoneMobile = Get ( 'phoneMobile' );
		$email = Get ( 'email' );
		$birthdayDay = Get ( 'birthdayDay' );
		$birthdayMonth = Get ( 'birthdayMonth' );
		$birthdayYear = Get ( 'birthdayYear' );
		$birthdayRemindMe = Get ( 'birthdayRemindMe' );
		if ($uuid != '' && $name != '' && $group != '' && $address != '' && $phoneHome != '' && $phoneMobile != '' && $email != '' && $birthdayDay != '' && $birthdayMonth != '' && $birthdayYear != '' && $birthdayRemindMe != '') {
			echo Send ( "$login::CONTACT::ADD::$uuid::$name::$group::$address::$phoneHome::$phoneMobile::$email::$birthdayDay::$birthdayMonth::$birthdayYear::$birthdayRemindMe" );
		} else {
			echo CONTACT_ERROR_PARAM;
		}
		break;
	case 'updateContact':
		$uuid = Get ( 'uuid' );
		$name = Get ( 'name' );
		$group = Get ( 'group' );
		$address = Get ( 'address' );
		$phoneHome = Get ( 'phoneHome' );
		$phoneMobile = Get ( 'phoneMobile' );
		$email = Get ( 'email' );
		$birthdayDay = Get ( 'birthdayDay' );
		$birthdayMonth = Get ( 'birthdayMonth' );
		$birthdayYear = Get ( 'birthdayYear' );
		$birthdayRemindMe = Get ( 'birthdayRemindMe' );
		if ($uuid != '' && $name != '' && $group != '' && $address != '' && $phoneHome != '' && $phoneMobile != '' && $email != '' && $birthdayDay != '' && $birthdayMonth != '' && $birthdayYear != '' && $birthdayRemindMe != '') {
			echo Send ( "$login::CONTACT::UPDATE::$uuid::$name::$group::$address::$phoneHome::$phoneMobile::$email::$birthdayDay::$birthdayMonth::$birthdayYear::$birthdayRemindMe" );
		} else {
			echo CONTACT_ERROR_PARAM;
		}
		break;
		break;
	case 'deleteContact':
		$uuid = Get ( 'uuid' );
		if ($uuid != '') {
			echo Send ( "$login::CONTACT::DELETE::$uuid" );
		} else {
			echo CONTACT_ERROR_PARAM;
		}
		break;
	case 'mailContact':
		$uuid = Get ( 'uuid' );
		$message = Get ( 'message' );
		if ($uuid != '' && $message != '') {
			echo Send ( "$login::CONTACT::MAIL::$uuid::$message" );
		} else {
			echo CONTACT_ERROR_PARAM;
		}
		break;
		
	/* ------------------- Gpio -------------------- */
	case 'getGpio' :
		echo Send ( "$login::GPIO::GET::ALL" );
		break;
	case 'addGpio' :
		$uuid = Get ( 'uuid' );
		$name = Get ( 'name' );
		$pin = Get ( 'pin' );
		$state = Get ( 'state' );
		if ($uuid != '' && $name != '' && $pin != '' && $state != '') {
			echo Send ( "$login::GPIO::ADD::$uuid::$name::$pin::$state" );
		} else {
			echo GPIO_ERROR_PARAM;
		}
		break;
	case 'updateGpio' :
		$uuid = Get ( 'uuid' );
		$name = Get ( 'name' );
		$pin = Get ( 'pin' );
		$state = Get ( 'state' );
		if ($uuid != '' && $name != '' && $pin != '' && $state != '') {
			echo Send ( "$login::GPIO::UPDATE::$uuid::$name::$pin::$state" );
		} else {
			echo GPIO_ERROR_PARAM;
		}
		break;
	case 'deleteGpio' :
		$uuid = Get ( 'uuid' );
		if ($uuid != '') {
			echo Send ( "$login::GPIO::DELETE::$uuid" );
		} else {
			echo GPIO_ERROR_PARAM;
		}
		break;
	case 'setGpio' :
		$uuid = Get ( 'uuid' );
		$state = Get ( 'state' );
		if ($uuid != '' && $state != '') {
			echo Send ( "$login::GPIO::SET::$gpio::$state" );
		} else {
			echo GPIO_ERROR_PARAM;
		}
		break;
		
	/* ------------------- MapContent -------------------- */
	case 'MapContent':
		break;
		
	/* ------------------- Meal -------------------- */
	case 'Meal':
		break;
		
	/* ------------------- MediaServer -------------------- */
	case 'MediaServer':
		break;
		
	/* ------------------- MeterLog -------------------- */
	case 'MeterLog':
		break;
		
	/* ------------------- MoneyLog -------------------- */
	case 'MoneyLog':
		break;
		
	/* ------------------- Movie -------------------- */
	case 'Movie':
		break;
		
	/* ------------------- PuckJs -------------------- */
	case 'PuckJs':
		break;
		
	/* ------------------- RadioStream -------------------- */
	case 'RadioStream':
		break;
		
	/* ------------------- Room -------------------- */
	case 'Room':
		break;
		
	/* ------------------- RssFeed -------------------- */
	case 'RssFeed':
		break;
		
	/* ------------------- ShoppingItem -------------------- */
	case 'ShoppingItem':
		break;
		
	/* ------------------- SuggestedMeal -------------------- */
	case 'SuggestedMeal':
		break;
		
	/* ------------------- SuggestedShoppingItem -------------------- */
	case 'SuggestedShoppingItem':
		break;
		
	/* ------------------- Temperature -------------------- */
	case 'Temperature':
		break;
		
	/* ------------------- User -------------------- */
	case 'User':
		break;
		
	/* ------------------- WirelessSchedule -------------------- */
	case 'WirelessSchedule':
		break;
		
	/* ------------------- WirelessSocket -------------------- */
	case 'WirelessSocket':
		break;
		
	/* ------------------- WirelessSwitch -------------------- */
	case 'WirelessSwitch':
		break;
		
	/* ------------------- WirelessTimer -------------------- */
	case 'WirelessTimer':
		break;
		
	/* ------------------- YoutubeVideo -------------------- */
	case 'YoutubeVideo':
		break;

	/* --------------------- Default ------------------- */
	default :
		var2console ( "Warning: " );
		var2console ( $action );
		break;
}

/* ===================================================== */
/* ================== HELPER METHODS =================== */
/* ===================================================== */
function Get($val) {
	if (isset ( $_GET [$val] )){
		return $_GET [$val];
	}
}

function Send($data) {
	$socket = fsockopen ( 'udp://127.0.0.1', LUCAHOMEPORT, $errno, $errstr, 10 );
	$out = "";
	if (! $socket) {
		var2console ( "SocketError" );
		echo "$errstr ($errno)";
		exit ();
	} else {
		fwrite ( $socket, "$data" );
		$out = fread ( $socket, 65536 );
		fclose ( $socket );
	}
	return $out;
}

/* ===================================================== */
/* ====================== LOGGER ======================= */
/* ===================================================== */

function var2console($var, $name = '', $now = false) {
	if ($var === null)
		$type = 'NULL';
	else if (is_bool ( $var ))
		$type = 'BOOL';
	else if (is_string ( $var ))
		$type = 'STRING[' . strlen ( $var ) . ']';
	else if (is_int ( $var ))
		$type = 'INT';
	else if (is_float ( $var ))
		$type = 'FLOAT';
	else if (is_array ( $var ))
		$type = 'ARRAY[' . count ( $var ) . ']';
	else if (is_object ( $var ))
		$type = 'OBJECT';
	else if (is_resource ( $var ))
		$type = 'RESOURCE';
	else
		$type = '???';
	if (strlen ( $name )) {
		str2console ( "$type $name = " . var_export ( $var, true ) . ';', $now );
	} else {
		str2console ( "$type = " . var_export ( $var, true ) . ';', $now );
	}
}
function str2console($str, $now = false) {
	if ($now) {
		echo "<script type='text/javascript'>\n";
		echo "//<![CDATA[\n";
		echo "console.log(", json_encode ( $str ), ");\n";
		echo "//]]>\n";
		echo "</script>";
	} else {
		register_shutdown_function ( 'str2console', $str, true );
	}
}

?>
