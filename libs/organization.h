#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include "./common_headers.h"
#include "./person.h"

namespace data {
    class Organization;
}

class data::Organization
{
private:
    std::string id, name ;
    data::Person person;
    data::Email email;

public:
    Organization();
    Organization(std::vector<std::string>* args);

    std::string& getId();
    std::string& getName();
    data::Person& getPerson();
    data::Email& getData();
};

#endif // ORGANIZATION_H
