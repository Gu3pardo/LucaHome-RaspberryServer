#include "XmlParser.h"

XmlParser::XmlParser(std::string content)
{
	_content = content;
}

XmlParser::~XmlParser()
{
}

std::string XmlParser::FindTag(std::string tag)
{
	std::string tagContent;
	std::string openTag;
	std::string closeTag;
	openTag += std::string("<") + tag + std::string(">");
	closeTag += std::string("</") + tag + std::string(">");
	if (_content.length() > 0)
	{
		int openTag_pos = _content.find(openTag, 0);
		int closeTag_pos = _content.find(closeTag, openTag_pos);
		if (openTag_pos < closeTag_pos)
		{
			tagContent = _content.substr(openTag_pos + openTag.length(),
				closeTag_pos - (openTag_pos + openTag.length()));
		}
	}
	return tagContent;
}

std::vector<std::string> XmlParser::ParseAreaList()
{
	std::string entries = FindTag("areas");
	std::vector<std::string> areaList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				areaList.push_back(lines[l]);
			}
		}
	}

	return areaList;
}

std::vector<std::string> XmlParser::ParseSensorList()
{
	std::string entries = FindTag("sensors");
	std::vector<std::string> sensorList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				sensorList.push_back(lines[l]);
			}
		}
	}

	return sensorList;
}

std::vector<std::string> XmlParser::ParseUrlList()
{
	std::string entries = FindTag("urls");
	std::vector<std::string> urlList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				urlList.push_back(lines[l]);
			}
		}
	}

	return urlList;
}

std::string XmlParser::ParseAccessUrl()
{
	std::string entries = FindTag("accessurl");
	std::vector<std::string> accessurls;
	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				accessurls.push_back(lines[l]);
			}
		}
	}
	if (accessurls.size() != 1)
	{
		return "";
	}
	else
	{
		return accessurls[0];
	}
}

std::vector<std::string> XmlParser::ParseMediaMirrorList()
{
	std::string entries = FindTag("mediamirror");
	std::vector<std::string> mediaMirrorList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				mediaMirrorList.push_back(lines[l]);
			}
		}
	}

	return mediaMirrorList;
}

std::vector<BirthdayDto> XmlParser::ParseBirthdayList()
{
	std::string entries = FindTag("birthdays");
	std::vector<BirthdayDto> birthdayList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);

				BirthdayDto newBirthday;
				newBirthday.SetId(l);

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newBirthday.SetName(words[0]);
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newBirthday.SetDay(atoi(words[1].c_str()));
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newBirthday.SetMonth(atoi(words[2].c_str()));
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newBirthday.SetYear(atoi(words[3].c_str()));
					}
					if (typeid(words.at(4)) == typeid(std::string))
					{
						bool remindMe = Tools::ConvertStrToBool(words[4].c_str());
						newBirthday.SetRemindMe(remindMe);
					}
					if (typeid(words.at(5)) == typeid(std::string))
					{
						bool sendMail = Tools::ConvertStrToBool(words[5].c_str());
						newBirthday.SetSendMail(sendMail);
					}
				}

				birthdayList.push_back(newBirthday);
			}
		}
	}

	return birthdayList;
}

std::vector<ChangeDto> XmlParser::ParseChangeList()
{
	std::string entries = FindTag("changes");
	std::vector<ChangeDto> changeList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				ChangeDto newChange;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newChange.SetType(words[0]);
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newChange.SetHour(atoi(words[1].c_str()));
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newChange.SetMinute(atoi(words[2].c_str()));
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newChange.SetDay(atoi(words[3].c_str()));
					}
					if (typeid(words.at(4)) == typeid(std::string))
					{
						newChange.SetMonth(atoi(words[4].c_str()));
					}
					if (typeid(words.at(5)) == typeid(std::string))
					{
						newChange.SetYear(atoi(words[5].c_str()));
					}
					if (typeid(words.at(6)) == typeid(std::string))
					{
						newChange.SetUserName(words[6]);
					}
				}

				changeList.push_back(newChange);
			}
		}
	}

	return changeList;
}

std::vector<CoinDto> XmlParser::ParseCoinList()
{
	std::string entries = FindTag("coins");
	std::vector<CoinDto> coinList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				CoinDto newCoin;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newCoin.SetId(atoi(words[0].c_str()));
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newCoin.SetUser(words[1]);
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newCoin.SetType(words[2]);
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						double amount = Tools::ConvertStrToDouble(words[3].c_str());
						newCoin.SetAmount(amount);
					}
				}

				coinList.push_back(newCoin);
			}
		}
	}

	return coinList;
}

std::vector<GpioDto> XmlParser::ParseGpioList()
{
	std::string entries = FindTag("gpios");
	std::vector<GpioDto> gpioList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				GpioDto newGpio;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newGpio.SetName(words[0]);
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newGpio.SetGpio(atoi(words[1].c_str()));
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newGpio.SetState(atoi(words[2].c_str()));
					}
				}

				gpioList.push_back(newGpio);
			}
		}
	}

	return gpioList;
}

std::vector<ListedMenuDto> XmlParser::ParseListedMenuList()
{
	std::string entries = FindTag("listedmenu");
	std::vector<ListedMenuDto> listedMenuList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				ListedMenuDto newListedMenu;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newListedMenu.SetId(atoi(words[0].c_str()));
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newListedMenu.SetTitle(words[1]);
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newListedMenu.SetDescription(words[2]);
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newListedMenu.SetUseCount(atoi(words[3].c_str()));
					}
					if (typeid(words.at(4)) == typeid(std::string))
					{
						newListedMenu.SetRating(atoi(words[4].c_str()));
					}
				}

				listedMenuList.push_back(newListedMenu);
			}
		}
	}

	return listedMenuList;
}

std::vector<MapContentDto> XmlParser::ParseMapContentList()
{
	std::string entries = FindTag("mapcontent");
	std::vector<MapContentDto> mapContentList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);

				int id = -1;
				std::string type = "";
				int typeId = -1;
				int x = -1;
				int y = -1;
				std::string name = "";
				std::string shortName = "";
				std::string area = "";
				bool visibility = true;

				if (typeid(words.at(0)) == typeid(std::string))
				{
					id = atoi(words[0].c_str());
				}
				if (typeid(words.at(1)) == typeid(std::string))
				{
					type = words[1].c_str();
				}
				if (typeid(words.at(2)) == typeid(std::string))
				{
					typeId = atoi(words[2].c_str());
				}
				if (typeid(words.at(3)) == typeid(std::string))
				{
					std::vector<std::string> coordinates = Tools::Explode("|", words[3]);
					if (typeid(coordinates.at(0)) == typeid(std::string) && typeid(coordinates.at(1)) == typeid(std::string))
					{
						x = atoi(coordinates[0].c_str());
						y = atoi(coordinates[1].c_str());
					}
				}
				if (typeid(words.at(4)) == typeid(std::string))
				{
					name = words[4].c_str();
				}
				if (typeid(words.at(5)) == typeid(std::string))
				{
					shortName = words[5].c_str();
				}
				if (typeid(words.at(6)) == typeid(std::string))
				{
					area = words[6].c_str();
				}
				if (typeid(words.at(7)) == typeid(std::string))
				{
					visibility = Tools::ConvertStrToBool(words[7].c_str());
				}

				PointDto position = PointDto(x, y);
				MapContentDto newEntry = MapContentDto(id, type, typeId, position, name, shortName, area, visibility);

				mapContentList.push_back(newEntry);
			}
		}
	}

	return mapContentList;
}

std::vector<MenuDto> XmlParser::ParseMenuList()
{
	std::vector<MenuDto> menuList;

	std::string monday = FindTag("monday");
	MenuDto mondayMenu = ParseMenuDay("monday", monday);
	menuList.push_back(mondayMenu);

	std::string tuesday = FindTag("tuesday");
	MenuDto tuesdayMenu = ParseMenuDay("tuesday", tuesday);
	menuList.push_back(tuesdayMenu);

	std::string wednesday = FindTag("wednesday");
	MenuDto wednesdayMenu = ParseMenuDay("wednesday", wednesday);
	menuList.push_back(wednesdayMenu);

	std::string thursday = FindTag("thursday");
	MenuDto thursdayMenu = ParseMenuDay("thursday", thursday);
	menuList.push_back(thursdayMenu);

	std::string friday = FindTag("friday");
	MenuDto fridayMenu = ParseMenuDay("friday", friday);
	menuList.push_back(fridayMenu);

	std::string saturday = FindTag("saturday");
	MenuDto saturdayMenu = ParseMenuDay("saturday", saturday);
	menuList.push_back(saturdayMenu);

	std::string sunday = FindTag("sunday");
	MenuDto sundayMenu = ParseMenuDay("sunday", sunday);
	menuList.push_back(sundayMenu);

	return menuList;
}

MenuDto XmlParser::ParseMenuDay(std::string weekday, std::string tagData)
{
	std::vector<std::string> data = Tools::Explode(":", tagData);
	MenuDto menu;

	menu.SetWeekday(weekday);
	menu.SetDay(atoi(data[0].c_str()));
	menu.SetMonth(atoi(data[1].c_str()));
	menu.SetYear(atoi(data[2].c_str()));
	menu.SetTitle(data[3].c_str());
	menu.SetDescription(data[4].c_str());

	return menu;
}

std::vector<ScheduleDto> XmlParser::ParseScheduleList()
{
	std::string entries = FindTag("schedules");
	std::vector<ScheduleDto> scheduleList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				ScheduleDto newSchedule;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newSchedule.SetName(words[0]);
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newSchedule.SetSocket(words[1]);
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newSchedule.SetGpio(words[2]);
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newSchedule.SetSwitch(words[3]);
					}
					if (typeid(words.at(4)) == typeid(std::string))
					{
						newSchedule.SetWeekday(atoi(words[4].c_str()));
					}
					if (typeid(words.at(5)) == typeid(std::string))
					{
						newSchedule.SetHour(atoi(words[5].c_str()));
					}
					if (typeid(words.at(6)) == typeid(std::string))
					{
						newSchedule.SetMinute(atoi(words[6].c_str()));
					}
					if (typeid(words.at(7)) == typeid(std::string))
					{
						newSchedule.SetOnoff(atoi(words[7].c_str()));
					}
					if (typeid(words.at(8)) == typeid(std::string))
					{
						bool isTimer = Tools::ConvertStrToBool(words[8].c_str());
						newSchedule.SetIsTimer(isTimer);
					}
					if (typeid(words.at(9)) == typeid(std::string))
					{
						newSchedule.SetState(atoi(words[9].c_str()));
					}
				}

				scheduleList.push_back(newSchedule);
			}
		}
	}

	return scheduleList;
}

std::vector<WirelessSocketDto> XmlParser::ParseSocketList()
{
	std::string entries = FindTag("sockets");
	std::vector<WirelessSocketDto> socketList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				WirelessSocketDto newSocket;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newSocket.SetName(words[0]);
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newSocket.SetArea(words[1]);
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newSocket.SetCode(words[2]);
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newSocket.SetState(atoi(words[3].c_str()), 0, atoi(words[4].c_str()), atoi(words[5].c_str()), atoi(words[6].c_str()), atoi(words[7].c_str()), atoi(words[8].c_str()), words[9].c_str());
					}
				}

				socketList.push_back(newSocket);
			}
		}
	}

	return socketList;
}

std::vector<WirelessSwitchDto> XmlParser::ParseSwitchList()
{
	std::string entries = FindTag("switches");
	std::vector<WirelessSwitchDto> switchList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				WirelessSwitchDto newSwitch(
					words[0],
					words[1],
					atoi(words[3].c_str()),
					words[4],
					0,
					atoi(words[5].c_str()), atoi(words[6].c_str()),
					atoi(words[7].c_str()), atoi(words[8].c_str()), atoi(words[9].c_str()),
					words[10]
				);

				switchList.push_back(newSwitch);
			}
		}
	}

	return switchList;
}

std::vector<ShoppingEntryDto> XmlParser::ParseShoppingList()
{
	std::string entries = FindTag("entries");
	std::vector<ShoppingEntryDto> shoppingList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				ShoppingEntryDto newEntry;

				for (int w = 0; w < words.size(); w++)
				{
					if (typeid(words.at(0)) == typeid(std::string))
					{
						newEntry.SetId(atoi(words[0].c_str()));
					}
					if (typeid(words.at(1)) == typeid(std::string))
					{
						newEntry.SetName(words[1]);
					}
					if (typeid(words.at(2)) == typeid(std::string))
					{
						newEntry.SetGroup(words[2]);
					}
					if (typeid(words.at(3)) == typeid(std::string))
					{
						newEntry.SetQuantity(atoi(words[3].c_str()));
					}
				}

				shoppingList.push_back(newEntry);
			}
		}
	}

	return shoppingList;
}

std::vector<UserDto> XmlParser::ParseUserList()
{
	std::string entries = FindTag("users");
	std::vector<UserDto> userList;

	if (entries.length() > 0)
	{
		std::vector<std::string> lines = Tools::Explode(";", entries);
		for (int l = 0; l < lines.size(); l++)
		{
			if (lines[l].length() > 0)
			{
				std::vector<std::string> words = Tools::Explode(":", lines[l]);
				if (words.size() == 5)
				{
					UserDto user(
						words[0].c_str(),
						words[1].c_str(),
						atoi(words[2].c_str()),
						atoi(words[3].c_str()),
						atoi(words[4].c_str()));

					userList.push_back(user);
				}
			}
		}
	}

	return userList;
}
