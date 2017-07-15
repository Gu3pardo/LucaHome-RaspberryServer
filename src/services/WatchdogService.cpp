#include "WatchdogService.h"

WatchdogService::WatchdogService() {
	_count = -1;
}

WatchdogService::~WatchdogService() {
}

//--------------------------Public-----------------------//

std::string WatchdogService::PerformAction(std::string action, std::vector<std::string> data) {
	if (action == COUNT) {
		if (data[4] == CHECK) {
			int newCount = atoi(data[5].c_str());
			if (newCount != _count) {
				_count = newCount;
				return std::string("watchdog:count:ok:") + Tools::ConvertIntToStr(_count);
			}
			else {
				return std::string("watchdog:count:error:") + Tools::ConvertIntToStr(_count);
			}
		}
		else {
			return "Error 191:Invalid data for watchdog";
		}
	}
	else if (action == AVAILABILITY) {
		return "server:available:1";
	}

	return "Error 190:Action not found for watchdog";
}
