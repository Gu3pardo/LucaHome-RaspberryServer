#include "Encrypter.h"

string Encrypter::Encrypt(int source, char key[], string textToEncrypt)
{
	if (source == CMD_SOURCE_SCHEDULER) {
		return textToEncrypt;
	}

	// TODO Implement Encryption
	return textToEncrypt;
}