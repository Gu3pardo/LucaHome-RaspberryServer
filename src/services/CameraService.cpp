#include "CameraService.h"

CameraService::CameraService()
{
	_isMotionRunning = false;

	_startCamera = false;
	_stopCamera = false;

	_motionControlActive = false;
}

CameraService::~CameraService()
{
}

//--------------------------Public-----------------------//

void CameraService::Initialize(std::string cameraUrl, MailController mailController, PathController pathController, SystemService systemService)
{
	_cameraUrl = cameraUrl;
	_mailController = mailController;
	_pathController = pathController;
	_systemService = systemService;

	_alreadyDetectedMotionEvents = _pathController.ScanCameraFolder();
}

std::string CameraService::PerformAction(std::vector<std::string> data)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == START && actionParameter == MOTION)
	{
		startCamera();
		return CAMERA_START_MOTION_SUCCESS;
	}

	else if (action == STOP && actionParameter == MOTION)
	{
		stopCamera();
		return CAMERA_STOP_MOTION_SUCCESS;
	}

	else if (action == SETCONTROLTASK && actionParameter == ON)
	{
		_motionControlActive = true;
		return CAMERA_ACTIVATE_MOTION_CONTROL_SUCCESS;
	}

	else if (action == SETCONTROLTASK && actionParameter == OFF)
	{
		_motionControlActive = false;
		return CAMERA_DEACTIVATE_MOTION_CONTROL_SUCCESS;
	}

	else if (action == GET && actionParameter == MOTION)
	{
		std::string commandParameter = data[CAMERA_CMD_PARAMETER_INDEX];

		if (commandParameter == STATE &&  IsMotionRunning())
		{
			return ACTIVE;
		}
		else if (commandParameter == STATE && !IsMotionRunning())
		{
			return INACTIVE;
		}

		else if (commandParameter == CONTROL && _motionControlActive)
		{
			return ACTIVE;
		}
		else if (commandParameter == CONTROL && !_motionControlActive)
		{
			return INACTIVE;
		}

		else if (commandParameter == DATA)
		{
			return getDataJsonString();
		}

		else
		{
			return CAMERA_ERROR_NR_172;
		}
	}

	return CAMERA_ERROR_NR_170;
}

void CameraService::Check()
{
	std::vector<std::string> currentMotionEvents = _pathController.ScanCameraFolder();

	int currentMotionEventsCount = currentMotionEvents.size();
	int alreadyDetectedMotionEventsCount = _alreadyDetectedMotionEvents.size();

	if (currentMotionEventsCount != alreadyDetectedMotionEventsCount)
	{
		if (currentMotionEventsCount > alreadyDetectedMotionEventsCount)
		{
			int maxImagesToSend = CAMERA_IMAGES_TO_SEND;
			int difference = currentMotionEventsCount - alreadyDetectedMotionEventsCount;
			int startIndex = 0;

			if (difference > maxImagesToSend)
			{
				startIndex = currentMotionEventsCount - maxImagesToSend;
			}

			for (int index = startIndex; index < currentMotionEventsCount;
				index++)
			{
				std::string currentMotionEventImage = currentMotionEvents[index];
				bool alreadySentImage = false;

				for (int controlIndex = 0; controlIndex < _alreadySentEvents.size(); controlIndex++)
				{
					if (_alreadySentEvents[controlIndex] == currentMotionEventImage)
					{
						alreadySentImage = true;
						break;
					}
				}

				if (alreadySentImage)
				{
					continue;
				}

				std::stringstream imagePath;
				imagePath << "../../.." << NAS_PATH_CAMERA << currentMotionEventImage;

				_mailController.SendMailWithImage(imagePath.str());
				_alreadySentEvents.push_back(currentMotionEvents[index]);
			}
		}
	}

	_alreadyDetectedMotionEvents = currentMotionEvents;
}

bool CameraService::GetMotionControlActive()
{
	return _motionControlActive;
}

bool CameraService::GetStartCamera()
{
	return _startCamera;
}

bool CameraService::GetStopCamera()
{
	return _stopCamera;
}

bool CameraService::IsMotionRunning()
{
	return _isMotionRunning;
}

std::string CameraService::StartMotion()
{
	if (IsMotionRunning())
	{
		return CAMERA_ERROR_NR_173;
	}

	_isMotionRunning = true;

	_startCamera = false;
	_stopCamera = false;

	std::string command = CMD_SUDO_MOTION;
	Tools::SendSystemCommandGetResult(command);

	return CAMERA_START_MOTION_SUCCESS;
}

std::string CameraService::StopMotion()
{
	if (!IsMotionRunning())
	{
		return CAMERA_ERROR_NR_174;
	}

	_isMotionRunning = false;

	_startCamera = false;
	_stopCamera = false;

	std::string command = CMD_SUDO_KILLALL_MOTION;
	Tools::SendSystemCommandGetResult(command);

	return CAMERA_STOP_MOTION_SUCCESS;
}

//--------------------------Private-----------------------//

std::string CameraService::startCamera()
{
	if (IsMotionRunning())
	{
		return CAMERA_ERROR_NR_173;
	}

	_startCamera = true;
	_stopCamera = false;

	return CAMERA_START_CAMERA_SUCCESS;
}

std::string CameraService::stopCamera()
{
	if (!IsMotionRunning())
	{
		return CAMERA_ERROR_NR_174;
	}

	_startCamera = false;
	_stopCamera = true;

	_motionControlActive = false;

	return CAMERA_STOP_CAMERA_SUCCESS;
}

std::string CameraService::getDataJsonString()
{
	std::stringstream out;
	out << "{\"MotionData\":";

	out << "{\"State\":";
	if (IsMotionRunning())
	{
		out << "\"ON\"},";
	}
	else
	{
		out << "\"OFF\"},";
	}

	out << "{\"Control\":";
	if (_motionControlActive)
	{
		out << "\"ON\"},";
	}
	else
	{
		out << "\"OFF\"},";
	}

	out << "{\"URL\":\"" << _cameraUrl << "\"},"
		<< "{" << getMotionEventsJsonString() << "}"
		<< "}";

	return out.str();
}

std::string CameraService::getMotionEventsJsonString()
{
	std::stringstream out;
	out << "[";

	_motionEvents = _pathController.ScanCameraFolder();

	int maxEventCount = CAMERA_EVENTS_MAX_COUNT;
	int motionEventCount = _motionEvents.size();

	int startIndex = 0;
	if (motionEventCount > maxEventCount)
	{
		startIndex = motionEventCount - maxEventCount;
	}

	std::stringstream data;
	for (int index = startIndex; index < _motionEvents.size(); index++)
	{
		std::string motionEventString =
			std::string("{")
			+ std::string("\"Event\":")
			+ std::string("{")
			+ std::string("\"FileName\":\"") + _motionEvents[index]
			+ std::string("\"}")
			+ std::string("}");

		data << motionEventString << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]";

	return out.str();
}
