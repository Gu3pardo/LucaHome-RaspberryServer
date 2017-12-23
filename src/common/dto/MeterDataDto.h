#include <string>
#include <ctime>
#include <cstring>
#include <iostream>

#include "../utils/Tools.h"

#ifndef METER_DATA_DTO_H
#define METER_DATA_DTO_H

class MeterDataDto
{
private:
	int _id;
	std::string _type;
	int _typeId;
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;
	std::string _meterId;
	std::string _area;
	double _value;
	std::string _imageName;

public:
	MeterDataDto();
	MeterDataDto(int, std::string, int, int, int, int, int, int, std::string, std::string, double, std::string);
	~MeterDataDto();

	void SetId(int);
	int GetId();

	void SetType(std::string);
	std::string GetType();

	void SetTypeId(int);
	int GetTypeId();

	void SetDay(int);
	int GetDay();

	void SetMonth(int);
	int GetMonth();

	void SetYear(int);
	int GetYear();

	void SetHour(int);
	int GetHour();

	void SetMinute(int);
	int GetMinute();

	void SetMeterId(std::string);
	std::string GetMeterId();

	void SetArea(std::string);
	std::string GetArea();

	void SetValue(double);
	double GetValue();

	void SetImageName(std::string);
	std::string GetImageName();

	std::string SaveString();
	std::string JsonString();
	std::string PhpString();
	std::string ToString();
};

#endif
