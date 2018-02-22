#include "SecurityService.h"

/*===============PUBLIC==============*/

SecurityService::SecurityService()
{
	_flagMotionStart = false;
	_flagMotionStop = false;
	_isMotionActive = false;
}

SecurityService::~SecurityService() {}

void SecurityService::Initialize(string motionUrl)
{
	_motionUrl = motionUrl;

	_mailController = MailController();
	_pathController = PathController();

	_motionEventList = _pathController.ScanCameraFolder();
	_sentMotionEventList = _motionEventList;
}

string SecurityService::PerformAction(vector<string> data)
{
	string actionParameter = data[ACTION_PARAMETER_INDEX];
	string action = data[ACTION_INDEX];

	if (actionParameter == MOTION) {
		if (action == START) {
			return startMotion();
		}
		else if (action == STOP) {
			return stopMotion();
		}
		else if (action == GET) {
			return getJsonString();
		}
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void SecurityService::Dispose()
{
	stopMotion();
}

void SecurityService::CheckMotionEvents()
{
	_motionEventList = _pathController.ScanCameraFolder();

	int motionEventCount = _motionEventList.size();
	int sendMotionEventCount = _sentMotionEventList.size();

	if (motionEventCount != sendMotionEventCount)
	{
		if (motionEventCount > sendMotionEventCount)
		{
			int difference = motionEventCount - sendMotionEventCount;
			int startIndex = 0;

			if (difference > MOTION_IMAGES_TO_SEND)
			{
				startIndex = motionEventCount - MOTION_IMAGES_TO_SEND;
			}

			for (int index = startIndex; index < motionEventCount; index++)
			{
				string currentMotionEventImage = _motionEventList[index];
				bool alreadySentImage = false;

				for (int controlIndex = 0; controlIndex < sendMotionEventCount; controlIndex++)
				{
					if (_sentMotionEventList[controlIndex] == currentMotionEventImage)
					{
						alreadySentImage = true;
						break;
					}
				}

				if (alreadySentImage)
				{
					continue;
				}

				stringstream imagePath;
				imagePath << "../../.." << NAS_PATH_CAMERA << currentMotionEventImage;
				MailController::SendMail(RECEIVER_MAIL, 1, imagePath.str());
			}
		}
	}

	_sentMotionEventList = _motionEventList;
}

bool SecurityService::GetFlagMotionStart()
{
	return _flagMotionStart;
}

bool SecurityService::GetFlagMotionStop()
{
	return _flagMotionStop;
}

void SecurityService::StartMotion()
{
	if (_isMotionActive)
	{
		return;
	}

	_isMotionActive = true;
	Tools::SendSystemCommandGetResult(CMD_SUDO_MOTION);
}

void SecurityService::StopMotion()
{
	if (!_isMotionActive)
	{
		return;
	}

	_isMotionActive = false;
	Tools::SendSystemCommandGetResult(CMD_SUDO_KILLALL_MOTION);
}

/*==============PRIVATE==============*/

string SecurityService::startMotion()
{
	if (_isMotionActive)
	{
		return SECURITY_ERROR_MOTION_IS_RUNNING;
	}

	_flagMotionStart = true;
	_flagMotionStop = false;

	return SECURITY_START_MOTION_SUCCESS;
}

string SecurityService::stopMotion()
{
	if (!_isMotionActive)
	{
		return SECURITY_ERROR_MOTION_NOT_RUNNING;
	}

	_flagMotionStart = false;
	_flagMotionStop = true;

	return SECURITY_STOP_MOTION_SUCCESS;
}

string SecurityService::getJsonString()
{
	stringstream out;
	out << "{"
		<< "\"Motion\":"
		<< "{"
		<< "\"Active\":" << (_isMotionActive ? "\"ON\"" : "\"OFF\"") << ","
		<< "\"TaskActive\":" << "\"ON\"" << ","
		<< "\"URL\":\"" << _motionUrl << "\","
		<< "\"Events\":" << getMotionEventsJsonString()
		<< "}"
		<< "}";

	return out.str();
}

string SecurityService::getMotionEventsJsonString()
{
	_motionEventList = _pathController.ScanCameraFolder();

	int maxEventCount = MOTION_EVENTS_MAX_COUNT;
	int motionEventCount = _motionEventList.size();

	int startIndex = 0;
	if (motionEventCount > maxEventCount)
	{
		startIndex = motionEventCount - maxEventCount;
	}

	stringstream data;
	for (int index = startIndex; index < motionEventCount; index++)
	{
		string motionEventString =
			string("{")
			+ string("\"Event\":")
			+ string("{")
			+ string("\"FileName\":\"") + _motionEventList[index] + string("\"")
			+ string("}")
			+ string("}");
		data << motionEventString << ",";
	}

	stringstream out;
	out << "[" << data.str().substr(0, data.str().size() - 1) << "]";
	return out.str();
}