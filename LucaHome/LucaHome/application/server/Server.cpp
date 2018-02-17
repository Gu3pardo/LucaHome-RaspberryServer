#include "Server.h"

Server::Server() {}

Server::~Server() {}

void Server::Run()
{
	pthread_t serverThread;
	pthread_create(&serverThread, NULL, server, NULL);
	pthread_join(serverThread, NULL);
}

void *server(void *arg) {
	syslog(LOG_INFO, "Server started!");

	int socketResult, connection, answer, clientLength;
	struct sockaddr_in clientAddress, serverAddress;
	char message[BUFFER_LENGTH];

	int port = SERVER_PORT;

	socketResult = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketResult < 0) {
		syslog(LOG_CRIT, "Cant't open socket");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	connection = bind(socketResult, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	if (connection < 0) {
		syslog(LOG_CRIT, "Can't bind socket to port %d", port);
		exit(1);
	}

	syslog(LOG_INFO, "Server listen on port %u", port);

	while (1) {
		memset(message, 0x0, BUFFER_LENGTH);
		clientLength = sizeof(clientAddress);

		answer = recvfrom(socketResult, message, BUFFER_LENGTH, 0, (struct sockaddr *) &clientAddress, (socklen_t*)&clientLength);

		if (answer < 0) {
			syslog(LOG_ERR, "Can't receive data");
			continue;
		}
		else {
			syslog(LOG_INFO, "Received: %s", message);

			string response = CommandHandler::getInstance()->ExecuteCommand(message, CMD_SOURCE_EXTERNAL);

			int sendResult = sendto(socketResult, response.c_str(), strlen(response.c_str()), 0, (struct sockaddr *) &clientAddress, clientLength);
			if (sendResult < 0) {
				syslog(LOG_ERR, "Can't send data");
			}
		}
	}

	close(socketResult);
	syslog(LOG_INFO, "Exiting *server");
	pthread_exit(NULL);
}