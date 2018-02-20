#include "WirelessSchedule.h"

#ifndef WIRELESS_TIMER_H
#define WIRELESS_TIMER_H

class WirelessTimer : public WirelessSchedule
{
public:
	WirelessTimer();
	WirelessTimer(string, string, int, int, int, string, bool, string, bool, string);
	virtual ~WirelessTimer();

	virtual string JsonString();
	virtual string ToString();
};

#endif
