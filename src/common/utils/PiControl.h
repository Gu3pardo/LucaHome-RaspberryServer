#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>

#define WTRUE 136
#define WFALSE 142
#define PLENGTH 300
#define REPEAT 10
#define CODE_LENGTH 6

#ifndef PICONTROL_H
#define PICONTROL_H

class PiControl
{
private:
	static bool sendEther(int, int[]);
	static void printCode(int[]);

public:
	static bool Send433Mhz(int, std::string, int);
	static bool WriteGpio(int, int);
};

#endif
