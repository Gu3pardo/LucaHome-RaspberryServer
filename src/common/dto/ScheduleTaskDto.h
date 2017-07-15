#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef SCHEDULETASK_DTO_H
#define SCHEDULETASK_DTO_H

class ScheduleTaskDto
{
  private:
	std::string _schedule;
	time_t _time;
	int _weekday;
	int _done;
	int _active;

  public:
	ScheduleTaskDto();
	ScheduleTaskDto(std::string, time_t, int);
	~ScheduleTaskDto();

	void SetSchedule(std::string);
	std::string GetSchedule();

	void SetTime(time_t);
	time_t GetTime();

	void SetWeekday(int);
	int GetWeekday();

	void SetDone(int);
	int IsDone();

	std::string ToString();
};

#endif
