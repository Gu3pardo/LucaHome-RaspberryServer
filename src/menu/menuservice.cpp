#include "menuservice.h"

/*===============PUBLIC==============*/

MenuService::MenuService() {
}

MenuService::~MenuService() {
}

void MenuService::initialize(FileController fileController) {
	_fileController = fileController;
	_menuFile = "/etc/default/lucahome/menu";

	loadMenu();
}

std::string MenuService::performAction(std::string action,
		std::vector<std::string> data, ChangeService changeService,
		std::string username) {
	if (action == "GET") {
		return getMenu();
	} else if (action == "UPDATE") {
		if (data.size() == 10) {
			if (updateMenu(data, changeService, username)) {
				return "updateMenu:1";
			} else {
				return "Error 161:Could not update menu";
			}
		} else {
			return "Error 160:Wrong word size for menu";
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
		out << "{menu:" << "{weekday:" << _menu[index].getWeekday() << "};"
				<< "{day:" << Tools::convertIntToStr(_menu[index].getDay())
				<< "};" << "{month:"
				<< Tools::convertIntToStr(_menu[index].getMonth()) << "};"
				<< "{year:" << Tools::convertIntToStr(_menu[index].getYear())
				<< "};" << "{title:" << _menu[index].getTitle() << "};"
				<< "{description:" << _menu[index].getDescription() << "};"
				<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::updateMenu(std::vector<std::string> updateMenuData,
		ChangeService changeService, std::string username) {

	for (int index = 0; index < _menu.size(); index++) {
		if (_menu[index].getWeekday() == updateMenuData[4]) {
			Menu updateMenu(updateMenuData[4], atoi(updateMenuData[5].c_str()),
					atoi(updateMenuData[6].c_str()),
					atoi(updateMenuData[7].c_str()), updateMenuData[8],
					updateMenuData[9]);
			_menu[index] = updateMenu;

			saveMenu(changeService, username);
			loadMenu();

			syslog(LOG_INFO, "Updated menu %s", updateMenuData[3].c_str());

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
