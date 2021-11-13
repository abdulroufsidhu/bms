#ifndef USER_H
#define USER_H

#include "./common_headers.h"
#include "./person.h"
#include "./branch.h"
// #include "./job.h"

namespace data {
  class User;
}

class data::User
{
private:
    std::string id;
    data::Person person;
//    data::Job job;
    data::Branch branch;
    double salary;

public:
    User();
    User(std::vector<std::string>* args);

    std::string& getId();
    data::Person& getPerson();
    // data::Job& getJob();
    data::Branch& getBranch();
    double& getSalary();

};

#endif // USER_H
