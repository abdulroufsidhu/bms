#include "auth.h"

data::Auth::Auth() { }

data::Auth::Auth(std::vector<std::string> * args) {

    // below logic seems to be wrong it should get email, password and verify only returning current user instead of current logic.
    this->id = args->at(0);
    this->password = args->at(1);
    // email at 2 and boolean for activation status is at 3 need to check where active == true in database query

//    delete args;
}

std::string& data::Auth::getId() { return this->id; }
std::string& data::Auth::getPassword() { return this->password; }
data::Email& data::Auth::getEmail() { return this->email; }

