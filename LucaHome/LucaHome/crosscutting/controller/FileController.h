#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <syslog.h>

using namespace std;

#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

class FileController
{
public:
	static string ReadFile(string path);
	static vector<string> ReadFileList(string path);
	static bool SaveFile(string path, string content);
};

#endif
