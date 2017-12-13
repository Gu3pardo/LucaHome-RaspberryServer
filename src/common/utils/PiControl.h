#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
/* below is necessary due to https://github.com/platenspeler/LamPI-2.0/blob/master/transmitters/livolo/livolo.h */
#include <errno.h>
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define WTRUE 136
#define WFALSE 142
#define PLENGTH 300
#define REPEAT 15
#define CODE_LENGTH 6

#ifndef PICONTROL_H
#define PICONTROL_H

class PiControl
{
private:
	static bool sendEther(int, int[]);
	static void printCode(int[]);

	/* from https://github.com/platenspeler/LamPI-2.0/blob/master/transmitters/livolo/livolo.h */
	static void selectPulse(unsigned char, int, bool);
	static void sendPulse(unsigned char, int);

public:
	static bool Send433Mhz(int, std::string, int);
	static bool WriteGpio(int, int);

	/* from https://github.com/platenspeler/LamPI-2.0/blob/master/transmitters/livolo/livolo.h */
	static bool SendButton(unsigned int, unsigned char, int, bool);
};

#endif
