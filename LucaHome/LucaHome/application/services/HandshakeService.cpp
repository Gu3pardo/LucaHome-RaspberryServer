#include "HandshakeService.h"

/*===============PUBLIC==============*/

HandshakeService::HandshakeService() {}

HandshakeService::~HandshakeService() {}

bool HandshakeService::HandshakePerformed(string clientAddress) {
	for (int index = 0; index < _handshakes.size(); index++) {
		if (_handshakes[index][HANDSHAKE_ARRAY_CLIENT_ADDRESS_INDEX] == clientAddress) {
			return true;
		}
	}
	return false;
}

string HandshakeService::CreateSecret(string clientAddress) {
	string secret = clientAddress;

	secret.erase(remove(clientAddress.begin(), clientAddress.end(), ':'), clientAddress.end());
	secret.erase(remove(clientAddress.begin(), clientAddress.end(), '.'), clientAddress.end());
	secret.erase(remove(clientAddress.begin(), clientAddress.end(), '/'), clientAddress.end());
	secret.erase(remove(clientAddress.begin(), clientAddress.end(), '\\'), clientAddress.end());

	array<string, 2> handshake = { clientAddress, secret };
	_handshakes.push_back(handshake);

	return secret;
}

string HandshakeService::GetSecret(string clientAddress) {
	for (int index = 0; index < _handshakes.size(); index++) {
		if (_handshakes[index][HANDSHAKE_ARRAY_CLIENT_ADDRESS_INDEX] == clientAddress) {
			return _handshakes[index][HANDSHAKE_ARRAY_SECRET_INDEX];
		}
	}
	return AUTHENTIFICATION_ERROR_NO_HANDSHAKE;
}

void HandshakeService::RemoveHandshake(string clientAddress) {
	for (int index = 0; index < _handshakes.size(); index++) {
		if (_handshakes[index][HANDSHAKE_ARRAY_CLIENT_ADDRESS_INDEX] == clientAddress) {
			_handshakes.erase(_handshakes.begin() + index);
			break;
		}
	}
}