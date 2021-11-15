#include "organization.h"

data::Organization::Organization() { }

data::Organization::Organization( std::vector<std::string>* args ) {
    this->id = args->at(0);
    this->name = args->at(1);
    //Person
    std::string select, from, where;
    select = "*";
    from = "persons";
    where = "id ='" + args->at(2) + "'";
    std::vector<data::Person> p;
    db::PSQL::getInstance()->get(&select, &from, &where, &p);
    this->person = p.at(0);

    //Email
    from = "emails";
    where = "id ='" + args->at(3) + "'";
    std::vector<data::Email> e;
    db::PSQL::getInstance()->get(&select, &from, &where, &e);
    this->email = e.at(0);

//    delete args;
}

std::string& data::Organization::getId() { return this->id; }
std::string& data::Organization::getName() { return this->name; }
data::Person& data::Organization::getPerson () { return this->person; }
data::Email& data::Organization::getEmail() { return this->email; }

