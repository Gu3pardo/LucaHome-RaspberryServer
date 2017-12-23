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
		xml << birthdayList[index].SaveString() << std::endl;
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
		xml << changelist[index].SaveString() << std::endl;
	}
	xml << "</changes>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateCoinsXml(std::vector<CoinDto> coinList)
{
	std::stringstream xml;

	xml << "<coins>" << std::endl;
	for (int index = 0; index < coinList.size(); index++)
	{
		xml << coinList[index].SaveString() << std::endl;
	}
	xml << "</coins>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateListedMenuXml(std::vector<ListedMenuDto> listedmenus)
{
	std::stringstream xml;

	xml << "<listedmenu>" << std::endl;
	for (int index = 0; index < listedmenus.size(); index++)
	{
		xml << listedmenus[index].SaveString() << std::endl;
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
		xml << mapcontents[index].SaveString() << std::endl;
	}
	xml << "</mapcontent>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateMenuXml(std::vector<MenuDto> menu)
{
	std::stringstream xml;

	for (int index = 0; index < menu.size(); index++)
	{
		xml << menu[index].SaveString() << std::endl;
	}

	return xml.str();
}

std::string XmlWriter::GenerateMeterDataXml(std::vector<MeterDataDto> meterData)
{
	std::stringstream xml;

	xml << "<meterdata>" << std::endl;
	for (int index = 0; index < meterData.size(); index++)
	{
		xml << meterData[index].SaveString() << std::endl;
	}
	xml << "</meterdata>" << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateSettingsXml(
	int port, int datagpio, int raspberry,
	std::vector<std::string> areas, std::vector<std::string> sensors,
	std::vector<std::string> urls, std::vector<std::string> mediamirror,
	std::vector<WirelessSocketDto> sockets, std::vector<GpioDto> gpios, std::vector<ScheduleDto> schedules,
	std::vector<WirelessSwitchDto> switches)
{
	std::stringstream xml;

	xml << "<port>" << Tools::ConvertIntToStr(port) << "</port>" << std::endl << std::endl;

	xml << "<datagpio>" << Tools::ConvertIntToStr(datagpio) << "</datagpio>" << std::endl << std::endl;

	xml << "<raspberry>" << Tools::ConvertIntToStr(raspberry) << "</raspberry>" << std::endl << std::endl;

	xml << "<areas>" << std::endl;
	for (int index = 0; index < areas.size(); index++)
	{
		xml << areas[index] << ";" << std::endl;
	}
	xml << "</areas>" << std::endl << std::endl;

	xml << "<sensors>" << std::endl;
	for (int index = 0; index < sensors.size(); index++)
	{
		xml << sensors[index] << ";" << std::endl;
	}
	xml << "</sensors>" << std::endl << std::endl;

	xml << "<urls>" << std::endl;
	for (int index = 0; index < urls.size(); index++)
	{
		xml << urls[index] << ";" << std::endl;
	}
	xml << "</urls>" << std::endl << std::endl;

	xml << "<mediamirror>" << std::endl;
	for (int index = 0; index < mediamirror.size(); index++)
	{
		xml << mediamirror[index] << ";" << std::endl;
	}
	xml << "</mediamirror>" << std::endl << std::endl;

	xml << "<sockets>" << std::endl;
	for (int index = 0; index < sockets.size(); index++)
	{
		xml << sockets[index].SaveString() << std::endl;
	}
	xml << "</sockets>" << std::endl << std::endl;

	xml << "<gpios>" << std::endl;
	for (int index = 0; index < gpios.size(); index++)
	{
		xml << gpios[index].SaveString() << std::endl;
	}
	xml << "</gpios>" << std::endl << std::endl;

	xml << "<schedules>" << std::endl;
	for (int index = 0; index < schedules.size(); index++)
	{
		xml << schedules[index].SaveString() << std::endl;
	}
	xml << "</schedules>" << std::endl << std::endl;

	xml << "<switches>" << std::endl;
	for (int index = 0; index < switches.size(); index++)
	{
		xml << switches[index].SaveString() << std::endl;
	}
	xml << "</switches>" << std::endl << std::endl;

	return xml.str();
}

std::string XmlWriter::GenerateShoppingListXml(std::vector<ShoppingEntryDto> entries)
{
	std::stringstream xml;

	xml << "<entries>" << std::endl;
	for (int index = 0; index < entries.size(); index++)
	{
		xml << entries[index].SaveString() << std::endl;
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
