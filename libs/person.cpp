#include "person.h"

data::Person::Person() { }

data::Person::Person(std::vector<std::string>* args) { 
    this->id = args->at(0);
    // emailid
    // contactid
    // cnicid
    // locationid
    this->name = args->at(5);
}

data::Email& data::Person::getEmail() {
  return this->email;
}

data::Contact& data::Person::getContact() {
  return this->contact;
}

data::CNIC& data::Person::getCnic () {
  return this->cnic;
}

data::Location& data::Person::getLocation() {
  return this->location;
}



