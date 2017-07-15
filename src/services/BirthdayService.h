#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#include "../common/dto/BirthdayDto.h"
#include "../common/utils/Tools.h"
#include "../controller/FileController.h"
#include "../controller/MailController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#define GET "GET"
#define ADD "ADD"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define BIRTHDAY_DATA_SIZE 9
#define SETCONTROLTASK "SETCONTROLTASK"
#define ON "ON"
#define OFF "OFF"
#define ID_INDEX 4
#define NAME_INDEX 5
#define DAY_INDEX 6
#define MONTH_INDEX 7
#define YEAR_INDEX 8

#ifndef BIRTHDAYSERVICE_H
#define BIRTHDAYSERVICE_H

class BirthdayService
{
  private:
	std::string _birthdayFile;
	std::vector<BirthdayDto> _birthdayList;

	bool _birthdayControlActive;

	FileController _fileController;
	MailController _mailController;
	XmlService _xmlService;

	void loadBirthdays();
	void saveBirthdays(ChangeService, std::string);

	std::string getBirthdays();

	bool addBirthday(std::vector<std::string>, ChangeService, std::string);
	bool updateBirthday(std::vector<std::string>, ChangeService, std::string);
	bool deleteBirthday(int, ChangeService, std::string);

  public:
	BirthdayService();
	~BirthdayService();

	void Initialize(FileController, MailController);
	void CheckBirthdayList();
	void ReloadBirthdayList();

	std::string PerformAction(std::string, std::vector<std::string>, ChangeService, std::string);

	bool GetBirthdayControlActive();
};

#endif
