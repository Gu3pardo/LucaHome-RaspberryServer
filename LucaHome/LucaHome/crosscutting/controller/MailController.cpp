#include "MailController.h"

void MailController::SendMail(string address, int messageType, string data)
{
	string command = CMD_SEND_MAIL;

	if (address.length() < MAIL_MIN_ADDRESS_LENGTH)
	{
		syslog(LOG_CRIT, "Error! Address too short! Length: %d", address.length());
		return;
	}

	if (messageType != 0 && messageType != 1)
	{
		syslog(LOG_CRIT, "Error! Invalid message type: %d", messageType);
		return;
	}

	if (command.length() + data.length() > MAIL_MAX_DATA_LENGTH)
	{
		syslog(LOG_CRIT, "Error! Data too long! Length: %d", data.length());
		return;
	}

	char buffer[MAIL_MAX_DATA_LENGTH];
	int length;

	length = sprintf(buffer, "%s %s %d %s", command.c_str(), address.c_str(), messageType, data.c_str());

	string str(buffer);

	system(buffer);
}