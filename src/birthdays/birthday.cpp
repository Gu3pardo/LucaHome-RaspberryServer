#include "birthday.h"

Birthday::Birthday() {
}

Birthday::Birthday(int _id, std::string _name, int _day, int _month,
		int _year) {
	id = _id;
	name = _name;
	day = _day;
	month = _month;
	year = _year;
}

Birthday::~Birthday() {
}

void Birthday::setId(int _id) {
	id = _id;
}

void Birthday::setName(std::string _name) {
	name = _name;
}

void Birthday::setDay(int _day) {
	day = _day;
}

void Birthday::setMonth(int _month) {
	month = _month;
}

void Birthday::setYear(int _year) {
	year = _year;
}

int Birthday::getId() {
	return id;
}

std::string Birthday::getName() {
	return name;
}

int Birthday::getDay() {
	return day;
}

int Birthday::getMonth() {
	return month;
}

int Birthday::getYear() {
	return year;
}

std::string Birthday::toString() {
	std::string str = std::string("Birthday { id: ")
			+ Tools::convertIntToStr(id) + std::string("; name: ") + name
			+ std::string("; day: ") + Tools::convertIntToStr(day)
			+ std::string("; month: ") + Tools::convertIntToStr(month)
			+ std::string("; year: ") + Tools::convertIntToStr(year)
			+ std::string(" }");
	return str;
}
