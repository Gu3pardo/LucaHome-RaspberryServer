#include "MeterLogItem.h"

MeterLogItem::MeterLogItem()
{
	_uuid = "";
	_roomUuid = "";
	_typeUuid = "";
	_type = "";
	_day = 1;
	_month = 1;
	_year = 1970;
	_hour = 0;
	_minute = 0;
	_meterId = "";
	_value = 0;
	_imageName = "";
}

MeterLogItem::MeterLogItem(
	string uuid,
	string roomUuid,
	string typeUuid,
	string type,
	int day, int month, int year,
	int hour, int minute,
	string meterId,
	double value,
	string imageName)
{
	_uuid = uuid;
	_roomUuid = roomUuid;
	_typeUuid = typeUuid;
	_type = type;
	_day = day;
	_month = month;
	_year = year;
	_hour = hour;
	_minute = minute;
	_meterId = meterId;
	_value = value;
	_imageName = imageName;
}

MeterLogItem::~MeterLogItem()
{
}

void MeterLogItem::SetUuid(string uuid)
{
	_uuid = uuid;
}

string MeterLogItem::GetUuid()
{
	return _uuid;
}

void MeterLogItem::SetRoomUuid(string roomUuid)
{
	_roomUuid = roomUuid;
}

string MeterLogItem::GetRoomUuid()
{
	return _roomUuid;
}

void MeterLogItem::SetTypeUuid(string typeUuid)
{
	_typeUuid = typeUuid;
}

string MeterLogItem::GetTypeUuid()
{
	return _typeUuid;
}

void MeterLogItem::SetType(string type)
{
	_type = type;
}

string MeterLogItem::GetType()
{
	return _type;
}

void MeterLogItem::SetDay(int day)
{
	_day = day;
}

int MeterLogItem::GetDay()
{
	return _day;
}

void MeterLogItem::SetMonth(int month)
{
	_month = month;
}

int MeterLogItem::GetMonth()
{
	return _month;
}

void MeterLogItem::SetYear(int year)
{
	_year = year;
}

int MeterLogItem::GetYear()
{
	return _year;
}

void MeterLogItem::SetHour(int hour)
{
	_hour = hour;
}

int MeterLogItem::GetHour()
{
	return _hour;
}

void MeterLogItem::SetMinute(int minute)
{
	_minute = minute;
}

int MeterLogItem::GetMinute()
{
	return _minute;
}

void MeterLogItem::SetMeterId(string meterId)
{
	_meterId = meterId;
}

string MeterLogItem::GetMeterId()
{
	return _meterId;
}

void MeterLogItem::SetValue(double value)
{
	_value = value;
}

double MeterLogItem::GetValue()
{
	return _value;
}

void MeterLogItem::SetImageName(string imageName)
{
	_imageName = imageName;
}

string MeterLogItem::GetImageName()
{
	return _imageName;
}

string MeterLogItem::JsonString()
{
	string str =
		string("{")
		+ string("\"MeterLogItem\":")
		+ string("{")
		+ string("\"Uuid\":\"") + _uuid + string("\",")
		+ string("\"RoomUuid\":\"") + _roomUuid + string("\",")
		+ string("\"TypeUuid\":\"") + _typeUuid + string("\",")
		+ string("\"Type\":\"") + _type + string("\",")
		+ string("\"Date\":")
		+ string("{")
		+ string("\"Day\":") + Tools::ConvertIntToStr(_day) + string(",")
		+ string("\"Month\":") + Tools::ConvertIntToStr(_month) + string(",")
		+ string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ string("}")
		+ string(",")
		+ string("\"Time\":")
		+ string("{")
		+ string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + string(",")
		+ string("\"Minute\":") + Tools::ConvertIntToStr(_minute)
		+ string("}")
		+ string(",")
		+ string("\"MeterId\":\"") + _meterId + string("\",")
		+ string("\"Value\":") + Tools::ConvertDoubleToStr(_value) + string(",")
		+ string("\"ImageName\":\"") + _imageName + string("\"")
		+ string("}")
		+ string("}");
	return str;
}

string MeterLogItem::ToString()
{
	string str =
		string("MeterLogItem { uuid: ") + _uuid
		+ string("; roomUuid: ") + _roomUuid
		+ string("; typeUuid: ") + _typeUuid
		+ string("; type: ") + _type
		+ string("; day: ") + Tools::ConvertIntToStr(_day)
		+ string("; month: ") + Tools::ConvertIntToStr(_month)
		+ string("; year: ") + Tools::ConvertIntToStr(_year)
		+ string("; hour: ") + Tools::ConvertIntToStr(_hour)
		+ string("; hour: ") + Tools::ConvertIntToStr(_minute)
		+ string("; meterId: ") + _meterId
		+ string("; value: ") + Tools::ConvertDoubleToStr(_value)
		+ string("; imageName: ") + _imageName
		+ string(" }");
	return str;
}
