#include "menuservice.h"

/*===============PUBLIC==============*/

MenuService::MenuService() {
}

MenuService::~MenuService() {
}

void MenuService::initialize(FileController fileController) {
	_fileController = fileController;
	_menuFile = "/etc/default/lucahome/menu";
	_listedmenuFile = "/etc/default/lucahome/listedmenu";

	loadMenu();
	loadListedMenu();
}

std::string MenuService::performAction(std::string action,
		std::vector<std::string> data, ChangeService changeService,
		std::string username) {
	if (action == "GET") {
		if (data[4] == "MENU") {
			return getMenu();
		} else if (data[4] == "LISTEDMENU") {
			return getListedMenu();
		} else {
			return "Error 165:Invalid data for menu";
		}
	} else if (action == "ADD") {
		if (data[4] == "LISTEDMENU") {
			if (addListedMenu(data, changeService, username)) {
				return "addlistedmenu:1";
			} else {
				return "Error 169:Could not add listedmenu";
			}
		} else {
			return "Error 165:Invalid data for menu";
		}
	} else if (action == "UPDATE") {
		if (data[4] == "MENU") {
			if (data.size() == 11) {
				if (updateMenu(data, changeService, username)) {
					return "updateMenu:1";
				} else {
					return "Error 161:Could not update menu";
				}
			} else {
				return "Error 160:Wrong word size for menu";
			}
		} else if (data[4] == "LISTEDMENU") {
			if (data.size() == 9) {
				if (updateListedMenu(data, changeService, username)) {
					return "updateListedMenu:1";
				} else {
					return "Error 166:Could not update listedmenu";
				}
			} else {
				return "Error 167:Wrong word size for listedmenu";
			}
		} else {
			return "Error 165:Invalid data for menu";
		}
	} else if (action == "DELETE") {
		if (data[4] == "LISTEDMENU") {
			if (deleteListedMenu(atoi(data[5].c_str()), changeService, username)) {
				return "deletelistedmenu:1";
			} else {
				return "Error 168:Could not delete listedmenu";
			}
		} else {
			return "Error 165:Invalid data for menu";
		}
	} else if (action == "CLEAR") {
		if (clearMenu(data[4].c_str(), changeService, username)) {
			return "clearMenu:1";
		} else {
			return "Error 162:Could not clear menu";
		}
	} else {
		return "Error 163:Action not found for menu";
	}
}

/*==============PRIVATE==============*/

void MenuService::saveMenu(ChangeService changeService, std::string username) {
	std::string xmldata = _xmlService.generateMenuXml(_menu);
	_fileController.saveFile(_menuFile, xmldata);

	changeService.updateChange("Menu", username);
}

void MenuService::loadMenu() {
	std::string menuString = _fileController.readFile(_menuFile);
	_xmlService.setContent(menuString);

	_menu = _xmlService.getMenu();
}

std::string MenuService::getMenu() {
	std::stringstream out;

	for (int index = 0; index < _menu.size(); index++) {
		out << "{menu:"
				<< "{weekday:" << _menu[index].getWeekday() << "};"
				<< "{day:" << Tools::convertIntToStr(_menu[index].getDay()) << "};"
				<< "{month:" << Tools::convertIntToStr(_menu[index].getMonth()) << "};"
				<< "{year:" << Tools::convertIntToStr(_menu[index].getYear()) << "};"
				<< "{title:" << _menu[index].getTitle() << "};"
				<< "{description:" << _menu[index].getDescription() << "};"
				<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::updateMenu(std::vector<std::string> updateMenuData,
		ChangeService changeService, std::string username) {

	for (int index = 0; index < _menu.size(); index++) {
		if (_menu[index].getWeekday() == updateMenuData[5]) {
			Menu updateMenu(
					updateMenuData[5],
					atoi(updateMenuData[6].c_str()),
					atoi(updateMenuData[7].c_str()),
					atoi(updateMenuData[8].c_str()),
					updateMenuData[9],
					updateMenuData[10]);
			_menu[index] = updateMenu;

			saveMenu(changeService, username);
			loadMenu();

			syslog(LOG_INFO, "Updated menu %s", updateMenuData[5].c_str());

			return true;
		}
	}

	return false;
}

bool MenuService::clearMenu(std::string weekday, ChangeService changeService,
		std::string username) {

	for (int index = 0; index < _menu.size(); index++) {
		if (_menu[index].getWeekday() == weekday) {
			Menu clearMenu(weekday, -1, -1, -1, "Nothing defined", "");
			_menu[index] = clearMenu;

			saveMenu(changeService, username);
			loadMenu();

			syslog(LOG_INFO, "Cleared menu %s", weekday.c_str());

			return true;
		}
	}

	return false;
}

void MenuService::saveListedMenu(ChangeService changeService,
		std::string username) {
	std::string xmldata = _xmlService.generateListedMenuXml(_listedmenus);
	_fileController.saveFile(_listedmenuFile, xmldata);

	changeService.updateChange("Menu", username);
}

void MenuService::loadListedMenu() {
	std::string listedmenuString = _fileController.readFile(_listedmenuFile);
	_xmlService.setContent(listedmenuString);

	_listedmenus = _xmlService.getListedMenu();
}

std::string MenuService::getListedMenu() {
	std::stringstream out;

	for (int index = 0; index < _listedmenus.size(); index++) {
		out << "{listedmenu:"
				<< "{id:" << Tools::convertIntToStr(_listedmenus[index].getId()) << "};"
				<< "{description:" << _listedmenus[index].getDescription() << "};"
				<< "{rating:" << Tools::convertIntToStr(_listedmenus[index].getRating()) << "};"
				<< "{lastSuggestion:" << Tools::convertIntToStr(_listedmenus[index].isLastSuggestion()) << "};"
				<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::addListedMenu(std::vector<std::string> newListedMenuData,
		ChangeService changeService, std::string username) {
	ListedMenu newListedMenu(
			atoi(newListedMenuData[5].c_str()),
			newListedMenuData[6],
			atoi(newListedMenuData[7].c_str()),
			atoi(newListedMenuData[8].c_str()));
	_listedmenus.push_back(newListedMenu);

	saveListedMenu(changeService, username);
	loadListedMenu();

	syslog(LOG_INFO, "Added listedMenu %d", atoi(newListedMenuData[5].c_str()));

	return true;
}

bool MenuService::updateListedMenu(std::vector<std::string> updateListedMenuData,
		ChangeService changeService, std::string username) {
	ListedMenu updatedListedMenu(
			atoi(updateListedMenuData[5].c_str()),
			updateListedMenuData[6],
			atoi(updateListedMenuData[7].c_str()),
			atoi(updateListedMenuData[8].c_str()));

	for (int index = 0; index < _listedmenus.size(); index++) {
		if (_listedmenus[index].getId() == updatedListedMenu.getId()) {
			_listedmenus[index] = updatedListedMenu;

			saveListedMenu(changeService, username);
			loadListedMenu();

			syslog(LOG_INFO, "Updated listedmenu %d", atoi(updateListedMenuData[5].c_str()));

			return true;
		}
	}
	return false;
}

bool MenuService::deleteListedMenu(int id, ChangeService changeService,
		std::string username) {
	std::vector<ListedMenu>::iterator it = _listedmenus.begin();
	while (it != _listedmenus.end()) {
		if ((*it).getId() == id) {
			it = _listedmenus.erase(it);

			saveListedMenu(changeService, username);
			loadListedMenu();

			syslog(LOG_INFO, "Deleted listedmenu %d", id);

			return true;
		} else {
			++it;
		}
	}
	return false;
}
