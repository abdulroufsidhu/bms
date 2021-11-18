#include "auth.h"

data::Auth::Auth() { }

data::Auth::Auth(std::vector<std::string> * args) {

    // below logic seems to be wrong it should get email, password and verify only returning current user instead of current logic.
    this->id = args->at(0);
    this->password = args->at(1);
    // email at 2 and boolean for activation status is at 3 need to check where active == true in database query

//    delete args;
}

data::Auth::Auth(std::string* email, std::string* pswd) {
    std::string select, from, where;
    select = "*";
    from = "emails";
    where = "email = '" + *email + "'";
    std::vector<data::Email> e;
    db::PSQL::getInstance()->get(&select, &from, &where, &e);
    this->email = e.at(0);

    std::string query = "select emailid from auth where password = '" + *pswd + "'";
    std::string eid;
    db::PSQL::getInstance()->get(&query, &eid);
    if (this->email.getId() != eid) { QMessageBox::critical(0, "error", "login credentials not confirmed."); return ; }

    std::vector<data::Person> per;
    from = "persons";
    where = "emailid = '" + this->email.getId() + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &per);
    std::vector<data::User> usr;
    from = "users";
    where = "personid = '" + per.at(0).getId() + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &usr);
    data::User::setCurrentUser(usr.at(0));
}

std::string& data::Auth::getId() { return this->id; }
std::string& data::Auth::getPassword() { return this->password; }
data::Email& data::Auth::getEmail() { return this->email; }

