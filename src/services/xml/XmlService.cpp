#include "XmlService.h"

/* ------------------- Public ------------------- */

XmlService::XmlService()
{
}

XmlService::~XmlService()
{
}

std::string XmlService::GenerateBirthdaysXml(std::vector<BirthdayDto> birthdayList)
{
	XmlWriter writer;
	return writer.GenerateBirthdaysXml(birthdayList);
}

std::vector<BirthdayDto> XmlService::GetBirthdayList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseBirthdayList();
}

std::string XmlService::GenerateChangesXml(std::vector<ChangeDto> changeList)
{
	XmlWriter writer;
	return writer.GenerateChangesXml(changeList);
}

std::vector<ChangeDto> XmlService::GetChangeList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseChangeList();
}

InformationDto XmlService::GetInformation(std::string content)
{
	XmlParser parser(content);
	InformationDto information(
		parser.FindTag("author"),
		parser.FindTag("company"),
		parser.FindTag("contact"),
		parser.FindTag("builddate"),
		parser.FindTag("serverversion"),
		parser.FindTag("websiteversion"),
		parser.FindTag("temperaturelogversion"),
		parser.FindTag("appversion"),
		parser.FindTag("wearappversion"),
		parser.FindTag("accessappversion"),
		parser.FindTag("mediaserverversion"),
		parser.FindTag("wpfapplicationversion"));
	return information;
}

std::string XmlService::GenerateMapContentsXml(std::vector<MapContentDto> mapcontentList)
{
	XmlWriter writer;
	return writer.GenerateMapContentsXml(mapcontentList);
}

std::vector<MapContentDto> XmlService::GetMapContentList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseMapContentList();
}

std::string XmlService::GenerateListedMenuXml(std::vector<ListedMenuDto> listedMenuList)
{
	XmlWriter writer;
	return writer.GenerateListedMenuXml(listedMenuList);
}

std::vector<ListedMenuDto> XmlService::GetListedMenuList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseListedMenuList();
}

std::string XmlService::GenerateMenuXml(std::vector<MenuDto> menuList)
{
	XmlWriter writer;
	return writer.GenerateMenuXml(menuList);
}

std::vector<MenuDto> XmlService::GetMenuList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseMenuList();
}

std::string XmlService::GenerateSettingsXml(
	int port, int datagpio, int receivergpio, int raspberry, std::string alarmSound,
	std::string wakeUpSound, std::vector<std::string> areas, std::vector<std::string> sensors,
	std::vector<std::string> urls, std::string accessurl, std::vector<std::string> mediamirror,
	std::vector<WirelessSocketDto> sockets, std::vector<GpioDto> gpios, std::vector<ScheduleDto> schedules)
{
	XmlWriter writer;
	return writer.GenerateSettingsXml(
		port, datagpio, receivergpio, raspberry, alarmSound, wakeUpSound, areas, sensors, urls,
		accessurl, mediamirror, sockets, gpios, schedules);
}

int XmlService::GetPort(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("port").c_str());
}

int XmlService::GetDatagpio(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("datagpio").c_str());
}

int XmlService::GetReceivergpio(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("receivergpio").c_str());
}

int XmlService::GetRaspberry(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("raspberry").c_str());
}

std::string XmlService::GetAlarmSound(std::string content)
{
	XmlParser parser(content);
	return parser.FindTag("alarmsound").c_str();
}

std::string XmlService::GetWakeUpSound(std::string content)
{
	XmlParser parser(content);
	return parser.FindTag("wakeupsound").c_str();
}

std::vector<std::string> XmlService::GetAreaList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseAreaList();
}

std::vector<std::string> XmlService::GetSensorList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseSensorList();
}

std::vector<std::string> XmlService::GetUrlList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseUrlList();
}

std::string XmlService::GetAccessUrl(std::string content)
{
	XmlParser parser(content);
	return parser.ParseAccessUrl();
}

std::vector<std::string> XmlService::GetMediaMirrorList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseMediaMirrorList();
}

std::vector<GpioDto> XmlService::GetGpioList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseGpioList();
}

std::vector<ScheduleDto> XmlService::GetScheduleList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseScheduleList();
}

std::vector<WirelessSocketDto> XmlService::GetSocketList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseSocketList();
}

std::string XmlService::GenerateShoppingListXml(std::vector<ShoppingEntryDto> shoppingList)
{
	XmlWriter writer;
	return writer.GenerateShoppingListXml(shoppingList);
}

std::vector<ShoppingEntryDto> XmlService::GetShoppingList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseShoppingList();
}

std::string XmlService::GenerateTemperatureSettingsXml(int tempMin, int tempMax, int ledTempNormal, int ledTempLow, int ledTempHigh, bool tempControlActive)
{
	XmlWriter writer;
	return writer.GenerateTemperatureSettingsXml(tempMin, tempMax, ledTempNormal, ledTempLow, ledTempHigh, tempControlActive);
}

int XmlService::GetTempMin(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("tempmin").c_str());
}

int XmlService::GetTempMax(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("tempmax").c_str());
}

int XmlService::GetLEDTempNormal(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("ledtempnormal").c_str());
}

int XmlService::GetLEDTempLow(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("ledtemplow").c_str());
}

int XmlService::GetLEDTempHigh(std::string content)
{
	XmlParser parser(content);
	return atoi(parser.FindTag("ledtemphigh").c_str());
}

bool XmlService::IsTempControlActive(std::string content)
{
	XmlParser parser(content);
	int controlState = atoi(parser.FindTag("controlactive").c_str());
	if (controlState == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string XmlService::GenerateUsersXml(std::vector<UserDto> userList)
{
	XmlWriter writer;
	return writer.GenerateUsersXml(userList);
}

std::vector<UserDto> XmlService::GetUserList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseUserList();
}

std::string XmlService::GenerateLoggerXml(std::vector<LogDto> logList)
{
	XmlWriter writer;
	return writer.GenerateLoggerXml(logList);
}

std::vector<LogDto> XmlService::GetLogList(std::string content)
{
	XmlParser parser(content);
	return parser.ParseLogList();
}
