#include "listedmenu.h"

ListedMenu::ListedMenu() {
}

ListedMenu::ListedMenu(int id, std::string description, int rating, int lastSuggestion) {
	_id = id;
	_description = description;
	_rating = rating;
	_lastSuggestion = lastSuggestion;
}

ListedMenu::~ListedMenu() {
}

void ListedMenu::setId(int id) {
	_id = id;
}

void ListedMenu::setDescription(std::string description) {
	_description = description;
}

void ListedMenu::setRating(int rating) {
	_rating = rating;
}

void ListedMenu::setLastSuggestion(int lastSuggestion) {
	_lastSuggestion = lastSuggestion;
}

int ListedMenu::getId(){
	return _id;
}

std::string ListedMenu::getDescription() {
	return _description;
}

int ListedMenu::getRating(){
	return _rating;
}

int ListedMenu::isLastSuggestion(){
	return _lastSuggestion;
}

std::string ListedMenu::toString() {
	std::string str =
			std::string("ListedMenu { id: ") + Tools::convertIntToStr(_id)
			+ std::string("; description: ") + _description
			+ std::string("; rating: ") + Tools::convertIntToStr(_rating)
			+ std::string("; isLastSuggestion: ") + Tools::convertIntToStr(_lastSuggestion)
			+ std::string(" }");
	return str;
}
