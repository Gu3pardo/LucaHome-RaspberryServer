<?php

/* ===================================================== */
/* =================== DEFINITIONS ===================== */
/* ===================================================== */

define ( 'LUCAHOMEPORT', 6677 );

define ( 'MEDIA_SERVER_ERROR_PARAM', "Error 215:Parameter not found for mediaserver");

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
	/* ------------------- MediaServer -------------------- */
	case 'get':
		echo Send ( "$login::MEDIASERVER::GET::ALL" );
		break;
	case 'add':
		$uuid = Get ( 'uuid' );
		$roomUuid = Get ( 'roomUuid' );
		$ip = Get ( 'ip' );
		$isSleepingServer = Get ( 'isSleepingServer' );
		$wirelessSocketUuid = Get ( 'wirelessSocketUuid' );
		if ($uuid != '' && $roomUuid != '' && $ip != '' && $isSleepingServer != '' && $wirelessSocketUuid != '') {
			echo Send ( "$login::MEDIASERVER::ADD::$uuid::$roomUuid::$ip::$isSleepingServer::$wirelessSocketUuid" );
		} else {
			echo MEDIA_SERVER_ERROR_PARAM;
		}
		break;
	case 'update':
		$uuid = Get ( 'uuid' );
		$roomUuid = Get ( 'roomUuid' );
		$ip = Get ( 'ip' );
		$isSleepingServer = Get ( 'isSleepingServer' );
		$wirelessSocketUuid = Get ( 'wirelessSocketUuid' );
		if ($uuid != '' && $roomUuid != '' && $ip != '' && $isSleepingServer != '' && $wirelessSocketUuid != '') {
			echo Send ( "$login::MEDIASERVER::UPDATE::$uuid::$roomUuid::$ip::$isSleepingServer::$wirelessSocketUuid" );
		} else {
			echo MEDIA_SERVER_ERROR_PARAM;
		}
		break;
	case 'delete':
		$uuid = Get ( 'uuid' );
		if ($uuid != '') {
			echo Send ( "$login::MEDIASERVER::DELETE::$uuid" );
		} else {
			echo MEDIA_SERVER_ERROR_PARAM;
		}
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
	if ($var === null){
		$type = 'NULL';
	}
	else if (is_bool ( $var )){
		$type = 'BOOL';
	}
	else if (is_string ( $var )){
		$type = 'STRING[' . strlen ( $var ) . ']';
	}
	else if (is_int ( $var )){
		$type = 'INT';
	}
	else if (is_float ( $var )){
		$type = 'FLOAT';
	}
	else if (is_array ( $var )){
		$type = 'ARRAY[' . count ( $var ) . ']';
	}
	else if (is_object ( $var )){
		$type = 'OBJECT';
	}
	else if (is_resource ( $var )){
		$type = 'RESOURCE';
	}
	else{
		$type = '???';
	}

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
