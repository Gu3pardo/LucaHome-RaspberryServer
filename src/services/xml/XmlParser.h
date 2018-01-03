#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>

#include "../../common/utils/Tools.h"

#include "../../common/dto/BirthdayDto.h"
#include "../../common/dto/ChangeDto.h"
#include "../../common/dto/CoinDto.h"
#include "../../common/dto/GpioDto.h"
#include "../../common/dto/InformationDto.h"
#include "../../common/dto/ListedMenuDto.h"
#include "../../common/dto/MapContentDto.h"
#include "../../common/dto/MenuDto.h"
#include "../../common/dto/MeterDataDto.h"
#include "../../common/dto/MoneyMeterDataDto.h"
#include "../../common/dto/PointDto.h"
#include "../../common/dto/PuckJsDto.h"
#include "../../common/dto/ScheduleDto.h"
#include "../../common/dto/ShoppingEntryDto.h"
#include "../../common/dto/UserDto.h"
#include "../../common/dto/WirelessSocketDto.h"
#include "../../common/dto/WirelessSwitchDto.h"

#ifndef XMLPARSER_H
#define XMLPARSER_H

class XmlParser
{
private:
	std::string _content;

public:
	XmlParser(std::string);
	~XmlParser();

	std::string FindTag(std::string);

	std::vector<std::string> ParseAreaList();
	std::vector<std::string> ParseSensorList();
	std::vector<std::string> ParseUrlList();
	std::string ParseAccessUrl();
	std::vector<std::string> ParseMediaMirrorList();

	std::vector<BirthdayDto> ParseBirthdayList();
	std::vector<ChangeDto> ParseChangeList();
	std::vector<CoinDto> ParseCoinList();
	std::vector<GpioDto> ParseGpioList();
	std::vector<ListedMenuDto> ParseListedMenuList();
	std::vector<MapContentDto> ParseMapContentList();
	std::vector<MenuDto> ParseMenuList();
	std::vector<MeterDataDto> ParseMeterDataList();
	std::vector<MoneyMeterDataDto> ParseMoneyMeterDataList();
	MenuDto ParseMenuDay(std::string, std::string);
	std::vector<PuckJsDto> ParsePuckJsList();
	std::vector<ScheduleDto> ParseScheduleList();
	std::vector<WirelessSocketDto> ParseSocketList();
	std::vector<WirelessSwitchDto> ParseSwitchList();
	std::vector<ShoppingEntryDto> ParseShoppingList();
	std::vector<UserDto> ParseUserList();
};

#endif
