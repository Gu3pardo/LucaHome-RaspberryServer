#include "XmlWriter.h"

/* ------------------- Public ------------------- */

XmlWriter::XmlWriter()
{
}

XmlWriter::~XmlWriter()
{
}

std::string XmlWriter::GenerateBirthdaysXml(std::vector<BirthdayDto> birthdayList)
{
	std::stringstream xml;

	xml << "<birthdays>" << std::endl;
	for (int index = 0; index < birthdayList.size(); index++)
	{
		xml << birthdayList[index].GetName() << ":"
			<< Tools::ConvertIntToStr(birthdayList[index].GetDay()) << ":"
			<< Tools::ConvertIntToStr(birthdayList[index].GetMonth()) << ":"
			<< Tools::ConvertIntToStr(birthdayList[index].GetYear()) << ";"
			<< std::endl;
	}
	xml << "</birthdays>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateChangesXml(std::vector<ChangeDto> changelist)
{
	std::stringstream xml;

	xml << "<changes>" << std::endl;
	for (int index = 0; index < changelist.size(); index++)
	{
		xml << changelist[index].GetType() << ":"
			<< Tools::ConvertIntToStr(changelist[index].GetHour()) << ":"
			<< Tools::ConvertIntToStr(changelist[index].GetMinute()) << ":"
			<< Tools::ConvertIntToStr(changelist[index].GetDay()) << ":"
			<< Tools::ConvertIntToStr(changelist[index].GetMonth()) << ":"
			<< Tools::ConvertIntToStr(changelist[index].GetYear()) << ":"
			<< changelist[index].GetUser() << ";"
			<< std::endl;
	}
	xml << "</changes>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateListedMenuXml(std::vector<ListedMenuDto> listedmenus)
{
	std::stringstream xml;

	xml << "<listedmenu>" << std::endl;
	for (int index = 0; index < listedmenus.size(); index++)
	{
		xml << Tools::ConvertIntToStr(listedmenus[index].GetId()) << ":"
			<< listedmenus[index].GetDescription() << ":"
			<< Tools::ConvertIntToStr(listedmenus[index].GetRating()) << ":"
			<< Tools::ConvertIntToStr(listedmenus[index].IsLastSuggestion()) << ";"
			<< std::endl;
	}
	xml << "</listedmenu>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateMapContentsXml(std::vector<MapContentDto> mapcontents)
{
	std::stringstream xml;

	xml << "<mapcontent>" << std::endl;
	for (int index = 0; index < mapcontents.size(); index++)
	{
		xml << Tools::ConvertIntToStr(mapcontents[index].GetId()) << ":"
			<< mapcontents[index].GetPosition().GetString() << ":"
			<< Tools::ConvertIntToStr(mapcontents[index].GetType()) << ":"
			<< mapcontents[index].GetSchedulesString() << ":"
			<< mapcontents[index].GetSocketsString() << ":"
			<< mapcontents[index].GetTemperatureArea() << ":"
			<< Tools::ConvertIntToStr(mapcontents[index].GetVisibility()) << ";"
			<< std::endl;
	}
	xml << "</mapcontent>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateMenuXml(std::vector<MenuDto> menu)
{
	std::stringstream xml;

	for (int index = 0; index < menu.size(); index++)
	{
		xml << "<" << menu[index].GetWeekday() << ">"
			<< Tools::ConvertIntToStr(menu[index].GetDay()) << ":"
			<< Tools::ConvertIntToStr(menu[index].GetMonth()) << ":"
			<< Tools::ConvertIntToStr(menu[index].GetYear()) << ":"
			<< menu[index].GetTitle() << ":"
			<< menu[index].GetDescription()
			<< "</" << menu[index].GetWeekday() << ">"
			<< std::endl;
	}

	return xml.str();
}

std::string XmlWriter::GenerateSettingsXml(
	int port, int datagpio, int receivergpio, int raspberry, std::string alarmsound,
	std::string wakeUpSound, std::vector<std::string> areas, std::vector<std::string> sensors,
	std::vector<std::string> urls, std::string accessurl, std::vector<std::string> mediamirror,
	std::vector<WirelessSocketDto> sockets, std::vector<GpioDto> gpios, std::vector<ScheduleDto> schedules)
{
	std::stringstream xml;

	xml << "<port>" << Tools::ConvertIntToStr(port) << "</port>" << std::endl << std::endl;

	xml << "<datagpio>" << Tools::ConvertIntToStr(datagpio) << "</datagpio>" << std::endl << std::endl;

	xml << "<receivergpio>" << Tools::ConvertIntToStr(receivergpio) << "</receivergpio>" << std::endl << std::endl;

	xml << "<raspberry>" << Tools::ConvertIntToStr(raspberry) << "</raspberry>" << std::endl << std::endl;

	xml << "<alarmsound>" << alarmsound << "</alarmsound>" << std::endl << std::endl;

	xml << "<wakeupsound>" << wakeUpSound << "</wakeupsound>" << std::endl << std::endl;

	xml << "<areas>" << std::endl;
	for (int index = 0; index < areas.size(); index++)
	{
		xml << areas[index] << ";" << std::endl;
	}
	xml << "</areas>" << std::endl
		<< std::endl;

	xml << "<sensors>" << std::endl;
	for (int index = 0; index < sensors.size(); index++)
	{
		xml << sensors[index] << ";" << std::endl;
	}
	xml << "</sensors>" << std::endl
		<< std::endl;

	xml << "<urls>" << std::endl;
	for (int index = 0; index < urls.size(); index++)
	{
		xml << urls[index] << ";" << std::endl;
	}
	xml << "</urls>" << std::endl
		<< std::endl;

	xml << "<accessurl>" << accessurl << "</accessurl>" << std::endl
		<< std::endl;

	xml << "<mediamirror>" << std::endl;
	for (int index = 0; index < mediamirror.size(); index++)
	{
		xml << mediamirror[index] << ";" << std::endl;
	}
	xml << "</mediamirror>" << std::endl
		<< std::endl;

	xml << "<sockets>" << std::endl;
	for (int index = 0; index < sockets.size(); index++)
	{
		xml << sockets[index].GetName() << ":"
			<< sockets[index].GetArea() << ":"
			<< sockets[index].GetCode() << ":"
			<< Tools::ConvertIntToStr(sockets[index].GetState()) << ";"
			<< std::endl;
	}
	xml << "</sockets>" << std::endl
		<< std::endl;

	xml << "<gpios>" << std::endl;
	for (int index = 0; index < gpios.size(); index++)
	{
		xml << gpios[index].GetName() << ":"
			<< Tools::ConvertIntToStr(gpios[index].GetGpio()) << ":"
			<< Tools::ConvertIntToStr(gpios[index].GetState()) << ";"
			<< std::endl;
	}
	xml << "</gpios>" << std::endl
		<< std::endl;

	xml << "<schedules>" << std::endl;
	for (int index = 0; index < schedules.size(); index++)
	{
		xml << schedules[index].GetName() << ":"
			<< schedules[index].GetSocket() << ":"
			<< schedules[index].GetGpio() << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetWeekday()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetHour()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetMinute()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetOnoff()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetIsTimer()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetPlaySound()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetPlayRaspberry()) << ":"
			<< Tools::ConvertIntToStr(schedules[index].GetStatus()) << ";"
			<< std::endl;
	}
	xml << "</schedules>" << std::endl
		<< std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateShoppingListXml(std::vector<ShoppingEntryDto> entries)
{
	std::stringstream xml;

	xml << "<entries>" << std::endl;
	for (int index = 0; index < entries.size(); index++)
	{
		xml << Tools::ConvertIntToStr(entries[index].GetId()) << ":"
			<< entries[index].GetName() << ":"
			<< entries[index].GetGroup() << ":"
			<< Tools::ConvertIntToStr(entries[index].GetQuantity()) << ";"
			<< std::endl;
	}
	xml << "</entries>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateTemperatureSettingsXml(int tempMin, int tempMax, int ledTempNormal, int ledTempLow, int ledTempHigh, bool tempControlActive)
{
	std::stringstream xml;

	xml << "<tempmin>" << Tools::ConvertIntToStr(tempMin) << "</tempmin>" << std::endl << std::endl;

	xml << "<tempmax>" << Tools::ConvertIntToStr(tempMax) << "</tempmax>" << std::endl << std::endl;

	xml << "<ledtempnormal>" << Tools::ConvertIntToStr(ledTempNormal) << "</ledtempnormal>" << std::endl << std::endl;

	xml << "<ledtemplow>" << Tools::ConvertIntToStr(ledTempLow) << "</ledtemplow>" << std::endl << std::endl;

	xml << "<ledtemphigh>" << Tools::ConvertIntToStr(ledTempHigh) << "</ledtemphigh>" << std::endl << std::endl;

	int controlActive = -1;
	if (tempControlActive)
	{
		controlActive = 1;
	}
	else
	{
		controlActive = 0;
	}

	xml << "<controlactive>" << Tools::ConvertIntToStr(controlActive) << "</controlactive>" << std::endl << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateUsersXml(std::vector<UserDto> users)
{
	std::stringstream xml;

	xml << "<users>" << std::endl;
	for (int index = 0; index < users.size(); index++)
	{
		xml << users[index].GetName() << ":"
			<< users[index].GetPassword() << ":"
			<< Tools::ConvertIntToStr(users[index].GetRole()) << ":"
			<< Tools::ConvertIntToStr(users[index].IsAdmin()) << ":"
			<< Tools::ConvertIntToStr(users[index].GetInvalidLoginCount()) << ";"
			<< std::endl;
	}
	xml << "</users>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateLoggerXml(std::vector<LogDto> logs)
{
	std::stringstream xml;

	xml << "<logs>" << std::endl;
	for (int index = 0; index < logs.size(); index++)
	{
		xml << logs[index].GetLevel() << ":"
			<< logs[index].GetContent() << ":"
			<< logs[index].GetLogTime() << ":"
			<< logs[index].GetUser() << ";"
			<< std::endl;
	}
	xml << "</logs>" << std::endl;

	return xml.str();
}
