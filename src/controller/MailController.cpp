#include "MailController.h"

MailController::MailController()
{
}

MailController::~MailController()
{
}

//--------------------------Public-----------------------//

void MailController::SendMail(std::string message)
{
	std::string command = SEND_SIMPLE_MAIL;

	if (command.length() + message.length() > MAX_MESSAGE_LENGTH)
	{
		syslog(LOG_INFO, "Error! Message too long! Message: %s; Length: %d", message.c_str(), message.length());
		return;
	}

	syslog(LOG_INFO, "Send mail with message: %s", message.c_str());

	char buffer[MAX_MESSAGE_LENGTH];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), message.c_str());

	std::string str(buffer);

	system(buffer);
}

void MailController::SendMailWithImage(std::string imagePath)
{
	std::string command = SEND_IMAGE_MAIL;

	if (command.length() + imagePath.length() > MAX_MESSAGE_LENGTH)
	{
		syslog(LOG_INFO, "Error! ImagePath too long! ImagePath: %s; Length: %d", imagePath.c_str(), imagePath.length());
		return;
	}

	syslog(LOG_INFO, "Send mail with imagePath: %s", imagePath.c_str());

	char buffer[MAX_MESSAGE_LENGTH];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), imagePath.c_str());

	std::string str(buffer);

	system(buffer);
}
