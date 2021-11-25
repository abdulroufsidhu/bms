#include "inventory.h"

data::Inventory::Inventory() { }

data::Inventory::Inventory(std::vector<std::string> *args) {
	this->id = args->at(0);
	// item at 1
	std::string select, from, where;
	select = "*";
	from = "items";
	where = " id ='" + args->at(1) +"'";
	std::vector<data::Item> i;
	db::PSQL::getInstance()->get(&select, &from, &where, &i);
	this->item = i.at(0);

	this->attributes = args->at(2);
	this->colour = args->at(3);
	this->serial = args->at(4);
	// branch at 5
	from = "branches";
	where = "id = '" + args->at(5) + "'";
	std::vector<data::Branch> b;
	db::PSQL::getInstance()->get(&select, &from, &where, &b);
	this->branch = b.at(0);

	this->quantity = std::atoi(args->at(6).c_str());
	this->price = std::atof(args->at(7).c_str());

	//    delete args;
}

std::string& data::Inventory::getId() { return this->id; }
std::string& data::Inventory::getAttributes() { return this->attributes; }
std::string& data::Inventory::getColour() { return this->colour; }
std::string& data::Inventory::getSerial() { return this->serial; }

data::Item& data::Inventory::getItem() { return this->item; }
data::Branch& data::Inventory::getBranch() { return this->branch; }

int& data::Inventory::getQuantity() { return this->quantity; }
double& data::Inventory::getPrice() { return this->price; }
