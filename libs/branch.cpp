#include "branch.h"

data::Branch::Branch() { }

data::Branch::Branch(std::vector<std::string>* args) {
    this->id = args->at(0);
    this->name = args->at(1);
    std::string select, from, where;

    std::vector<data::Location>* l = new std::vector<data::Location>();
    select = "*";
    from = "location";
    where = "id = " + args->at(2);
    db::PSQL::getInstance()->get(&select, &from, &where, l);
    this->location = l->at(0);

    std::vector<data::Organization>* o = new std::vector<data::Organization>();
    select = "*";
    from = "organizations";
    where = "id = " + args->at(3);
    db::PSQL::getInstance()->get(&select, &from, &where, o);
    this->organization = o->at(0);

    std::vector<data::Contact>* c = new std::vector<data::Contact>();
    select = "*";
    from = "contacts";
    where = "id = " + args->at(4);
    db::PSQL::getInstance()->get(&select, &from, &where, c);
    this->contact = c->at(0);

    std::vector<data::Email>* e = new std::vector<data::Email>();
    select = "*";
    from = "location";
    where = "id = " + args->at(5);
    db::PSQL::getInstance()->get(&select, &from, &where, e);
    this->email = e->at(0);

    delete l;
    delete o;
    delete c;
    delete e;

    // location         2
    // organization     3
    // contact          4
    // email            5

//    delete args;

}

std::string& data::Branch::getId() { return this->id; }
std::string& data::Branch::getName () { return this->name; }
data::Location& data::Branch::getLocation () { return this->location; }
data::Organization& data::Branch::getOrganization() { return this->organization; }
data::Contact& data::Branch::getContact() { return this->contact; }
data::Email& data::Branch::getEmail() { return this->email; }




