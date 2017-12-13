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

#include "../common/dto/ShoppingEntryDto.h"
#include "../common/utils/Tools.h"
#include "../common/Constants.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#ifndef SHOPPING_LIST_SERVICE_H
#define SHOPPING_LIST_SERVICE_H

class ShoppingListService
{
private:
	std::string _shoppingListFile;
	std::vector<ShoppingEntryDto> _shoppingList;

	FileController _fileController;
	XmlService _xmlService;

	void saveShoppingList(ChangeService, std::string);

	std::string getJsonString();
	std::string getPhpString();

	bool addShoppingEntry(std::vector<std::string>, ChangeService, std::string);
	bool updateShoppingEntry(std::vector<std::string>, ChangeService, std::string);
	bool deleteShoppingEntry(int, ChangeService, std::string);

public:
	ShoppingListService();
	~ShoppingListService();

	void Initialize(FileController, std::string);
	std::string PerformAction(std::vector<std::string>, ChangeService, std::string);
	void LoadData();
};

#endif
