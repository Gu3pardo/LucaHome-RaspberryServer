#include "TemperatureService.h"

/*===============PUBLIC==============*/

TemperatureService::TemperatureService()
{
	_isInitialized = false;

	_minTemp = 15;
	_maxTemp = 35;

	//TODO: add gpios for LEDs
	_ledNormalTemp = -1;
	_ledErrorLowTemp = -1;
	_ledErrorHighTemp = -1;

	_temperatureControlActive = true;
}

TemperatureService::~TemperatureService()
{
}

void TemperatureService::Initialize(FileController fileController, MailController mailController, std::string settingsFile, std::string sensorId, std::string temperatureArea, std::string graphPath)
{
	_fileController = fileController;
	_mailController = mailController;

	_settingsFile = settingsFile;
	loadSettings();

	std::ostringstream path;
	path << "/sys/bus/w1/devices/" << sensorId << "/w1_slave";
	_sensorPath = path.str();

	_temperatureArea = temperatureArea;

	_graphPath = graphPath;

	_warningCount = 0;
	_isInitialized = true;
}

void TemperatureService::ControlTemperature()
{
	if (!_isInitialized)
	{
		syslog(LOG_INFO, "TemperatureService is not initialized!");
		return;
	}

	double currentTemperature = loadTemperature();

	if (currentTemperature < _minTemp)
	{
		syslog(LOG_INFO, "Temperature low! %d", currentTemperature);

		std::ostringstream data;
		data << "Current temperature at " << _temperatureArea << " is too low! " << currentTemperature << "�C!";

		sendWarningMail(data.str());
		enableLED(_ledErrorLowTemp);
	}
	else if (currentTemperature > _maxTemp)
	{
		syslog(LOG_INFO, "Temperature high! %d", currentTemperature);

		std::ostringstream data;
		data << "Current temperature at " << _temperatureArea << " is too high! " << currentTemperature << "�C!";

		sendWarningMail(data.str());
		enableLED(_ledErrorHighTemp);
	}
	else
	{
		if (_warningCount > 0)
		{
			syslog(LOG_INFO, "Temperature was for %d minutes not in normal values!", _warningCount);
		}

		_warningCount = 0;
		enableLED(_ledNormalTemp);
	}
}

std::string TemperatureService::PerformAction(std::string action, std::vector<std::string> data)
{
	if (action == GET)
	{
		if (data.size() == 5)
		{
			if (data[4] == REST)
			{
				return getRestString();
			}
			else if (data[4] == WEBSITE)
			{
				return getString();
			}
			else
			{
				return "Error 132:Wrong action parameter for temperature";
			}
		}
		else
		{
			return "Error 131:Wrong data size for temperature";
		}
	}
	else if (action == SETCONTROLTASK)
	{
		if (data[4] == ON)
		{
			_temperatureControlActive = true;
			return "setTemperatureControl:1:1";
		}
		else if (data[4] == OFF)
		{
			_temperatureControlActive = false;
			return "setTemperatureControl:0:1";
		}
		else
		{
			return "Error 133:Invalid data for temperature";
		}
	}
	else
	{
		return "Error 130:Action not found for temperature";
	}
}

bool TemperatureService::GetTemperatureControlActive()
{
	return _temperatureControlActive;
}

void TemperatureService::ReloadData()
{
	syslog(LOG_INFO, "Reloading temperature data!");
	loadSettings();
}

/*==============PRIVATE==============*/

void TemperatureService::loadSettings()
{
	std::string settingsFileContent = _fileController.ReadFile(_settingsFile);

	_minTemp = _xmlService.GetTempMin(settingsFileContent);
	_maxTemp = _xmlService.GetTempMax(settingsFileContent);

	_ledNormalTemp = _xmlService.GetLEDTempNormal(settingsFileContent);
	_ledErrorLowTemp = _xmlService.GetLEDTempLow(settingsFileContent);
	_ledErrorHighTemp = _xmlService.GetLEDTempHigh(settingsFileContent);

	_temperatureControlActive = _xmlService.IsTempControlActive(settingsFileContent);
}

void TemperatureService::saveSettings()
{
	std::string xmldata = _xmlService.GenerateTemperatureSettingsXml(_minTemp, _maxTemp, _ledNormalTemp, _ledErrorLowTemp, _ledErrorHighTemp, _temperatureControlActive);
	_fileController.SaveFile(_settingsFile, xmldata);
}

double TemperatureService::loadTemperature()
{
	const char *charPath = _sensorPath.c_str();
	FILE *device = fopen(charPath, "r");

	double temperature = -1;
	char crcVar[5];

	if (device != NULL)
	{
		if (!ferror(device))
		{
			fscanf(device, "%*x %*x %*x %*x %*x %*x %*x %*x %*x : crc=%*x %s", crcVar);
			if (strncmp(crcVar, "YES", 3) == 0)
			{
				fscanf(device, "%*x %*x %*x %*x %*x %*x %*x %*x %*x t=%lf", &temperature);
				temperature /= 1000.0;
			}
			else
			{
				syslog(LOG_INFO, "Error strncmp!");
			}
		}
		else
		{
			syslog(LOG_INFO, "Error with device!");
		}
	}
	else
	{
		syslog(LOG_INFO, "Check connections %s", _sensorPath.c_str());
	}

	fclose(device);

	return temperature;
}

void TemperatureService::sendWarningMail(std::string warning)
{
	_warningCount++;

	if (_warningCount % 10 != 0)
	{
		syslog(LOG_INFO, "Already send a mail within the last minutes!");
		return;
	}

	_mailController.SendMail(warning);
}

void TemperatureService::enableLED(int led)
{
	if (led == -1)
	{
		//syslog(LOG_INFO, "LED has wrong value! Cannot enable -1!");
		return;
	}

	PiControl::WriteGpio(_ledErrorHighTemp, 0);
	PiControl::WriteGpio(_ledErrorLowTemp, 0);
	PiControl::WriteGpio(_ledNormalTemp, 0);

	if (led == _ledErrorHighTemp)
	{
		PiControl::WriteGpio(_ledErrorHighTemp, 1);
	}
	else if (led == _ledErrorLowTemp)
	{
		PiControl::WriteGpio(_ledErrorLowTemp, 1);
	}
	else if (led == _ledNormalTemp)
	{
		PiControl::WriteGpio(_ledNormalTemp, 1);
	}
	else
	{
		syslog(LOG_INFO, "LED has wrong value! Cannot enable %d!", led);
	}
}

double TemperatureService::getValue()
{
	if (!_isInitialized)
	{
		syslog(LOG_INFO, "TemperatureService is not initialized!");
		return -1;
	}

	return loadTemperature();
}

std::string TemperatureService::getString()
{
	if (!_isInitialized)
	{
		syslog(LOG_INFO, "TemperatureService is not initialized!");
		return "";
	}

	std::stringstream out;
	out << loadTemperature();
	out << std::endl;

	return out.str();
}

std::string TemperatureService::getRestString()
{
	if (!_isInitialized)
	{
		syslog(LOG_INFO, "TemperatureService is not initialized!");
		return "";
	}

	std::stringstream out;

	out << "{temperature:"
		<< "{value:" << loadTemperature() << "};"
		<< "{area:" << _temperatureArea << "};"
		<< "{sensorPath:" << _sensorPath << "};"
		<< "{graphPath:" << _graphPath << "};"
		<< "};";

	out << "\x00" << std::endl;

	return out.str();
}
