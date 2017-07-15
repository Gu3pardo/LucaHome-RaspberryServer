#include "ReceiverService.h"

/*===============PUBLIC==============*/

ReceiverService::ReceiverService() {
}

ReceiverService::~ReceiverService() {
}

std::string ReceiverService::PerformAction(int receivedValue) {
	//TODO add prober handling!

	std::stringstream out;
	out << "{ReceivedValue:" << Tools::ConvertIntToStr(receivedValue) << "};" << "\x00" << std::endl;
	return out.str();
}
