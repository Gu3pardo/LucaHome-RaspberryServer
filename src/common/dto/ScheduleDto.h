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
	std::string _name;
	std::string _socket;
	std::string _gpio;
	int _weekday;
	int _hour;
	int _minute;
	int _onoff;
	bool _isTimer;
	int _playSound;
	int _playRaspberry;
	int _status;

  public:
	ScheduleDto();
	ScheduleDto(std::string, std::string, std::string, int, int, int, int, int, int, int, int);
	~ScheduleDto();

	void SetName(std::string);
	std::string GetName();

	void SetSocket(std::string);
	std::string GetSocket();

	void SetGpio(std::string);
	std::string GetGpio();

	void SetWeekday(int);
	int GetWeekday();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetOnoff(int);
	int GetOnoff();

	void SetIsTimer(int);
	int GetIsTimer();

	void SetPlaySound(int);
	int GetPlaySound();

	void SetPlayRaspberry(int);
	int GetPlayRaspberry();

	bool SetStatus(int);
	int GetStatus();

	std::string ToString();
};

#endif