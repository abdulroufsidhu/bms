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
    std::vector<data::Organization> organizations;
    double salary;
    static data::User* currentUser;
    int index ;

public:
    User();
    User(std::vector<std::string>* args);

    static void setCurrentUser(std::vector<std::string> *args) ;
    static data::User* getCurrentUser();

    std::string& getId();
    data::Person& getPerson();
    data::Job& getJob();
    data::Branch& getBranch();
    std::vector<data::Organization>& getOrganization();
    void setOrganization(std::vector<data::Organization> *org_vector);
    double& getSalary();
    int& getIndex();

};

#endif // USER_H
