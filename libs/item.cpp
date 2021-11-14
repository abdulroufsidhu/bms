#include "item.h"

data::Item::Item() { }

data::Item::Item(std::vector<std::string> *args) {
    this->id = args->at(0);
    this->itemType = args->at(1);
    this->company = args->at(2);
    this->name = args->at(3);
    this->modal = args->at(4);
    this->version = args->at(5);
    this->vendor = args->at(6);

//    delete args;
}

std::string& data::Item::getId() { return this->id; }
std::string& data::Item::getItemType() { return this->itemType; }
std::string& data::Item::getCompany() { return this->company; }
std::string& data::Item::getName() { return this->name; }
std::string& data::Item::getModal() { return this->modal; }
std::string& data::Item::getVersion() { return this->version; }
std::string& data::Item::getVendor() { return this->vendor; }



