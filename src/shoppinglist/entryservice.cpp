#include "entryservice.h"

/*===============PUBLIC==============*/

EntryService::EntryService() {
}

EntryService::~EntryService() {
}

void EntryService::initialize(FileController fileController) {
	_fileController = fileController;

	_shoppingListFile = "/etc/default/lucahome/shoppinglist";

	loadEntries();
}

std::string EntryService::performAction(std::string action,
		std::vector<std::string> data, ChangeService changeService,
		std::string username) {
	if (action == "GET") {
		return getEntries();
	} else if (action == "ADD") {
		if (data.size() == 8) {
			if (addEntry(data, changeService, username)) {
				return "addEntry:1";
			} else {
				return "Error 150:Could not add shopping entry";
			}
		} else {
			return "Error 151:Wrong word size for shopping entry";
		}
	} else if (action == "UPDATE") {
		if (data.size() == 8) {
			if (updateEntry(data, changeService, username)) {
				return "updateEntry:1";
			} else {
				return "Error 152:Could not update shopping entry";
			}
		} else {
			return "Error 151:Wrong word size for shopping entry";
		}
	} else if (action == "DELETE") {
		if (deleteEntry(atoi(data[4].c_str()), changeService, username)) {
			return "deleteEntry:1";
		} else {
			return "Error 153:Could not delete shopping entry";
		}
	} else {
		return "Error 154:Action not found action for shopping entry";
	}
}

/*==============PRIVATE==============*/

void EntryService::saveEntries(ChangeService changeService,
		std::string username) {
	std::string xmldata = _xmlService.generateShoppingListXml(_entries);
	_fileController.saveFile(_shoppingListFile, xmldata);

	changeService.updateChange("ShoppingList", username);
}

void EntryService::loadEntries() {
	std::string entryString = _fileController.readFile(_shoppingListFile);
	_xmlService.setContent(entryString);

	_entries = _xmlService.getShoppingEntries();
}

std::string EntryService::getEntries() {
	std::stringstream out;

	for (int index = 0; index < _entries.size(); index++) {
		out << "{shopping_entry:"
				<< "{id:" << Tools::convertIntToStr(_entries[index].getId()) << "};"
				<< "{name:" << _entries[index].getName() << "};"
				<< "{group:" << _entries[index].getGroup() << "};"
				<< "{quantity:" << Tools::convertIntToStr(_entries[index].getQuantity()) << "};"
				<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool EntryService::addEntry(std::vector<std::string> newEntryData,
		ChangeService changeService, std::string username) {
	Entry newEntry(atoi(newEntryData[4].c_str()), newEntryData[5],
			newEntryData[6], atoi(newEntryData[7].c_str()));
	_entries.push_back(newEntry);

	saveEntries(changeService, username);
	loadEntries();

	syslog(LOG_INFO, "Added shopping entry %d", atoi(newEntryData[3].c_str()));

	return true;
}

bool EntryService::updateEntry(
		std::vector<std::string> updateEntryData,
		ChangeService changeService, std::string username) {
	Entry updateEntry(atoi(updateEntryData[4].c_str()), updateEntryData[5],
			updateEntryData[6], atoi(updateEntryData[7].c_str()));

	for (int index = 0; index < _entries.size(); index++) {
		if (_entries[index].getId() == updateEntry.getId()) {
			_entries[index] = updateEntry;

			saveEntries(changeService, username);
			loadEntries();

			syslog(LOG_INFO, "Updated shopping entry %d", atoi(updateEntryData[3].c_str()));

			return true;
		}
	}
	return false;
}

bool EntryService::deleteEntry(int id, ChangeService changeService,
		std::string username) {
	std::vector<Entry>::iterator it = _entries.begin();
	while (it != _entries.end()) {
		if ((*it).getId() == id) {
			it = _entries.erase(it);

			saveEntries(changeService, username);
			loadEntries();

			syslog(LOG_INFO, "Deleted shopping entry %d", id);

			return true;
		} else {
			++it;
		}
	}
	return false;
}
