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

#include "entry.h"
#include "../changes/changeservice.h"
#include "../common/tools.h"
#include "../controller/filecontroller.h"
#include "../xml/xmlservice.h"

#ifndef ENTRYSERVICE_H
#define ENTRYSERVICE_H

class EntryService {
private:
	std::string _shoppingListFile;
	std::vector<Entry> _entries;

	FileController _fileController;
	XmlService _xmlService;

	void saveEntries(ChangeService, std::string);
	void loadEntries();

	std::string getEntries();

	bool addEntry(std::vector<std::string>, ChangeService, std::string);
	bool updateEntry(std::vector<std::string>, ChangeService, std::string);
	bool deleteEntry(int, ChangeService, std::string);

public:
	EntryService();
	~EntryService();

	void initialize(FileController);

	std::string performAction(std::string, std::vector<std::string>,
			ChangeService, std::string);
};

#endif
