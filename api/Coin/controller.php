<?php

/* ===================================================== */
/* =================== DEFINITIONS ===================== */
/* ===================================================== */

define ( 'LUCAHOMEPORT', 6677 );

define ( 'COIN_ERROR_PARAM', "Error 175:Parameter not found for coin");

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
	/* ------------------- Coin -------------------- */
	case 'getAll' :
		echo Send ( "$login::COINS::GET::ALL" );
		break;
	case 'getUser' :
		echo Send ( "$login::COINS::GET::FOR_USER" );
		break;
	case 'add' :
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
	case 'update' :
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
	case 'delete' :
		$uuid = Get ( 'uuid' );
		if ($uuid != '') {
			echo Send ( "$login::COINS::DELETE::$uuid" );
		} else {
			echo COIN_ERROR_PARAM;
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
