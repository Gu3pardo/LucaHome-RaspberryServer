#include "Encrypter.h"

string Encrypter::Encrypt(int source, string key, string textToEncrypt)
{
	if (source == CMD_SOURCE_TASKER) {
		return textToEncrypt;
	}

	if (key == "") {
		return ENCRYPT_ERROR_KEY_NULL;
	}

	// TODO Implement Encryption
	return textToEncrypt;
}