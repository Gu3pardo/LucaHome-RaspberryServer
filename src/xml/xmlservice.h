#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>
#include <syslog.h>

#include "../remote/gpio.h"
#include "../remote/schedule.h"
#include "../remote/socket.h"

#include "../authentification/user.h"
#include "../birthdays/birthday.h"
#include "../changes/change.h"
#include "../informations/information.h"
#include "../menu/listedmenu.h"
#include "../menu/menu.h"
#include "../movies/movie.h"
#include "../shoppinglist/entry.h"

#include "../flatmap/mapcontent.h"
#include "../flatmap/point.h"

#include "../logger/log.h"

#include "xmlparser.h"
#include "xmlwriter.h"

#ifndef XMLSERVICE_H
#define XMLSERVICE_H

class XmlService {

private:
	std::string content;

public:
	XmlService();
	XmlService (std::string);
	~XmlService();

	static std::string generateBirthdaysXml(std::vector<Birthday>);
	static std::string generateChangesXml(std::vector<Change>);
	static std::string generateListedMenuXml(std::vector<ListedMenu>);
	static std::string generateMapContentsXml(std::vector<MapContent>);
	static std::string generateMenuXml(std::vector<Menu>);
	static std::string generateMoviesXml(std::vector<Movie>);
	static std::string generateSettingsXml(int, int, int, int, std::string,
			std::string, std::vector<std::string>, std::vector<std::string>,
			std::vector<std::string>, std::string, std::vector<std::string>,
			std::vector<Socket>, std::vector<Gpio>, std::vector<Schedule>);
	static std::string generateShoppingListXml(std::vector<Entry>);
	static std::string generateUsersXml(std::vector<User>);
	static std::string generateLoggerXml(std::vector<Log>);

	void setContent(std::string);
	std::string getContent();

	std::vector<Birthday> getBirthdays();

	std::vector<Change> getChanges();

	Information getInformation();

	std::vector<MapContent> getMapContents();

	std::vector<ListedMenu> getListedMenu();
	std::vector<Menu> getMenu();

	std::vector<Movie> getMovies();

	int getPort();
	int getDatagpio();
	int getReceivergpio();
	int getRaspberry();

	std::string getAlarmSound();
	std::string getWakeUpSound();

	std::vector<std::string> getAreas();
	std::vector<std::string> getSensors();
	std::vector<std::string> getUrls();

	std::string getAccessUrl();
	std::vector<std::string> getMediaMirror();

	std::vector<Gpio> getGpios();
	std::vector<Schedule> getSchedules();
	std::vector<Socket> getSockets();

	std::vector<Entry> getShoppingEntries();

	std::vector<User> getUsers();

	std::vector<Log> getLogs();
};

#endif
