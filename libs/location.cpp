#include "location.h"

data::Location::Location() { }

data::Location::Location(std::vector<std::string> * args) {
    this->id = args->at(0);
    this->city = args->at(1);
    this->country = args->at(2);
    this->address = args->at(3);
}

std::string& data::Location::getid() {
    return this->id;
}
std::string& data::Location::getCity() {
    return this->city;
}
std::string& data::Location::getCountry() {
    return this->country;
}
std::string& data::Location::getAddress() {
    return this->address;
}