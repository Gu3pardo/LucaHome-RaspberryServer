#include "GpioService.h"

/*===============PUBLIC==============*/

GpioService::GpioService() {}

GpioService::~GpioService() {}

void GpioService::Initialize(string databaseName)
{
	_gpioDatabase = GpioDatabase(databaseName);
}

string GpioService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	else if (action == ADD)
	{
		if (data.size() == GPIO_DATA_SIZE)
		{
			char error = addGpio(data);
			if (!error)
			{
				return GPIO_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return GPIO_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == GPIO_DATA_SIZE)
		{
			char error = updateGpio(data);
			if (!error)
			{
				return GPIO_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return GPIO_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteGpio(actionParameter);
		if (!error)
		{
			return GPIO_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "Error: " << error;
		return actionAnswer.str();
	}

	else if (action == SET)
	{
		if (data.size() == GPIO_SET_DATA_SIZE)
		{
			char error = setGpio(data);
			if (!error)
			{
				return GPIO_SET_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "Error: " << error;
			return actionAnswer.str();
		}
		return GPIO_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void GpioService::Dispose()
{
	_gpioDatabase.Dispose();
}

/*==============PRIVATE==============*/

string GpioService::getJsonString()
{
	vector<Gpio> gpioList = _gpioDatabase.GetList();

	stringstream data;
	for (int index = 0; index < gpioList.size(); index++)
	{
		data << gpioList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Data\":[" << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << endl;
	return out.str();
}

char GpioService::addGpio(vector<string> newGpioData)
{
	Gpio newGpio(
		newGpioData[GPIO_UUID_INDEX].c_str(),
		newGpioData[GPIO_NAME_INDEX].c_str(),
		Tools::ConvertStrToInt(newGpioData[GPIO_PIN_INDEX].c_str()),
		Tools::ConvertStrToBool(newGpioData[GPIO_STATE_INDEX].c_str()));
	return _gpioDatabase.Insert(_gpioDatabase.GetList().size(), newGpio);
}

char GpioService::updateGpio(vector<string> updateGpioData)
{
	Gpio updateGpio(
		updateGpioData[GPIO_UUID_INDEX].c_str(),
		updateGpioData[GPIO_NAME_INDEX].c_str(),
		Tools::ConvertStrToInt(updateGpioData[GPIO_PIN_INDEX].c_str()),
		Tools::ConvertStrToBool(updateGpioData[GPIO_STATE_INDEX].c_str()));
	return _gpioDatabase.Update(updateGpio);
}

char GpioService::deleteGpio(string deleteUuid)
{
	return _gpioDatabase.Delete(deleteUuid);
}

char GpioService::setGpio(vector<string> setGpioData)
{
	string uuid = setGpioData[GPIO_UUID_INDEX].c_str();
	bool newState = atoi(setGpioData[GPIO_SET_STATE_INDEX].c_str()) == 1;

	Gpio gpio = _gpioDatabase.GetByUuid(uuid);
	if (gpio.GetPin() == -1) {
		return -1;
	}

	bool sendSuccess = PiControl::WriteGpio(gpio.GetPin(), newState ? 1 : 0);
	if (!sendSuccess) {
		return -2;
	}

	return _gpioDatabase.UpdateState(uuid, newState);
}
