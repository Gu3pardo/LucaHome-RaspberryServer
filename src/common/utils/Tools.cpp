#include "Tools.h"

std::string Tools::ConvertIntToStr(int number)
{
	std::ostringstream numberStringStream;
	numberStringStream << number;
	return numberStringStream.str();
}

int Tools::ConvertStrToInt(std::string str)
{
	std::stringstream ss(str);
	int number;
	ss >> number;
	return number;
}

std::string Tools::ConvertBoolToStr(bool boolean)
{
	std::ostringstream booleanStringStream;
	if (boolean)
	{
		booleanStringStream << "1";
	}
	else
	{
		booleanStringStream << "0";
	}
	return booleanStringStream.str();
}

bool Tools::ConvertStrToBool(std::string str)
{
	std::stringstream ss(str);
	bool boolean;
	ss >> boolean;
	return boolean;
}

bool Tools::HasEnding(std::string fullString, std::string ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

std::vector<std::string> Tools::Explode(std::string delimiter, std::string str)
{
	std::vector<std::string> stringArray;
	int stringLength = str.length();

	int delimiterLength = delimiter.length();
	if (delimiterLength == 0)
	{
		return stringArray;
	}

	int startIndex = 0;
	int endIndex = 0;

	while (endIndex < stringLength)
	{
		int entryLength = 0;
		while (endIndex + entryLength < stringLength && entryLength < delimiterLength && str[endIndex + entryLength] == delimiter[entryLength])
		{
			entryLength++;
		}

		if (entryLength == delimiterLength)
		{
			stringArray.push_back(str.substr(startIndex, endIndex - startIndex));
			endIndex += delimiterLength;
			startIndex = endIndex;
		}
		else
		{
			endIndex++;
		}
	}

	stringArray.push_back(str.substr(startIndex, endIndex - startIndex));
	return stringArray;
}

bool Tools::ReplaceString(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);

	if (start_pos == std::string::npos) {
		return false;
	}

	str.replace(start_pos, from.length(), to);
	return true;
}

void Tools::SendSystemCommand(std::string commandString)
{
	syslog(LOG_INFO, "Sending command: %s", commandString.c_str());
	const char *commandChar = commandString.c_str();
	char command[50];
	strcpy(command, commandChar);
	system(command);
}

std::string Tools::SendSystemCommandGetResult(std::string commandString)
{
	const char *command = commandString.c_str();

	FILE *pipe = popen(command, "r");
	if (!pipe)
	{
		return "Error 80:System command error. Pipe Error!";
	}

	char buffer[256];
	std::string result = "";
	while (!feof(pipe))
	{
		if (fgets(buffer, 256, pipe) != NULL)
		{
			result += buffer;
		}
	}
	pclose(pipe);

	return result;
}
