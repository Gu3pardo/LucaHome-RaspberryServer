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

#include "../../crosscutting/Constants.h"
#include "../handler/CommandHandler.h"

using namespace std;

#define BUFFER_LENGTH 512
#define SERVER_PORT 6677

#ifndef SERVER_H
#define SERVER_H

class Server
{
private:

public:
	Server();
	~Server();

	void Run();
};

#endif
