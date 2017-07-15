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

#include "../common/dto/ShoppingEntryDto.h"
#include "../common/utils/Tools.h"
#include "../controller/FileController.h"
#include "shared/ChangeService.h"
#include "xml/XmlService.h"

#define GET "GET"
#define ADD "ADD"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define SHOPPING_ENTRY_DATA_SIZE 8
#define WEBSITE "WEBSITE"

#ifndef SHOPPING_LIST_SERVICE_H
#define SHOPPING_LIST_SERVICE_H

class ShoppingListService
{
  private:
	std::string _shoppingListFile;
	std::vector<ShoppingEntryDto> _shoppingList;

	FileController _fileController;
	XmlService _xmlService;

	void loadShoppingList();
	void saveShoppingList(ChangeService, std::string);

	std::string getShoppingList();
	std::string getReducedString();

	bool addShoppingEntry(std::vector<std::string>, ChangeService, std::string);
	bool updateShoppingEntry(std::vector<std::string>, ChangeService, std::string);
	bool deleteShoppingEntry(int, ChangeService, std::string);

  public:
	ShoppingListService();
	~ShoppingListService();

	void Initialize(FileController);
	std::string PerformAction(std::string, std::vector<std::string>, ChangeService, std::string);
	void ReloadData();
};

#endif
