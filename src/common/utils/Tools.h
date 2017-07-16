#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

#ifndef TOOLS_H
#define TOOLS_H

class Tools
{
public:
	static std::string ConvertIntToStr(int);
	static int ConvertStrToInt(std::string);

	static std::string ConvertDoubleToStr(double);
	static double ConvertStrToDouble(std::string);

	static std::string ConvertBoolToStr(bool);
	static bool ConvertStrToBool(std::string);

	static bool HasEnding(std::string, std::string);

	static std::vector<std::string> Explode(std::string, std::string);

	static void SendSystemCommand(std::string);
	static std::string SendSystemCommandGetResult(std::string);

	static bool ReplaceString(std::string&, const std::string&, const std::string&);
};

#endif
