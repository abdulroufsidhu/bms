#include "person.h"

data::Person::Person() { }

data::Person::Person(std::vector<std::string>* args) { 
	this->id = args->at(0);
	std::string select, from, where;
	select = "*";
	// emailid
	from = "emails";
	where = "id ='" + args->at(1) + "'";
	std::vector<data::Email> e;
	db::PSQL::getInstance()->get(&select, &from, &where, &e);
	this->email = e.at(0);

	// contactid
	from = "contacts";
	where = "id ='" + args->at(2) + "'";
	std::vector<data::Contact> c;
	db::PSQL::getInstance()->get(&select, &from, &where, &c);
	this->contact = c.at(0);

	// cnicid
	from = "cnics";
	where = "id ='" + args->at(3) + "'";
	std::vector<data::CNIC> cn;
	db::PSQL::getInstance()->get(&select, &from, &where, &cn);
	this->cnic = cn.at(0);

	// locationid
	from = "locations";
	where = "id ='" + args->at(4) + "'";
	std::vector<data::Location> l;
	db::PSQL::getInstance()->get(&select, &from, &where, &l);
	this->location = l.at(0);

	this->name = args->at(5);

	//    delete args;
}

std::string& data::Person::getId() { return this->id; }
std::string& data::Person::getName() { return this->name; }

data::Email& data::Person::getEmail() { return this->email; }
data::Contact& data::Person::getContact() { return this->contact; }
data::CNIC& data::Person::getCnic () { return this->cnic; }
data::Location& data::Person::getLocation() { return this->location; }
