#include "cameraservice.h"

CameraService::CameraService() {
	_isMotionRunning = false;

	_startCamera = false;
	_stopCamera = false;

	_motionControlActive = false;
}

CameraService::~CameraService() {
}

//--------------------------Public-----------------------//

void CameraService::Initialize(std::string motionPath, std::string cameraUrl,
		MailService mailService, SystemService systemService) {
	_motionPath = motionPath;
	_cameraUrl = cameraUrl;
	_mailService = mailService;
	_systemService = systemService;
}

std::string CameraService::PerformAction(std::string action,
		std::vector<std::string> data) {
	if (action == "START") {
		if (data[4] == "MOTION") {
			startCamera();
			return "startMotion:1";
		} else {
			return "Error 171:Invalid data for camera";
		}
	} else if (action == "STOP") {
		if (data[4] == "MOTION") {
			stopCamera();
			return "stopMotion:1";
		} else {
			return "Error 171:Invalid data for camera";
		}
	} else if (action == "GET") {
		if (data[4] == "MOTION") {
			if (data[5] == "STATE") {
				if (IsMotionRunning()) {
					return "motion:ON";
				} else {
					return "motion:OFF";
				}
			} else if (data[5] == "DATA") {
				return getData();
			} else {
				return "Error 172:Invalid data5 for camera";
			}
		} else {
			return "Error 171:Invalid data for camera";
		}
	} else if (action == "SETCONTROLTASK") {
		if (data[4] == "ON") {
			_motionControlActive = true;
			return "setMotionControl:1:1";
		} else if (data[4] == "OFF") {
			_motionControlActive = false;
			return "setMotionControl:0:1";
		} else {
			return "Error 171:Invalid data for camera";
		}
	}

	return "Error 170:Action not found for camera";
}

void CameraService::Check() {
	std::vector < std::string > currentMotionEvents = scanFolder();

	int currentMotionEventsCount = currentMotionEvents.size();
	int motionEventsCount = _motionEvents.size();

	if (currentMotionEventsCount != motionEventsCount) {
		if (currentMotionEventsCount > motionEventsCount) {
			int maxImagesToSend = 10;
			int difference = currentMotionEventsCount - motionEventsCount;
			int startIndex = 0;

			if (difference > maxImagesToSend) {
				startIndex = currentMotionEventsCount - maxImagesToSend;
			}

			for (int index = startIndex; index < currentMotionEventsCount;
					index++) {
				std::string currentMotionEventImage = currentMotionEvents[index];
				bool alreadySentImage = false;

				for (int controlIndex = 0;
						controlIndex < _alreadySentEvents.size();
						controlIndex++) {
					if (_alreadySentEvents[controlIndex]
							== currentMotionEventImage) {
						alreadySentImage = true;
						break;
					}
				}

				if (alreadySentImage) {
					continue;
				}

				std::stringstream imagePath;
				imagePath << "/NAS/Camera/" << currentMotionEventImage;

				_mailService.sendMailWithAttachement(imagePath.str());
				_alreadySentEvents.push_back(currentMotionEvents[index]);
			}
		}
	}

	_motionEvents = currentMotionEvents;
}

bool CameraService::GetMotionControlActive() {
	return _motionControlActive;
}

bool CameraService::GetStartCamera() {
	return _startCamera;
}

bool CameraService::GetStopCamera() {
	return _stopCamera;
}

bool CameraService::IsMotionRunning() {
	return _isMotionRunning;
	// not working... disabled for now...
	/*std::string motionProcessName = "motion";
	 int motionPid = _systemService.IsProcessRunning(motionProcessName);

	 if (motionPid != -1) {
	 return true;
	 }

	 return false;*/
}

std::string CameraService::StartMotion() {
	if (IsMotionRunning()) {
		return "startMotion:0:motionAlreadyRunning";
	}

	_isMotionRunning = true;

	_startCamera = false;
	_stopCamera = false;

	std::string command = "sudo motion";
	Tools::sendSystemCommandGetResult(command);

	return "startMotion:1";
}

std::string CameraService::StopMotion() {
	if (!IsMotionRunning()) {
		return "stopMotion:0:motionNotRunning";
	}

	_isMotionRunning = false;

	_startCamera = false;
	_stopCamera = false;

	std::string command = "sudo killall motion";
	Tools::sendSystemCommandGetResult(command);

	return "stopMotion:1";
}

//--------------------------Private-----------------------//

std::string CameraService::startCamera() {
	if (IsMotionRunning()) {
		return "startCamera:0:motionAlreadyRunning";
	}

	_startCamera = true;
	_stopCamera = false;

	return "startCamera:1";
}

std::string CameraService::stopCamera() {
	if (!IsMotionRunning()) {
		return "stopCamera:0:motionNotRunning";
	}

	_startCamera = false;
	_stopCamera = true;

	return "stopCamera:1";
}

std::string CameraService::getData() {
	std::stringstream data;
	data << "{MotionData:";

	if (IsMotionRunning()) {
		data << "{State:1};";
	} else {
		data << "{State:0};";
	}

	data << "{URL:" << _cameraUrl << "};";

	data << getMotionEventsRestString() << "};";

	return data.str();
}

std::vector<std::string> CameraService::scanFolder() {
	DIR *dir;
	struct dirent *ent;
	std::vector < std::string > imageEntries;

	const char *motionPathChar = _motionPath.c_str();

	if ((dir = opendir(motionPathChar)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string fileName = ent->d_name;
			if (fileName[0] == '.') {
				continue;
			}
			if (Tools::hasEnding(fileName, ".jpg")) {
				imageEntries.push_back(fileName);
			}
		}
		closedir(dir);
	}

	return imageEntries;
}

std::string CameraService::getMotionEventsRestString() {
	std::stringstream out;
	out << "{MotionEvents:";

	_motionEvents = scanFolder();

	int maxEventCount = 10;
	int startIndex = 0;

	int motionEventCount = _motionEvents.size();

	if (motionEventCount > maxEventCount) {
		startIndex = motionEventCount - maxEventCount;
	}

	for (int index = startIndex; index < _motionEvents.size(); index++) {
		out << "{Event:" << _motionEvents[index] << "},";
	}

	out << "};" << "\x00" << std::endl;
	return out.str();
}
