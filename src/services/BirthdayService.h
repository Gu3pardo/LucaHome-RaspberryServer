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

#include "../common/dto/BirthdayDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "../controller/MailController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

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

	void saveBirthdays(ChangeService, std::string);

	std::string getJsonString();
	std::string getPhpString();

	bool addBirthday(std::vector<std::string>, ChangeService, std::string);
	bool updateBirthday(std::vector<std::string>, ChangeService, std::string);
	bool deleteBirthday(int, ChangeService, std::string);

  public:
	BirthdayService();
	~BirthdayService();

	void Initialize(FileController, MailController, std::string);
	void CheckBirthdayList();
	void LoadData();

	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);

	bool GetBirthdayControlActive();
};

#endif
