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

using namespace std;

#ifndef DECRYPTER_H
#define DECRYPTER_H

class Decrypter
{
public:
	static string Decrypt(char[], string);
};

#endif
