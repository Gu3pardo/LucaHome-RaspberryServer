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

using namespace std;

#ifndef TOOLS_H
#define TOOLS_H

class Tools
{
public:
	static string ConvertIntToStr(int);
	static int ConvertStrToInt(string);

	static bool ConvertIntToBool(int);
	static int ConvertBoolToInt(bool);

	static string ConvertDoubleToStr(double);
	static double ConvertStrToDouble(string);

	static string ConvertBoolToStr(bool);
	static bool ConvertStrToBool(string);

	static string ConvertUnsignedCharToStr(unsigned char);
	static unsigned char ConvertStrToUnsignedChar(string);

	static bool HasEnding(string, string);

	static vector<string> Explode(string, string);

	static void SendSystemCommand(string);
	static string SendSystemCommandGetResult(string);

	static bool ReplaceString(string&, const string&, const string&);
};

#endif
