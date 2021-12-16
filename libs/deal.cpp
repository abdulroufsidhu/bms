#include "deal.h"

data::Deal::Deal() { }

data::Deal::Deal(std::vector<std::string> *args) {
	this->id = args->at(0);
	//         inventory   at(1)
	std::string select, from, where;
	select = "*";
	from = "inventory";
	where = " id ='" + args->at(1) + "'";
	std::vector<data::Inventory> i;
	db::PSQL::getInstance()->get(&select, &from, &where, &i);
	this->inventory = i.at(0);

	this->price = std::atof( args->at(2).c_str() );
	this->discount = std::atof( args->at(3).c_str() );

	//         person      at(4)
	from = "persons";
	where = "id ='" + args->at(4) + "'";
	std::vector<data::Person> p;
	db::PSQL::getInstance()->get(&select, &from, &where, &p);
	if (p.size() > 0)
	this->person = p.at(0);

	//         user        at(5)
	from = "users";
	where = "id ='" + args->at(5) + "'";
	std::vector<data::User> u;
	db::PSQL::getInstance()->get(&select, &from, &where, &u);
	this->user = u.at(0);

	this->quantity = std::atoi( args->at(6).c_str() );
	//         branch      at(7)
	from = "branches";
	where = "id = '" + args->at(7) + "'";
	std::vector<data::Branch> b;
	db::PSQL::getInstance()->get(&select, &from, &where, &b);
	this->branch = b.at(0);

	this->profit = std::atof ( args->at(8).c_str() );
	this->time = args->at(9);

	//    delete args;

}

std::string& data::Deal::getId() { return this->id; }
std::string& data::Deal::getTime() { return this->time; }
double& data::Deal::getPrice() { return this->price; }
float& data::Deal::getDiscount() { return this->discount; }
int& data::Deal::getQuantity() { return this->quantity; }
double& data::Deal::getProfit() { return this->profit; }

data::Inventory& data::Deal::getInventory() { return this->inventory; }
data::Person& data::Deal::getPerson() { return this->person; }
data::User& data::Deal::getUser() { return this->user; }
data::Branch& data::Deal::getBranch() { return this->branch; }
