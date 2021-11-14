#ifndef BRANCH_H
#define BRANCH_H

#include "./common_headers.h"
#include "./organization.h"
#include "./location.h"
#include "./contact.h"
#include "./email.h"
#include "./api.h"

namespace data {
  class Branch;
}

class data::Branch
{
private:
    std::string id, name;
    data::Location location;
    data::Organization organization;
    data::Contact contact;
    data::Email email;

public:
    Branch();
    Branch(std::vector<std::string>* args) ;

    std::string& getId();
    std::string& getName();
    data::Location& getLocation();
    data::Organization& getOrganization();
    data::Contact& getContact();
    data::Email& getEmail();

};

#endif // BRANCH_H
