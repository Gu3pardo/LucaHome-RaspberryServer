#include "Decrypter.h"

string Decrypter::Decrypt(int source, char key[], string textToDecrypt)
{
	if (source == CMD_SOURCE_TASKER) {
		return textToDecrypt;
	}

	// TODO Implement Decryption
	return textToDecrypt;
}