#include "menu.h"

Menu::Menu() {
}

Menu::Menu(std::string weekday, int day, int month, int year, std::string title, std::string description) {
	_weekday = weekday;
	_day = day;
	_month = month;
	_year = year;
	_title = title;
	_description = description;
}

Menu::~Menu() {
}

void Menu::setWeekday(std::string weekday) {
	_weekday = weekday;
}

void Menu::setDay(int day) {
	_day = day;
}

void Menu::setMonth(int month) {
	_month = month;
}

void Menu::setYear(int year) {
	_year = year;
}

void Menu::setTitle(std::string title) {
	_title = title;
}

void Menu::setDescription(std::string description) {
	_description = description;
}

std::string Menu::getWeekday() {
	return _weekday;
}

int Menu::getDay(){
	return _day;
}

int Menu::getMonth(){
	return _month;
}

int Menu::getYear(){
	return _year;
}

std::string Menu::getTitle() {
	return _title;
}

std::string Menu::getDescription() {
	return _description;
}

std::string Menu::toString() {
	std::string str =
			std::string("Menu { title: ") + _title
			+ std::string("; description: ") + _description
			+ std::string("; weekday: ") + _weekday
			+ std::string("; day: ") + Tools::convertIntToStr(_day)
			+ std::string("; month: ") + Tools::convertIntToStr(_month)
			+ std::string("; year: ") + Tools::convertIntToStr(_year)
			+ std::string(" }");
	return str;
}
