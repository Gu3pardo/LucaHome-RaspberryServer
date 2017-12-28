#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef SCHEDULE_DTO_H
#define SCHEDULE_DTO_H

class ScheduleDto
{
  private:

	  int _id;
	  std::string _name;
	  std::string _socket;
	  std::string _gpio;
	  std::string _switch;
	  int _weekday;
	  int _hour;
	  int _minute;
	  bool _action;
	  bool _isTimer;
	  bool _isActive;

  public:
	ScheduleDto();
	ScheduleDto(int, std::string, std::string, std::string, std::string, int, int, int, bool, bool, bool);
	~ScheduleDto();

	void SetId(int);
	int GetId();

	void SetName(std::string);
	std::string GetName();

	void SetSocket(std::string);
	std::string GetSocket();

	void SetGpio(std::string);
	std::string GetGpio();

	void SetSwitch(std::string);
	std::string GetSwitch();

	void SetWeekday(int);
	int GetWeekday();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetAction(bool);
	bool GetAction();

	void SetIsTimer(bool);
	bool GetIsTimer();

	void SetIsActive(bool);
	bool GetIsActive();

	std::string SaveString();
	std::string JsonString();
	std::string ToString();
};

#endif