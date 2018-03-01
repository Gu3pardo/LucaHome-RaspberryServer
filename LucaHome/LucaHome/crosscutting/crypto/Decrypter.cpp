#include "Decrypter.h"

string Decrypter::Decrypt(int source, string key, string textToDecrypt)
{
	if (source == CMD_SOURCE_TASKER) {
		return textToDecrypt;
	}

	if (key == "") {
		return DECRYPT_ERROR_KEY_NULL;
	}

	// TODO Implement Decryption
	return textToDecrypt;
}