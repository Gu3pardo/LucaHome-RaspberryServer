#include "Encrypter.h"

string Encrypter::Encrypt(int source, char key[], string textToEncrypt)
{
	if (source == CMD_SOURCE_TASKER) {
		return textToEncrypt;
	}

	// TODO Implement Encryption
	return textToEncrypt;
}