#include "ContactService.h"

/*===============PUBLIC==============*/

ContactService::ContactService() {}

ContactService::~ContactService() {}

void ContactService::Initialize(string databaseName)
{
	_contactDatabase = ContactDatabase(databaseName);
}

string ContactService::PerformAction(vector<string> data)
{
	string username = data[USER_NAME_INDEX];
	string action = data[ACTION_INDEX];
	string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		return getJsonString();
	}

	else if (action == ADD)
	{
		if (data.size() == CONTACT_DATA_SIZE)
		{
			char error = addContact(data);
			if (!error)
			{
				return CONTACT_ADD_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Contact\",\"Error\":35,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return CONTACT_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == UPDATE)
	{
		if (data.size() == CONTACT_DATA_SIZE)
		{
			char error = updateContact(data);
			if (!error)
			{
				return CONTACT_UPDATE_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Contact\",\"Error\":35,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return CONTACT_ERROR_WRONG_WORD_SIZE;
	}

	else if (action == DELETE)
	{
		char error = deleteContact(actionParameter);
		if (!error)
		{
			return CONTACT_DELETE_SUCCESS;
		}

		stringstream actionAnswer;
		actionAnswer << "{\"Category\":\"Contact\",\"Error\":35,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
		return actionAnswer.str();
	}

	else if (action == MAIL)
	{
		if (data.size() == CONTACT_MAIL_MESSAGE_DATA_SIZE)
		{
			string error = writeMailToContact(data);
			if (error.length() == 0)
			{
				return CONTACT_MAIL_SUCCESS;
			}

			stringstream actionAnswer;
			actionAnswer << "{\"Category\":\"Contact\",\"Error\":35,\"Success\":false,\"Data\":\"" << error << "\"}\x00" << endl;
			return actionAnswer.str();
		}
		return CONTACT_ERROR_WRONG_WORD_SIZE;
	}

	return COMMAND_ERROR_NO_ACTION_FOUND;
}

void ContactService::Dispose()
{
	_contactDatabase.Dispose();
}

void ContactService::CheckContactBirthdayList()
{
	vector<Contact> contactList = _contactDatabase.GetList();

	for (int index = 0; index < contactList.size(); index++)
	{
		Contact contact = contactList[index];
		if (contact.HasBirthday() && contact.GetBirthdayRemindMe() && !contact.GetBirthdaySentReminder())
		{
			stringstream information;
			information << contact.GetName() << " has birthday today! It is the " << Tools::ConvertIntToStr(contact.GetAge()) << "th birthday!";
			MailController::SendMail(RECEIVER_MAIL, 0, information.str());
			contact.SetBirthdaySentReminder(true);
		}
		else if (!contact.HasBirthday() && contact.GetBirthdaySentReminder())
		{
			contact.SetBirthdaySentReminder(false);
		}
		_contactDatabase.Update(contact);
	}
}

/*==============PRIVATE==============*/

string ContactService::getJsonString()
{
	vector<Contact> contactList = _contactDatabase.GetList();

	stringstream data;
	for (int index = 0; index < contactList.size(); index++)
	{
		data << contactList[index].JsonString() << ",";
	}

	stringstream out;
	out << "{\"Category\":\"Contact\",\"Action\":\"Get\",\"Success\":true,\"Data\":["
		<< data.str().substr(0, data.str().size() - 1)
		<< "]}\x00" << endl;
	return out.str();
}

char ContactService::addContact(vector<string> newContactData)
{
	Contact newContact(
		newContactData[CONTACT_UUID_INDEX].c_str(),
		newContactData[CONTACT_NAME_INDEX].c_str(),
		newContactData[CONTACT_GROUP_INDEX].c_str(),
		newContactData[CONTACT_ADDRESS_INDEX].c_str(),
		newContactData[CONTACT_PHONE_HOME_INDEX].c_str(),
		newContactData[CONTACT_PHONE_MOBILE_INDEX].c_str(),
		newContactData[CONTACT_EMAIL_INDEX].c_str(),
		atoi(newContactData[CONTACT_BIRTHDAY_DAY_INDEX].c_str()),
		atoi(newContactData[CONTACT_BIRTHDAY_MONTH_INDEX].c_str()),
		atoi(newContactData[CONTACT_BIRTHDAY_YEAR_INDEX].c_str()),
		atoi(newContactData[CONTACT_BIRTHDAY_REMINDME_INDEX].c_str()) == 1,
		false);
	return _contactDatabase.Insert(newContact);
}

char ContactService::updateContact(vector<string> updateContactData)
{
	Contact updateContact(
		updateContactData[CONTACT_UUID_INDEX].c_str(),
		updateContactData[CONTACT_NAME_INDEX].c_str(),
		updateContactData[CONTACT_GROUP_INDEX].c_str(),
		updateContactData[CONTACT_ADDRESS_INDEX].c_str(),
		updateContactData[CONTACT_PHONE_HOME_INDEX].c_str(),
		updateContactData[CONTACT_PHONE_MOBILE_INDEX].c_str(),
		updateContactData[CONTACT_EMAIL_INDEX].c_str(),
		atoi(updateContactData[CONTACT_BIRTHDAY_DAY_INDEX].c_str()),
		atoi(updateContactData[CONTACT_BIRTHDAY_MONTH_INDEX].c_str()),
		atoi(updateContactData[CONTACT_BIRTHDAY_YEAR_INDEX].c_str()),
		atoi(updateContactData[CONTACT_BIRTHDAY_REMINDME_INDEX].c_str()) == 1,
		false);
	return _contactDatabase.Update(updateContact);
}

char ContactService::deleteContact(string deleteUuid)
{
	return _contactDatabase.Delete(deleteUuid);
}

string ContactService::writeMailToContact(vector<string> data)
{
	string uuid = data[CONTACT_UUID_INDEX].c_str();
	Contact contact = _contactDatabase.GetByUuid(uuid);
	if (contact.GetEMail().length() <= 0) {
		return "Contact has no email!";
	}

	string message = data[CONTACT_MAIL_MESSAGE_INDEX].c_str();
	if (message.length() <= 0) {
		return "Message is empty!";
	}

	MailController::SendMail(contact.GetEMail(), 0, message);

	return "";
}
