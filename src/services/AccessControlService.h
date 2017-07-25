#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/dto/UserDto.h"
#include "../controller/FileController.h"
#include "../controller/MailController.h"

#ifndef ACCESSCONTROLSERVICE_H
#define ACCESSCONTROLSERVICE_H

class AccessControlService {
private:
	int _loginTries;

	UserDto _accessUser;

	bool _accessControlActive;

	std::string _accessControlIp;
	std::vector<std::string> _mediaMirrorIps;

	FileController _fileController;
	MailController _mailController;

	void accessControlRequestCode();
	void accessControlAccessControlActive();
	void accessControlLoginSuccessful();
	void accessControlLoginFailed();

	void mediaMirrorPlayAlarmSound();
	void mediaMirrorStopAlarmSound();

	void playAlarmSound();
	void stopAlarmSound();

	void sendMessageToServer(std::string, int, std::string);

	void createCountdown();

public:
	AccessControlService();
	~AccessControlService();

	void Initialize(FileController, MailController, UserDto, std::string, std::vector<std::string>);

	std::string ActivateAlarm();
	std::string CheckCode(std::string);
	void DoorOpened();
	std::string PlayAlarm();
	std::string StopAlarm();
};

#endif
