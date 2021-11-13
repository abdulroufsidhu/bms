#include "user.h"

data::User::User() { }

data::User::User(std::vector<std::string>* args) {
    this->id = args->at(0);
    //Person
    //job
    //branch
    this->salary = atof( args->at(4) );
}

std::string& data::User::getId() { return this->id; }
data::Person& data::User::getPerson() { return this->person; }
// data::Job& data::User::getJob() { return this->job; }
data::Branch& data::User::getBranch() { return this->branch; }
double& data::User::getSalary() { return this->salary; }


