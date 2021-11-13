#include "branch.h"

data::Branch::Branch() { }

data::Branch::Branch(std::vector<std::string>* args) {
    this->id = args->at(0);
    this->name = args->at(1);
    // location
    // organization
    // contact
    // email 

}

std::string& data::Branch::getId() { return this->id; }
std::string& data::Branch::getName () { return this->name; }
data::Location& data::Branch::getLocation () { return this->location; }
data::Organization& data::Branch::getOrganization() { return this->organization; }
data::Contact& data::Branch::getContact() { return this->contact; }
data::Email& data::Branch::getEmail() { return this->email; }




