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
#include <syslog.h>

#include "../authentification/user.h"
#include "../controller/filecontroller.h"
#include "../mail/mailservice.h"

#ifndef ACCESSCONTROLSERVICE_H
#define ACCESSCONTROLSERVICE_H

class AccessControlService {
private:
	int _loginTries;

	User _accessUser;

	bool _accessControlActive;

	std::string _accessControlIp;
	std::vector<std::string> _mediaMirrorIps;

	FileController _fileController;
	MailService _mailService;

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

	void initialize(FileController, MailService, User, std::string,
			std::vector<std::string>);

	std::string activateAlarm();
	std::string checkCode(std::string);
	void doorOpened();
	std::string playAlarm();
	std::string stopAlarm();
};

#endif
