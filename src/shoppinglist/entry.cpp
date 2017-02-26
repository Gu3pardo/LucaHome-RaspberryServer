#include "entry.h"

Entry::Entry() {
}

Entry::Entry(int _id, std::string _name, std::string _group, int _quantity) {
	id = _id;
	name = _name;
	group = _group;
	quantity = _quantity;
}

Entry::~Entry() {
}

void Entry::setId(int _id) {
	id = _id;
}

void Entry::setName(std::string _name) {
	name = _name;
}

void Entry::setGroup(std::string _group) {
	group = _group;
}

void Entry::setQuantity(int _quantity) {
	quantity = _quantity;
}

int Entry::getId() {
	return id;
}

std::string Entry::getName() {
	return name;
}

std::string Entry::getGroup() {
	return group;
}

int Entry::getQuantity() {
	return quantity;
}

std::string Entry::toString() {
	std::string str = std::string("Entry { id: ")
			+ Tools::convertIntToStr(id)
			+ std::string("; name: ") + name
			+ std::string("; group: ") + group
			+ std::string("; quantity: ") + Tools::convertIntToStr(quantity)
			+ std::string(" }");
	return str;
}
