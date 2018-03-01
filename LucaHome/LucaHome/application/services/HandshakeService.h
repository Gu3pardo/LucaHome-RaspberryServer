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

#include "../../crosscutting/Constants.h"

using namespace std;

#ifndef HANDSHAKE_SERVICE_H
#define HANDSHAKE_SERVICE_H


#define HANDSHAKE_ARRAY_CLIENT_ADDRESS_INDEX 0
#define HANDSHAKE_ARRAY_SECRET_INDEX 1

class HandshakeService
{
private:
	vector<string[2]> _handshakes;


public:
	HandshakeService();
	~HandshakeService();

	bool HandshakePerformed(string);
	string CreateSecret(string);
	string GetSecret(string);
	void RemoveHandshake(string);
};

#endif
