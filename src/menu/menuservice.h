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
#include <syslog.h>

#include "menu.h"
#include "../changes/changeservice.h"
#include "../controller/filecontroller.h"
#include "../xml/xmlservice.h"

#include "../common/tools.h"

#ifndef MENUSERVICE_H
#define MENUSERVICE_H

class MenuService {
private:
	std::string _menuFile;
	std::vector<Menu> _menu;

	FileController _fileController;
	XmlService _xmlService;

	void saveMenu(ChangeService, std::string);
	void loadMenu();

	std::string getMenu();

	bool updateMenu(std::vector<std::string>, ChangeService, std::string);
	bool clearMenu(std::string, ChangeService, std::string);

public:
	MenuService();
	~MenuService();

	void initialize(FileController);

	std::string performAction(std::string, std::vector<std::string>,
			ChangeService, std::string);
};

#endif
