#include "MeterDataDto.h"

MeterDataDto::MeterDataDto()
{
	_id = 0;
	_type = "";
	_typeId = 0;
	_day = 1;
	_month = 1;
	_year = 1970;
	_hour = 0;
	_minute = 0;
	_meterId = "";
	_area = "";
	_value = 0;
	_imageName = "";
}

MeterDataDto::MeterDataDto(
	int id,
	std::string type,
	int typeId,
	int day, int month, int year,
	int hour, int minute,
	std::string meterId,
	std::string area,
	double value,
	std::string imageName)
{
	_id = id;
	_type = type;
	_typeId = typeId;
	_day = day;
	_month = month;
	_year = year;
	_hour = hour;
	_minute = minute;
	_meterId = meterId;
	_area = area;
	_value = value;
	_imageName = imageName;
}

MeterDataDto::~MeterDataDto()
{
}

void MeterDataDto::SetId(int id)
{
	_id = id;
}

int MeterDataDto::GetId()
{
	return _id;
}

void MeterDataDto::SetType(std::string type)
{
	_type = type;
}

std::string MeterDataDto::GetType()
{
	return _type;
}

void MeterDataDto::SetTypeId(int typeId)
{
	_typeId = _typeId;
}

int MeterDataDto::GetTypeId()
{
	return _typeId;
}

void MeterDataDto::SetDay(int day)
{
	_day = day;
}

int MeterDataDto::GetDay()
{
	return _day;
}

void MeterDataDto::SetMonth(int month)
{
	_month = month;
}

int MeterDataDto::GetMonth()
{
	return _month;
}

void MeterDataDto::SetYear(int year)
{
	_year = year;
}

int MeterDataDto::GetYear()
{
	return _year;
}

void MeterDataDto::SetHour(int hour)
{
	_hour = hour;
}

int MeterDataDto::GetHour()
{
	return _hour;
}

void MeterDataDto::SetMinute(int minute)
{
	_minute = minute;
}

int MeterDataDto::GetMinute()
{
	return _minute;
}

void MeterDataDto::SetMeterId(std::string meterId)
{
	_meterId = meterId;
}

std::string MeterDataDto::GetMeterId()
{
	return _meterId;
}

void MeterDataDto::SetArea(std::string area)
{
	_area = area;
}

std::string MeterDataDto::GetArea()
{
	return _area;
}

void MeterDataDto::SetValue(double value)
{
	_value = value;
}

double MeterDataDto::GetValue()
{
	return _value;
}

void MeterDataDto::SetImageName(std::string imageName)
{
	_imageName = imageName;
}

std::string MeterDataDto::GetImageName()
{
	return _imageName;
}

std::string MeterDataDto::SaveString()
{
	std::string str =
		Tools::ConvertIntToStr(_id) + ":"
		+ _type + ":"
		+ Tools::ConvertIntToStr(_typeId) + ":"
		+ Tools::ConvertIntToStr(_day) + ":"
		+ Tools::ConvertIntToStr(_month) + ":"
		+ Tools::ConvertIntToStr(_year) + ":"
		+ Tools::ConvertIntToStr(_hour) + ":"
		+ Tools::ConvertIntToStr(_minute) + ":"
		+ _meterId + ":"
		+ _area + ":"
		+ Tools::ConvertDoubleToStr(_value) + ":"
		+ _imageName + ";";

	return str;
}

std::string MeterDataDto::JsonString()
{
	std::string str =
		std::string("{")
		+ std::string("\"MeterData\":")
		+ std::string("{")
		+ std::string("\"Id\":") + Tools::ConvertIntToStr(_id) + std::string(",")
		+ std::string("\"Type\":\"") + _type + std::string("\",")
		+ std::string("\"TypeId\":") + Tools::ConvertIntToStr(_typeId) + std::string(",")
		+ std::string("\"Date\":")
		+ std::string("{")
		+ std::string("\"Day\":") + Tools::ConvertIntToStr(_day) + std::string(",")
		+ std::string("\"Month\":") + Tools::ConvertIntToStr(_month) + std::string(",")
		+ std::string("\"Year\":") + Tools::ConvertIntToStr(_year)
		+ std::string("}")
		+ std::string(",")
		+ std::string("\"Time\":")
		+ std::string("{")
		+ std::string("\"Hour\":") + Tools::ConvertIntToStr(_hour) + std::string(",")
		+ std::string("\"Minute\":") + Tools::ConvertIntToStr(_minute)
		+ std::string("}")
		+ std::string(",")
		+ std::string("\"MeterId\":\"") + _meterId + std::string("\",")
		+ std::string("\"Area\":\"") + _area + std::string("\",")
		+ std::string("\"Value\":") + Tools::ConvertDoubleToStr(_value) + std::string(",")
		+ std::string("\"ImageName\":\"") + _imageName + std::string("\"")
		+ std::string("}")
		+ std::string("}");
	return str;
}

std::string MeterDataDto::PhpString()
{
	std::stringstream out;

	out << "meterdata::"
		<< Tools::ConvertIntToStr(_id) << "::"
		<< _type << "::"
		<< Tools::ConvertIntToStr(_typeId) << "::"
		<< Tools::ConvertIntToStr(_day) << "::"
		<< Tools::ConvertIntToStr(_month) << "::"
		<< Tools::ConvertIntToStr(_year) << "::"
		<< Tools::ConvertIntToStr(_hour) << "::"
		<< Tools::ConvertIntToStr(_minute) << "::"
		<< _meterId << "::"
		<< _area << "::"
		<< Tools::ConvertDoubleToStr(_value) << "::"
		<< _imageName << ";";

	return out.str();
}

std::string MeterDataDto::ToString()
{
	std::string str =
		std::string("MeterDataDto { id: ") + Tools::ConvertIntToStr(_id)
		+ std::string("; type: ") + _type
		+ std::string("; typeId: ") + Tools::ConvertIntToStr(_typeId)
		+ std::string("; day: ") + Tools::ConvertIntToStr(_day)
		+ std::string("; month: ") + Tools::ConvertIntToStr(_month)
		+ std::string("; year: ") + Tools::ConvertIntToStr(_year)
		+ std::string("; hour: ") + Tools::ConvertIntToStr(_hour)
		+ std::string("; hour: ") + Tools::ConvertIntToStr(_minute)
		+ std::string("; meterId: ") + _meterId
		+ std::string("; area: ") + _area
		+ std::string("; value: ") + Tools::ConvertDoubleToStr(_value)
		+ std::string("; imageName: ") + _imageName
		+ std::string(" }");
	return str;
}
