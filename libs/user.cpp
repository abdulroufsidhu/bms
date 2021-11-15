#include "user.h"

data::User* data::User::currentUser = NULL;

data::User* data::User::getCurrentUser() {
    return data::User::currentUser ;
}

data::User* data::User::setCurrentUser(data::User &u) {
    if (data::User::currentUser == NULL) {
        data::User::currentUser = &u;
    }
    return data::User::currentUser;
}

data::User::User() { }
data::User::User(std::vector<std::string>* args) {
    this->id = args->at(0);

    std::string select, from, where;
    select = "*";
    //Person
    from = "persons";
    where = "id ='" + args->at(1) + "'";
    std::vector<data::Person> p;
    db::PSQL::getInstance()->get(&select, &from, &where, &p);
    this->person = p.at(0);
    //job
    from = "jobs";
    where = "id = '" + args->at(2) + "'";
    std::vector<data::Job> j;
    db::PSQL::getInstance()->get(&select, &from, &where, &j);
    this->job = j.at(0);
    //branch
    from = "branches";
    where = "id = '" + args->at(3) + "'";
    std::vector<data::Branch> b;
    db::PSQL::getInstance()->get(&select, &from, &where, &b);
    this->branch = b.at(0);

    this->salary = std::atof( args->at(4).c_str() );

//    delete args;
}

std::string& data::User::getId() { return this->id; }
data::Person& data::User::getPerson() { return this->person; }
data::Job& data::User::getJob() { return this->job; }
data::Branch& data::User::getBranch() { return this->branch; }
double& data::User::getSalary() { return this->salary; }


