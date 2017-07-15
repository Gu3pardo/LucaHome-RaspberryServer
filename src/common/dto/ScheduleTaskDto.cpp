#include "ScheduleTaskDto.h"

ScheduleTaskDto::ScheduleTaskDto()
{
	_done = 0;
}

ScheduleTaskDto::ScheduleTaskDto(std::string schedule, time_t time, int weekday)
{
	_schedule = schedule;
	memcpy(&_time, &time, sizeof(time_t));
	_weekday = weekday;
	_done = 0;
}

ScheduleTaskDto::~ScheduleTaskDto()
{
}

void ScheduleTaskDto::SetSchedule(std::string schedule)
{
	_schedule = schedule;
}

std::string ScheduleTaskDto::GetSchedule()
{
	return _schedule;
}

void ScheduleTaskDto::SetTime(time_t time)
{
	_time = time;
}

time_t ScheduleTaskDto::GetTime()
{
	return _time;
}

void ScheduleTaskDto::SetWeekday(int weekday)
{
	_weekday = weekday;
}

int ScheduleTaskDto::GetWeekday()
{
	return _weekday;
}

void ScheduleTaskDto::SetDone(int done)
{
	_done = done;
}

int ScheduleTaskDto::IsDone()
{
	return _done;
}

std::string ScheduleTaskDto::ToString()
{
	std::string str =
		std::string("ScheduleTaskDto { name: ") + _schedule +
		std::string("; weekday: ") + Tools::ConvertIntToStr(_weekday) +
		std::string("; time: ") + ctime(&_time) +
		std::string("; done: ") + Tools::ConvertIntToStr(_done) +
		std::string(" }");
	return str;
}
