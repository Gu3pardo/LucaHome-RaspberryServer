#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>

#include "XmlParser.h"
#include "XmlWriter.h"

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

#ifndef XMLSERVICE_H
#define XMLSERVICE_H

class XmlService
{
public:
	XmlService();
	~XmlService();

	static std::string GenerateBirthdaysXml(std::vector<BirthdayDto>);
	std::vector<BirthdayDto> GetBirthdayList(std::string);

	static std::string GenerateChangesXml(std::vector<ChangeDto>);
	std::vector<ChangeDto> GetChangeList(std::string);

	static std::string GenerateCoinsXml(std::vector<CoinDto>);
	std::vector<CoinDto> GetCoinList(std::string);

	InformationDto GetInformation(std::string);

	static std::string GenerateMapContentsXml(std::vector<MapContentDto>);
	std::vector<MapContentDto> GetMapContentList(std::string);

	static std::string GenerateListedMenuXml(std::vector<ListedMenuDto>);
	std::vector<ListedMenuDto> GetListedMenuList(std::string);
	static std::string GenerateMenuXml(std::vector<MenuDto>);
	std::vector<MenuDto> GetMenuList(std::string);

	static std::string GenerateMeterDataXml(std::vector<MeterDataDto>);
	std::vector<MeterDataDto> GetMeterDataList(std::string);

	static std::string GenerateMoneyMeterDataXml(std::vector<MoneyMeterDataDto>);
	std::vector<MoneyMeterDataDto> GetMoneyMeterDataList(std::string);

	static std::string GenerateSettingsXml(
		int, int, int,
		std::vector<std::string>, std::vector<std::string>, std::vector<std::string>, std::vector<std::string>,
		std::vector<GpioDto>, std::vector<PuckJsDto>, std::vector<ScheduleDto>, std::vector<WirelessSocketDto>, std::vector<WirelessSwitchDto>);
	int GetPort(std::string);
	int GetDatagpio(std::string);
	int GetReceivergpio(std::string);
	int GetRaspberry(std::string);
	std::string GetAlarmSound(std::string);
	std::string GetWakeUpSound(std::string);
	std::vector<std::string> GetAreaList(std::string);
	std::vector<std::string> GetSensorList(std::string);
	std::vector<std::string> GetUrlList(std::string);
	std::string GetAccessUrl(std::string);
	std::vector<std::string> GetMediaMirrorList(std::string);
	std::vector<GpioDto> GetGpioList(std::string);
	std::vector<PuckJsDto> GetPuckJsList(std::string);
	std::vector<ScheduleDto> GetScheduleList(std::string);
	std::vector<WirelessSocketDto> GetSocketList(std::string);
	std::vector<WirelessSwitchDto> GetSwitchList(std::string);

	static std::string GenerateShoppingListXml(std::vector<ShoppingEntryDto>);
	std::vector<ShoppingEntryDto> GetShoppingList(std::string);

	static std::string GenerateTemperatureSettingsXml(int, int, int, int, int, bool);
	int GetTempMin(std::string);
	int GetTempMax(std::string);
	int GetLEDTempNormal(std::string);
	int GetLEDTempLow(std::string);
	int GetLEDTempHigh(std::string);
	bool IsTempControlActive(std::string);

	static std::string GenerateUsersXml(std::vector<UserDto>);
	std::vector<UserDto> GetUserList(std::string);
};

#endif
