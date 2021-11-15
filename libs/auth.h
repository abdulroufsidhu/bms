#ifndef AUTH_H
#define AUTH_H

#include "./common_headers.h"
#include "./api.h"
#include "./email.h"
#include "./person.h"
#include "./user.h"

namespace data {
    class Auth;
}

class data::Auth
{
private:
    std::string id
                , password
                ;
    data::Email email;

public:
    Auth();
    Auth(std::vector<std::string> *args);
    Auth(std::string* email, std::string* pswd);

    std::string& getId();
    std::string& getPassword();
    data::Email& getEmail();
};

#endif // AUTH_H
