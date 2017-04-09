#include "mailservice.h"

MailService::MailService() {
}

MailService::~MailService() {
}

//--------------------------Public-----------------------//

void MailService::sendMail(std::string message) {
	int maxMessageLength = 512;
	std::string command = "python /etc/default/lucahome/mail.py";

	if (command.length() + message.length() > maxMessageLength) {
		syslog(LOG_INFO, "Error! Message too long! Message: %s; Length: %d",
				message.c_str(), message.length());
		return;
	}

	syslog(LOG_INFO, "Send mail with message: %s", message.c_str());

	char buffer[maxMessageLength];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), message.c_str());

	std::string str(buffer);

	system(buffer);
}

void MailService::sendMailWithAttachement(std::string imagePath) {
	int maxMessageLength = 512;
	std::string command = "python /etc/default/lucahome/mailWithAttachement.py";

	if (command.length() + imagePath.length() > maxMessageLength) {
		syslog(LOG_INFO, "Error! ImagePath too long! ImagePath: %s; Length: %d",
				imagePath.c_str(), imagePath.length());
		return;
	}

	syslog(LOG_INFO, "Send mail with imagePath: %s", imagePath.c_str());

	char buffer[maxMessageLength];
	int length;

	length = sprintf(buffer, "%s %s", command.c_str(), imagePath.c_str());

	std::string str(buffer);

	system(buffer);
}
