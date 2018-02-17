#include "PiControl.h"

int p_short = 110;									// 110 works quite OK
int p_long = 290;									// 300 works quite OK
int p_start = 520;									// 520 works quite OK

//================= PUBLIC =================

bool PiControl::Send433Mhz(int gpio, std::string codeStr, int active)
{
	// Validate code
	if (codeStr.length() != CODE_LENGTH)
	{
		printf("Invalid code length! Should be %d", CODE_LENGTH);
		return false;
	}

	for (int index = 0; index < 5; index++)
	{
		if (codeStr[index] != '1' && codeStr[index] != '0')
		{
			printf("The code must be in this format: 10101A\n");
			return false;
		}
	}

	if (!(codeStr[5] >= (int)'A' && codeStr[5] <= (int)'E'))
	{
		printf("The code must be in this format: 10101B\n");
		return false;
	}

	int code[16] = { 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 128, 0, 0, 0 };

	// Parse device-code
	for (int index = 0; index < 5; index++)
	{
		if (codeStr[index] == '1')
		{
			code[index] = WTRUE;
		}
		else
		{
			code[index] = WFALSE;
		}
	}

	// Parse device-id (A - E)
	int id = pow(2, (int)codeStr[5] - 65);
	// Set device-id
	int x = 1;

	for (int index = 1; index < 6; index++)
	{
		if ((id & x) > 0)
		{
			code[4 + index] = WTRUE;
		}
		else
		{
			code[4 + index] = WFALSE;
		}
		x = x << 1;
	}

	// Set Status
	if (active == 1)
	{
		code[10] = WTRUE;
		code[11] = WFALSE;
	}
	else
	{
		code[10] = WFALSE;
		code[11] = WTRUE;
	}

	printCode(code);

	return sendEther(gpio, code);
}

bool PiControl::WriteGpio(int gpio, int status)
{
	if (wiringPiSetupGpio() == -1)
	{
		return false;
	}

	pinMode(gpio, OUTPUT);

	if (status == 1)
	{
		digitalWrite(gpio, HIGH);
	}
	else
	{
		digitalWrite(gpio, LOW);
	}

	return true;
}

// Due to https://github.com/platenspeler/LamPI-2.0/blob/master/transmitters/livolo/livolo.cpp
// keycodes #1: 0, #2: 96, #3: 120, #4: 24, #5: 80, #6: 48, #7: 108, #8: 12, #9: 72; #10: 40, #OFF: 106
// real remote IDs: 6400; 19303; 23783
// tested "virtual" remote IDs: 10550; 8500; 7400
// other IDs could work too, as long as they do not exceed 16 bit
// known issue: not all 16 bit remote ID are valid
// have not tested other buttons, but as there is dimmer control, some keycodes could be strictly system
// use: sendButton(remoteID, keycode), see example blink.ino; 

// =======================================================================================
//
//
bool PiControl::SendButton(unsigned int remoteID, unsigned char keycode, int gpio, bool action)
{
	if (wiringPiSetupGpio() == -1)
	{
		return false;
	}

	pinMode(gpio, OUTPUT);

	for (int pulse = 0; pulse <= REPEAT; pulse++)
	{
		if (action) {
			sendPulse(1, gpio);
		}
		else {
			sendPulse(0, gpio);
		}

		for (int bitIndex = 15; bitIndex >= 0; bitIndex--) {	// transmit remoteID
			unsigned int txPulse = remoteID & (1 << bitIndex);	// read bits from remote ID
			if (txPulse > 0) {
				selectPulse(1, gpio, action);
			}
			else {
				selectPulse(0, gpio, action);
			}
		}

		for (int keyCodeIndex = 6; keyCodeIndex >= 0; keyCodeIndex--) 	// XXX transmit keycode
		{
			unsigned char txPulse = keycode & (1 << keyCodeIndex); 	// read bits from keycode
			if (txPulse > 0) {
				selectPulse(1, gpio, action);
			}
			else {
				selectPulse(0, gpio, action);
			}
		}
	}

	if (action) {
		digitalWrite(gpio, HIGH);
	}
	else {
		digitalWrite(gpio, LOW);
	}

	return true;
}

//================= PRIVATE =================

void PiControl::printCode(int code[])
{
	printf("Sending ");
	for (int index = 0; index < 16; index++)
	{
		printf("%d ", code[index]);
	}
	printf("via Ether\n");
}

bool PiControl::sendEther(int gpio, int code[])
{
	if (wiringPiSetupGpio() == -1)
	{
		return false;
	}

	pinMode(gpio, OUTPUT);
	int x = 0;

	for (int repeatIndex = 0; repeatIndex < REPEAT; repeatIndex++)
	{
		for (int codeIndex = 0; codeIndex < 16; codeIndex++)
		{
			x = 128;
			for (int i = 1; i < 9; i++)
			{
				if ((code[codeIndex] & x) > 0)
				{
					digitalWrite(gpio, HIGH);
				}
				else
				{
					digitalWrite(gpio, LOW);
				}

				usleep(PLENGTH);
				x = x >> 1;
			}
		}
	}
	return true;
}

// =======================================================================================
// build transmit sequence so that every high pulse is followed by low and vice versa
void PiControl::selectPulse(unsigned char inBit, int gpio, bool action) {
	switch (inBit) {
	case 0:
		if (action) {
			sendPulse(2, gpio);
			sendPulse(4, gpio);
		}
		else {
			sendPulse(4, gpio);
			sendPulse(2, gpio);
		}
		break;

	case 1:
		if (action) {
			sendPulse(3, gpio);
		}
		else {
			sendPulse(5, gpio);
		}
		break;
	}

}

// =========================================================================================
// transmit pulses
// slightly corrected pulse length, use old (commented out) values if these not working for you
void PiControl::sendPulse(unsigned char txPulse, int gpio) {
	switch (txPulse)
	{
	case 0:
		digitalWrite(gpio, LOW);
		delayMicroseconds(p_start);
		break;

	case 1:
		digitalWrite(gpio, HIGH);
		delayMicroseconds(p_start);
		break;

	case 2:
		digitalWrite(gpio, LOW);
		delayMicroseconds(p_short);
		break;

	case 3:
		digitalWrite(gpio, LOW);
		delayMicroseconds(p_long);
		break;

	case 4:
		digitalWrite(gpio, HIGH);
		delayMicroseconds(p_short);
		break;

	case 5:
		digitalWrite(gpio, HIGH);
		delayMicroseconds(p_long);
		break;
	}
}