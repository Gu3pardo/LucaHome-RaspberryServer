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

	LoadData();
}

std::string MenuService::PerformAction(std::vector<std::string> data, ChangeService changeService, std::string username)
{
	std::string action = data[ACTION_INDEX];
	std::string actionParameter = data[ACTION_PARAMETER_INDEX];

	if (action == GET)
	{
		if (actionParameter == MENU)
		{
			return getMenuJsonString();
		}
		else if (actionParameter == MENU_PHP)
		{
			return getMenuPhpString();
		}
		else if (actionParameter == LISTEDMENU)
		{
			return getListedMenuJsonString();
		}
		else if (actionParameter == LISTEDMENU_PHP)
		{
			return getListedMenuPhpString();
		}
		return MENU_ERROR_NR_165;
	}

	else if (action == ADD)
	{
		if (actionParameter == LISTEDMENU)
		{
			if (data.size() == MENU_DATA_SIZE)
			{
				if (addListedMenu(data, changeService, username))
				{
					return LISTED_MENU_ADD_SUCCESS;
				}
				return LISTED_MENU_ERROR_NR_169;
			}
			return MENU_ERROR_NR_160;
		}
		return MENU_ERROR_NR_165;
	}

	else if (action == UPDATE)
	{
		if (actionParameter == MENU)
		{
			if (data.size() == MENU_DATA_SIZE)
			{
				if (updateMenu(data, changeService, username))
				{
					return MENU_UPDATE_SUCCESS;
				}
				return MENU_ERROR_NR_161;
			}
			return MENU_ERROR_NR_160;
		}
		else if (actionParameter == LISTEDMENU)
		{
			if (data.size() == LISTEDMENU_DATA_SIZE)
			{
				if (updateListedMenu(data, changeService, username))
				{
					return LISTED_MENU_UPDATE_SUCCESS;
				}
				return LISTED_MENU_ERROR_NR_166;
			}
			return LISTED_MENU_ERROR_NR_167;
		}
		return MENU_ERROR_NR_165;
	}

	else if (action == DELETE)
	{
		if (actionParameter == LISTEDMENU)
		{
			if (deleteListedMenu(atoi(data[LISTEDMENU_ID_INDEX].c_str()), changeService, username))
			{
				return LISTED_MENU_DELETE_SUCCESS;
			}
			return LISTED_MENU_ERROR_NR_168;
		}
		return MENU_ERROR_NR_165;
	}

	else if (action == CLEAR)
	{
		if (clearMenu(actionParameter.c_str(), changeService, username))
		{
			return MENU_CLEAR_SUCCESS;
		}
		return MENU_ERROR_NR_162;
	}

	return MENU_ERROR_NR_163;
}

void MenuService::LoadData()
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

std::string MenuService::getMenuJsonString()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _menuList.size(); index++)
	{
		MenuDto menu = _menuList[index];
		data << menu.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

std::string MenuService::getMenuPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _menuList.size(); index++)
	{
		out << _menuList[index].PhpString();
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::updateMenu(std::vector<std::string> updateMenuData, ChangeService changeService, std::string username)
{
	std::string weekday = updateMenuData[MENU_WEEKDAY_INDEX].c_str();

	for (int index = 0; index < _menuList.size(); index++)
	{
		if (_menuList[index].GetWeekday() == weekday)
		{
			_menuList[index].SetDay(atoi(updateMenuData[MENU_DAY_INDEX].c_str()));
			_menuList[index].SetMonth(atoi(updateMenuData[MENU_MONTH_INDEX].c_str()));
			_menuList[index].SetYear(atoi(updateMenuData[MENU_YEAR_INDEX].c_str()));

			_menuList[index].SetTitle(updateMenuData[MENU_TITLE_INDEX].c_str());
			_menuList[index].SetDescription(updateMenuData[MENU_DESCRIPTION_INDEX].c_str());

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

std::string MenuService::getListedMenuJsonString()
{
	std::stringstream out;
	out << "{\"Data\":[";

	std::stringstream data;
	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		ListedMenuDto listedMenu = _listedMenuList[index];
		data << listedMenu.JsonString() << ",";
	}

	out << data.str().substr(0, data.str().size() - 1) << "]}" << "\x00" << std::endl;

	return out.str();
}

std::string MenuService::getListedMenuPhpString()
{
	std::stringstream out;

	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		out << _listedMenuList[index].PhpString();
	}

	out << "\x00" << std::endl;

	return out.str();
}

bool MenuService::addListedMenu(std::vector<std::string> newListedMenuData, ChangeService changeService, std::string username)
{
	ListedMenuDto newListedMenu(
		atoi(newListedMenuData[LISTEDMENU_ID_INDEX].c_str()),
		newListedMenuData[LISTEDMENU_TITLE_INDEX],
		newListedMenuData[LISTEDMENU_DESCRIPTION_INDEX],
		atoi(newListedMenuData[LISTEDMENU_RATING_INDEX].c_str()),
		atoi(newListedMenuData[LISTEDMENU_USE_COUNTER_INDEX].c_str()));
	_listedMenuList.push_back(newListedMenu);

	saveListedMenu(changeService, username);
	loadListedMenu();

	return true;
}

bool MenuService::updateListedMenu(std::vector<std::string> updateListedMenuData, ChangeService changeService, std::string username)
{
	int id = atoi(updateListedMenuData[LISTEDMENU_ID_INDEX].c_str());

	for (int index = 0; index < _listedMenuList.size(); index++)
	{
		if (_listedMenuList[index].GetId() == id)
		{
			_listedMenuList[index].SetTitle(updateListedMenuData[LISTEDMENU_TITLE_INDEX].c_str());
			_listedMenuList[index].SetDescription(updateListedMenuData[LISTEDMENU_DESCRIPTION_INDEX].c_str());
			_listedMenuList[index].SetRating(atoi(updateListedMenuData[LISTEDMENU_RATING_INDEX].c_str()));
			_listedMenuList[index].SetUseCount(atoi(updateListedMenuData[LISTEDMENU_USE_COUNTER_INDEX].c_str()));

			saveListedMenu(changeService, username);
			loadListedMenu();

			return true;
		}
	}
	return false;
}

bool MenuService::deleteListedMenu(int id, ChangeService changeService, std::string username)
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
