#ifndef USER_H
#define USER_H

#include "./common_headers.h"
#include "./person.h"
#include "./branch.h"
#include "./job.h"
#include "./api.h"

namespace data {
  class User;
}

class data::User
{
private:
    std::string id;
    data::Person person;
    data::Job job;
    data::Branch branch;
    double salary;
    static data::User* currentUser;

public:
    User();
    User(std::vector<std::string>* args);

    static data::User* setCurrentUser(data::User& u);
    static data::User* getCurrentUser();

    std::string& getId();
    data::Person& getPerson();
    data::Job& getJob();
    data::Branch& getBranch();
    double& getSalary();

};

#endif // USER_H
