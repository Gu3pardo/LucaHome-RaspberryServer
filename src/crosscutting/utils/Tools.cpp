#include "Tools.h"

string Tools::ConvertIntToStr(int number)
{
	ostringstream numberStringStream;
	numberStringStream << number;
	return numberStringStream.str();
}

int Tools::ConvertStrToInt(string str)
{
	stringstream ss(str);
	int number;
	ss >> number;
	return number;
}

bool Tools::ConvertIntToBool(int number)
{
	if (number == 0) {
		return false;
	}
	return true;
}

int Tools::ConvertBoolToInt(bool boolean)
{
	if (boolean)
	{
		return 1;
	}

	return 0;
}

string Tools::ConvertDoubleToStr(double number)
{
	ostringstream numberStringStream;
	numberStringStream << number;
	return numberStringStream.str();
}

double Tools::ConvertStrToDouble(string str)
{
	stringstream ss(str);
	double number;
	ss >> number;
	return number;
}

string Tools::ConvertBoolToStr(bool boolean)
{
	ostringstream booleanStringStream;
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

bool Tools::ConvertStrToBool(string str)
{
	stringstream ss(str);
	bool boolean;
	ss >> boolean;
	return boolean;
}

string Tools::ConvertUnsignedCharToStr(unsigned char unsignedChar)
{
	ostringstream unsignedCharStringStream;
	unsignedCharStringStream << unsignedChar;
	return unsignedCharStringStream.str();
}

unsigned char Tools::ConvertStrToUnsignedChar(string str)
{
	stringstream ss(str);
	unsigned char unsignedChar;
	ss >> unsignedChar;
	return unsignedChar;
}

bool Tools::HasEnding(string fullString, string ending)
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

vector<string> Tools::Explode(string delimiter, string str)
{
	vector<string> stringArray;
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

bool Tools::ReplaceString(string& str, const string& from, const string& to) {
	size_t start_pos = str.find(from);

	if (start_pos == string::npos) {
		return false;
	}

	str.replace(start_pos, from.length(), to);
	return true;
}

void Tools::SendSystemCommand(string commandString)
{
	const char *commandChar = commandString.c_str();
	char command[50];
	strcpy(command, commandChar);
	system(command);
}

string Tools::SendSystemCommandGetResult(string commandString)
{
	const char *command = commandString.c_str();

	FILE *pipe = popen(command, "r");
	if (!pipe)
	{
		return "Error 80:System command error. Pipe Error!";
	}

	char buffer[256];
	string result = "";
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
