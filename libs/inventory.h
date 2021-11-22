#ifndef INVENTORY_H
#define INVENTORY_H

#include "./common_headers.h"
#include "./branch.h"
#include "./item.h"
#include "./api.h"

namespace data {
	class Inventory;
}

class data::Inventory
{
private:
	std::string id
	//, item
	, attributes
	, colour
	, serial
	//, branch
	//                , quantity
	//, price
	;
	data::Item item;
	data::Branch branch;
	int quantity;
	double price;

public:
	Inventory();
	Inventory(std::vector<std::string> *args);

	std::string& getId();
	std::string& getAttributes();
	std::string& getColour();
	std::string& getSerial();
	data::Item& getItem();
	data::Branch& getBranch();
	int& getQuantity();
	double& getPrice();

};

#endif // INVENTORY_H
