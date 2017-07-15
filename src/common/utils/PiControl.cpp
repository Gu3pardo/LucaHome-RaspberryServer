#include "PiControl.h"

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
