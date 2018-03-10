#include "TemperatureService.h"

/*===============PUBLIC==============*/

TemperatureService::TemperatureService()
{
	_room = Room();
	_sensorPath = "";
	_graphPath = "";

	_minTemp = 15;
	_maxTemp = 35;

	_warningCount = 0;
	_isInitialized = false;
}

TemperatureService::~TemperatureService()
{
}

void TemperatureService::Initialize(Room room, string sensorId, string graphPath, int minTemp, int maxTemp)
{
	_room = room;

	ostringstream path;
	path << "/sys/bus/w1/devices/" << sensorId << "/w1_slave";
	_sensorPath = path.str();

	_graphPath = graphPath;

	_minTemp = minTemp;
	_maxTemp = maxTemp;

	_warningCount = 0;
	_isInitialized = true;
}

string TemperatureService::PerformAction(vector<string> data)
{
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void TemperatureService::CheckTemperature()
{
	if (!_isInitialized)
	{
		return;
	}

	double currentTemperature = loadTemperature();

	if (currentTemperature < _minTemp)
	{
		ostringstream data;
		data << "Current temperature at " << _room.GetName() << " is too low! " << currentTemperature << "°C!";

		sendWarningMail(data.str());
	}
	else if (currentTemperature > _maxTemp)
	{
		ostringstream data;
		data << "Current temperature at " << _room.GetName() << " is too high! " << currentTemperature << "°C!";

		sendWarningMail(data.str());
	}
	else
	{
		_warningCount = 0;
	}
}

/*==============PRIVATE==============*/

string TemperatureService::getJsonString()
{
	if (!_isInitialized)
	{
		return TEMPERATURE_ERROR_NOT_INITIALIZED;
	}

	string uuid = "444F5D57-E2B7-4FCD-955C-330B9AD61547";
	string roomUuid = _room.GetUuid();
	double currentTemperature = loadTemperature();

	time_t currentTime = time(0);
	struct tm *now = localtime(&currentTime);

	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;
	int hour = now->tm_hour;
	int minute = now->tm_min;

	int temperatureType = 1;

	Temperature temperature(
		uuid, roomUuid,
		currentTemperature,
		day, month, year,
		hour, minute,
		temperatureType,
		_sensorPath,
		_graphPath);

	stringstream out;
	out << "{\"Category\":\"Temperature\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< temperature.JsonString()
		<< "]}\x00" << endl;
	return out.str();
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

void TemperatureService::sendWarningMail(string warning)
{
	_warningCount++;

	if (_warningCount % 10 != 0)
	{
		return;
	}

	MailController::SendMail(RECEIVER_MAIL, 0, warning);
}
