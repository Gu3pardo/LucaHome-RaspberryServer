#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../common/dto/ListedMenuDto.h"
#include "../common/dto/MenuDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef MENUSERVICE_H
#define MENUSERVICE_H

class MenuService
{
private:
	std::string _menuFile;
	std::string _listedMenuFile;
	std::vector<MenuDto> _menuList;
	std::vector<ListedMenuDto> _listedMenuList;

	FileController _fileController;
	XmlService _xmlService;

	void loadMenu();
	void saveMenu(ChangeService, std::string);

	std::string getMenuJsonString();
	std::string getMenuPhpString();

	bool updateMenu(std::vector<std::string>, ChangeService, std::string);
	bool clearMenu(std::string, ChangeService, std::string);

	void loadListedMenu();
	void saveListedMenu(ChangeService, std::string);

	std::string getListedMenuJsonString();
	std::string getListedMenuPhpString();

	bool addListedMenu(std::vector<std::string>, ChangeService, std::string);
	bool updateListedMenu(std::vector<std::string>, ChangeService, std::string);
	bool deleteListedMenu(int, ChangeService, std::string);

public:
	MenuService();
	~MenuService();

	void Initialize(FileController, std::string, std::string);
	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);
	void LoadData();
};

#endif
