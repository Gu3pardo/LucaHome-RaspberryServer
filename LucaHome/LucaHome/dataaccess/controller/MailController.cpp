#include "MailController.h"

MailController::MailController() {}

MailController::~MailController() {}

//--------------------------Public-----------------------//

void MailController::SendMail(string message)
{
	string command = CMD_SEND_SIMPLE_MAIL;

	if (command.length() + message.length() > MAIL_MAX_MESSAGE_LENGTH)
	{
		syslog(LOG_CRIT, "Error! Message too long! Message: %s; Length: %d", message.c_str(), message.length());
		return;
	}

	char buffer[MAIL_MAX_MESSAGE_LENGTH];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), message.c_str());

	string str(buffer);

	system(buffer);
}

void MailController::SendMailWithImage(string imagePath)
{
	string command = CMD_SEND_IMAGE_MAIL;

	if (command.length() + imagePath.length() > MAIL_MAX_MESSAGE_LENGTH)
	{
		syslog(LOG_CRIT, "Error! ImagePath too long! ImagePath: %s; Length: %d", imagePath.c_str(), imagePath.length());
		return;
	}

	char buffer[MAIL_MAX_MESSAGE_LENGTH];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), imagePath.c_str());

	string str(buffer);

	system(buffer);
}
