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

#include "../Constants.h"

using namespace std;

#ifndef ENCRYPTER_H
#define ENCRYPTER_H

class Encrypter
{
public:
	static string Encrypt(int, string, string);
};

#endif
