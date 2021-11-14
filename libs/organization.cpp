#include "organization.h"

data::Organization::Organization() { }

data::Organization::Organization( std::vector<std::string>* args ) {
    this->id = args->at(0);
    this->name = args->at(1);
    //Person
    //Email

//    delete args;
}

std::string& data::Organization::getId() { return this->id; }
std::string& data::Organization::getName() { return this->name; }
data::Person& data::Organization::getPerson () { return this->person; }
data::Email& data::Organization::getEmail() { return this->email; }

