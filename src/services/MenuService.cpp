#include "MenuService.h"

/*===============PUBLIC==============*/

MenuService::MenuService()
{
}

MenuService::~MenuService()
{
}

void MenuService::Initialize(FileController fileController, std::string menuFile, std::string listedMenuFile)
{
	_fileController = fileController;
	_menuFile = menuFile;
	_listedMenuFile = listedMenuFile;

	loadMenu();
	loadListedMenu();
}

std::string MenuService::PerformAction(std::string action, std::vector<std::string> data, ChangeService changeService, std::string username)
{
	if (action == GET)
	{
		if (data[4] == MENU)
		{
			if (data.size() == 6) {
				if (data[5] == REDUCED) {
					return getReducedString();
				}
			}
			else {
				return getMenu();
			}
		}
		else if (data[4] == LISTEDMENU)
		{
			if (data.size() == 6) {
				if (data[5] == REDUCED) {
					return getListedMenuReduced();
				}
			}
			else {
			return getListedMenu();
			}
		}
		else
		{
			return "Error 165:Invalid data for menu";
		}
	}
	else if (action == ADD)
	{
		if (data[4] == LISTEDMENU)
		{
			if (data.size() == MENU_DATA_SIZE)
			{
				if (addListedMenu(data, changeService, username))
				{
					return "addlistedmenu:1";
				}
				else
				{
					return "Error 169:Could not add listedmenu";
				}
			}
			else
			{
				return "Error 160:Wrong word size for menu";
			}
		}
		else
		{
			return "Error 165:Invalid data for menu";
		}
	}
	else if (action == UPDATE)
	{
		if (data[4] == MENU)
		{
			if (data.size() == MENU_DATA_SIZE)
			{
				if (updateMenu(data, changeService, username))
				{
					return "updateMenu:1";
				}
				else
				{
					return "Error 161:Could not update menu";
				}
			}
			else
			{
				return "Error 160:Wrong word size for menu";
			}
		}
		else if (data[4] == LISTEDMENU)
		{
			if (data.size() == LISTEDMENU_DATA_SIZE)
			{
				if (updateListedMenu(data, changeService, username))
				{
					return "updateListedMenu:1";
				}
				else
				{
					return "Error 166:Could not update listedmenu";
				}
			}
			else
			{
				return "Error 167:Wrong word size for listedmenu";
			}
		}
		else
		{
			return "Error 165:Invalid data for menu";
		}
	}
	else if (action == DELETE)
	{
		if (data[4] == LISTEDMENU)
		{
			if (deleteListedMenu(atoi(data[5].c_str()), changeService, username))
			{
				return "deletelistedmenu:1";
			}
			else
			{
				return "Error 168:Could not delete listedmenu";
			}
		}
		else
		{
			return "Error 165:Invalid data for menu";
		}
	}
	else if (action == CLEAR)
	{
		if (clearMenu(data[4].c_str(), changeService, username))
		{
			return "clearMenu:1";
		}
		else
		{
			return "Error 162:Could not clear menu";
		}
	}
	else
	{
		return "Error 163:Action not found for menu";
	}
}

void MenuService::ReloadData()
{
	loadMenu();
	loadListedMenu();
}

/*==============PRIVATE==============*/

void MenuService::loadMenu()
{
	std::string menuString = _fileController.ReadFile(_menuFile);
	_menuList = _xmlService.GetMenuList(menuString);
}

void MenuService::saveMenu(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateMenuXml(_menuList);
	_fileController.SaveFile(_menuFile, xmldata);

	changeService.UpdateChange("Menu", username);
}

std::string MenuService::getMenu()
{
	std::stringstream out;

	for (int index = 0; index < _menuList.size(); index++)
	{
		out << "{menu:"
			<< "{weekday:" << _menuList[index].GetWeekday() << "};"
			<< "{day:" << Tools::ConvertIntToStr(_menuList[index].GetDay()) << "};"
			<< "{month:" << Tools::ConvertIntToStr(_menuList[index].GetMonth()) << "};"
			<< "{year:" << Tools::ConvertIntToStr(_menuList[index].GetYear()) << "};"
			<< "{title:" << _menuList[index].GetTitle() << "};"
			<< "{description:" << _menuList[index].GetDescription() << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string MenuService::getReducedString()
{
	std::stringstream out;

	for (int index = 0; index < _menuList.size(); index++)
	{
		out << "menu::"
			<< _menuList[index].GetWeekday() << "::"
			<< Tools::ConvertIntToStr(_menuList[index].GetDay()) << "::"
			<< Tools::ConvertIntToStr(_menuList[index].GetMonth()) << "::"
			<< Tools::ConvertIntToStr(_menuList[index].GetYear()) << "::"
			<< _menuList[index].GetTitle() << "::"
			<< _menuList[index].GetDescription() << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::updateMenu(std::vector<std::string> updateMenuData, ChangeService changeService, std::string username)
{

	for (int index = 0; index < _menuList.size(); index++)
	{
		if (_menuList[index].GetWeekday() == updateMenuData[5])
		{
			MenuDto updateMenu(
				updateMenuData[5],
				atoi(updateMenuData[6].c_str()),
				atoi(updateMenuData[7].c_str()),
				atoi(updateMenuData[8].c_str()),
				updateMenuData[9],
				updateMenuData[10]);
			_menuList[index] = updateMenu;

			saveMenu(changeService, username);
			loadMenu();

			return true;
		}
	}

	return false;
}

bool MenuService::clearMenu(std::string weekday, ChangeService changeService, std::string username)
{

	for (int index = 0; index < _menuList.size(); index++)
	{
		if (_menuList[index].GetWeekday() == weekday)
		{
			MenuDto clearMenu(weekday, -1, -1, -1, "Nothing defined", "");
			_menuList[index] = clearMenu;

			saveMenu(changeService, username);
			loadMenu();

			return true;
		}
	}

	return false;
}

void MenuService::saveListedMenu(ChangeService changeService, std::string username)
{
	std::string xmldata = _xmlService.GenerateListedMenuXml(_listedMenuList);
	_fileController.SaveFile(_listedMenuFile, xmldata);

	changeService.UpdateChange("Menu", username);
}

void MenuService::loadListedMenu()
{
	std::string listedmenuFileContent = _fileController.ReadFile(_listedMenuFile);
	_listedMenuList = _xmlService.GetListedMenuList(listedmenuFileContent);
}

std::string MenuService::getListedMenu()
{
	std::stringstream out;

	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		out << "{listedmenu:"
			<< "{id:" << Tools::ConvertIntToStr(_listedMenuList[index].GetId()) << "};"
			<< "{description:" << _listedMenuList[index].GetDescription() << "};"
			<< "{rating:" << Tools::ConvertIntToStr(_listedMenuList[index].GetRating()) << "};"
			<< "{lastSuggestion:" << Tools::ConvertIntToStr(_listedMenuList[index].IsLastSuggestion()) << "};"
			<< "};";
	}

	out << "\x00" << std::endl;

	return out.str();
}

std::string MenuService::getListedMenuReduced()
{
	std::stringstream out;

	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		out << "listedmenu::"
			<< Tools::ConvertIntToStr(_listedMenuList[index].GetId()) << "::"
			<< _listedMenuList[index].GetDescription() << "::"
			<< Tools::ConvertIntToStr(_listedMenuList[index].GetRating()) << "::"
			<< Tools::ConvertIntToStr(_listedMenuList[index].IsLastSuggestion()) << ";";
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::addListedMenu(std::vector<std::string> newListedMenuData, ChangeService changeService, std::string username)
{
	ListedMenuDto newListedMenu(
		atoi(newListedMenuData[5].c_str()),
		newListedMenuData[6],
		atoi(newListedMenuData[7].c_str()),
		atoi(newListedMenuData[8].c_str()));
	_listedMenuList.push_back(newListedMenu);

	saveListedMenu(changeService, username);
	loadListedMenu();

	return true;
}

bool MenuService::updateListedMenu(std::vector<std::string> updateListedMenuData, ChangeService changeService, std::string username)
{
	ListedMenuDto updatedListedMenu(
		atoi(updateListedMenuData[5].c_str()),
		updateListedMenuData[6],
		atoi(updateListedMenuData[7].c_str()),
		atoi(updateListedMenuData[8].c_str()));

	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		if (_listedMenuList[index].GetId() == updatedListedMenu.GetId())
		{
			_listedMenuList[index] = updatedListedMenu;

			saveListedMenu(changeService, username);
			loadListedMenu();

			return true;
		}
	}
	return false;
}

bool MenuService::deleteListedMenu(int id, ChangeService changeService,
	std::string username)
{
	std::vector<ListedMenuDto>::iterator it = _listedMenuList.begin();
	while (it != _listedMenuList.end())
	{
		if ((*it).GetId() == id)
		{
			it = _listedMenuList.erase(it);

			saveListedMenu(changeService, username);
			loadListedMenu();

			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}
