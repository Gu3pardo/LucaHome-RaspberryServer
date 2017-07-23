#include "AccessControlService.h"

/*===============PUBLIC==============*/

AccessControlService::AccessControlService() {
}

AccessControlService::~AccessControlService() {
}

void AccessControlService::Initialize(FileController fileController, MailController mailController, UserDto accessUser, std::string accessControlIp, std::vector<std::string> mediaMirrorIps) {
	_fileController = fileController;
	_mailController = mailController;

	_accessUser = accessUser;

	_loginTries = 0;

	_accessControlActive = false;

	_accessControlIp = accessControlIp;
	_mediaMirrorIps = mediaMirrorIps;
}

std::string AccessControlService::ActivateAlarm() {
	if (_accessControlActive) {
		return "alarmAlreadyRunning";
	}

	_accessControlActive = true;
	accessControlAccessControlActive();

	return "alarmActivated";
}

std::string AccessControlService::CheckCode(std::string code) {
	if (_accessUser.GetPassword() == code) {
		_accessControlActive = false;
		_loginTries = 0;
		accessControlLoginSuccessful();
		return "codeValid";
	}
	else {
		_loginTries++;
		accessControlLoginFailed();
		return "codeInvalid";
	}
}

void AccessControlService::DoorOpened() {
	if (_accessControlActive) {
		accessControlRequestCode();
	}
}

std::string AccessControlService::PlayAlarm() {
	mediaMirrorPlayAlarmSound();
	playAlarmSound();
	return "playingAlarmSound";
}

std::string AccessControlService::StopAlarm() {
	mediaMirrorStopAlarmSound();
	stopAlarmSound();
	return "stoppedPlayingAlarmSound";
}

/*==============PRIVATE==============*/

void AccessControlService::accessControlRequestCode() {
	sendMessageToServer(_accessControlIp, 8080, "ACTION:REQUEST_CODE");
}

void AccessControlService::accessControlAccessControlActive() {
	sendMessageToServer(_accessControlIp, 8080,
		"ACTION:ACTIVATE_ACCESS_CONTROL");
}

void AccessControlService::accessControlLoginSuccessful() {
	sendMessageToServer(_accessControlIp, 8080, "ACTION:LOGIN_SUCCESS");
}

void AccessControlService::accessControlLoginFailed() {
	sendMessageToServer(_accessControlIp, 8080, "ACTION:LOGIN_FAILED");
	if (_loginTries >= 5) {
		mediaMirrorPlayAlarmSound();
		playAlarmSound();
		_mailController.SendMail("User entered 5 times a wrong code!");
		sendMessageToServer(_accessControlIp, 8080, "ACTION:ALARM_ACTIVE");
	}
}

void AccessControlService::mediaMirrorPlayAlarmSound() {
	for (int index = 0; index < _mediaMirrorIps.size(); index++) {
		sendMessageToServer(_mediaMirrorIps[index], 8080,
			"ACTION:PLAY_ALARM&DATA:");
	}
}

void AccessControlService::mediaMirrorStopAlarmSound() {
	for (int index = 0; index < _mediaMirrorIps.size(); index++) {
		sendMessageToServer(_mediaMirrorIps[index], 8080,
			"ACTION:STOP_ALARM&DATA:");
	}
}

void AccessControlService::playAlarmSound() {
	sendMessageToServer("127.0.0.1", 6677, "Scheduler:435435:SOUND:PLAY:ALARM");
}

void AccessControlService::stopAlarmSound() {
	sendMessageToServer("127.0.0.1", 6677, "Scheduler:435435:SOUND:STOP:ALARM");
}

void AccessControlService::createCountdown() {
	// TODO
}

void AccessControlService::sendMessageToServer(std::string ip, int port,
	std::string messageString) {
	if (ip.length() < 13) {
		return;
	}

	int serverSocket;
	struct sockaddr_in server;
	const char *message = messageString.c_str();

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		//Error Could not create socket
		return;
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(ip.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(serverSocket, (struct sockaddr *) &server, sizeof(server))
		< 0) {
		//connect failed. Error
		return;
	}

	if (send(serverSocket, message, strlen(message), 0) < 0) {
		//Error Send failed
	}

	close(serverSocket);
}
