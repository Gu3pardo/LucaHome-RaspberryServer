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
	LoadData();

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
		return;
	}

	double currentTemperature = loadTemperature();

	if (currentTemperature < _minTemp)
	{
		std::ostringstream data;
		data << "Current temperature at " << _temperatureArea << " is too low! " << currentTemperature << "°C!";

		sendWarningMail(data.str());
		enableLED(_ledErrorLowTemp);
	}
	else if (currentTemperature > _maxTemp)
	{
		std::ostringstream data;
		data << "Current temperature at " << _temperatureArea << " is too high! " << currentTemperature << "°C!";

		sendWarningMail(data.str());
		enableLED(_ledErrorHighTemp);
	}
	else
	{
		_warningCount = 0;
		enableLED(_ledNormalTemp);
	}
}

std::string TemperatureService::PerformAction(std::vector<std::string> data)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == ALL)
		{
			return getJsonString();
		}
		else if (actionParameter == PHP)
		{
			return getPhpString();
		}
		return TEMPERATURE_ERROR_NR_132;
	}

	else if (action == SETCONTROLTASK)
	{
		if (actionParameter == ON)
		{
			_temperatureControlActive = true;
			return TEMPERATURE_ACTIVATE_CONTROL_SUCCESS;
		}
		else if (actionParameter == OFF)
		{
			_temperatureControlActive = false;
			return TEMPERATURE_DEACTIVATE_CONTROL_SUCCESS;
		}
		return TEMPERATURE_ERROR_NR_133;
	}

	return TEMPERATURE_ERROR_NR_130;
}

bool TemperatureService::GetTemperatureControlActive()
{
	return _temperatureControlActive;
}

void TemperatureService::LoadData()
{
	std::string settingsFileContent = _fileController.ReadFile(_settingsFile);

	_minTemp = _xmlService.GetTempMin(settingsFileContent);
	_maxTemp = _xmlService.GetTempMax(settingsFileContent);

	_ledNormalTemp = _xmlService.GetLEDTempNormal(settingsFileContent);
	_ledErrorLowTemp = _xmlService.GetLEDTempLow(settingsFileContent);
	_ledErrorHighTemp = _xmlService.GetLEDTempHigh(settingsFileContent);

	_temperatureControlActive = _xmlService.IsTempControlActive(settingsFileContent);
}

/*==============PRIVATE==============*/

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
		}
	}

	fclose(device);

	return temperature;
}

void TemperatureService::sendWarningMail(std::string warning)
{
	_warningCount++;

	if (_warningCount % 10 != 0)
	{
		return;
	}

	_mailController.SendMail(warning);
}

void TemperatureService::enableLED(int led)
{
	if (led == -1)
	{
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
}

double TemperatureService::getValue()
{
	if (!_isInitialized)
	{
		return -273.15;
	}

	return loadTemperature();
}

std::string TemperatureService::getJsonString()
{
	if (!_isInitialized)
	{
		return TEMPERATURE_ERROR_NR_134;
	}

	std::string str =
		std::string("{")
		+ std::string("\"Temperature\":")
		+ std::string("{")
		+ std::string("\"Value\":") + Tools::ConvertDoubleToStr(loadTemperature()) + std::string(",")
		+ std::string("\"Area\":\"") + _temperatureArea + std::string("\",")
		+ std::string("\"SensorPath\":\"") + _sensorPath + std::string("\",")
		+ std::string("\"GraphPath\":\"") + _graphPath
		+ std::string("\"}")
		+ std::string("}");
	return str;
}

std::string TemperatureService::getPhpString()
{
	if (!_isInitialized)
	{
		return "temperature::-273.15::NA::NA::NA;";
	}

	std::stringstream out;

	out << "temperature::"
		<< loadTemperature() << "::"
		<< _temperatureArea << "::"
		<< _sensorPath << "::"
		<< _graphPath << ";";

	out << "\x00" << std::endl;

	return out.str();
}

