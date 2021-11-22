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
	//    Auth(std::string* email, std::string* pswd);

	std::string& getId();
	std::string& getPassword();
	data::Email& getEmail();

	template<typename S, typename D>
	inline Auth (std::string* email, std::string* pswd, S* source_widow, D* destination_window ) {
		std::string select, from, where;
		select = "*";
		from = "emails";
		where = "email = '" + *email + "'";
		std::vector<data::Email> e;
		db::PSQL::getInstance()->get(&select, &from, &where, &e);
		this->email = e.at(0);

		std::string query = "select emailid from auth where emailid ='" + e.at(0).getId() + "' and password = '" + *pswd + "' and active ";
		std::string eid;
		db::PSQL::getInstance()->get(&query, &eid);
		//    QMessageBox::information(0,"email id", QString(eid.c_str()) + "\n" + QString(this->email.getId().c_str()));
		if (this->email.getId() != eid) { QMessageBox::critical(0, "error", "login credentials not confirmed."); return ; }

		std::vector<data::Person> per;
		from = "persons";
		where = "emailid = '" + this->email.getId() + "'";
		db::PSQL::getInstance()->get(&select, &from, &where, &per);
		std::vector<std::string> usr;
		from = "users";
		where = "personid = '" + per.at(0).getId() + "'";
		db::PSQL::getInstance()->getVecStr(&select, &from, &where, &usr);
		data::User::setCurrentUser(&usr);
		if (data::User::getCurrentUser()->getPerson().getId().length()) {
				std::vector<data::Organization> ov;
				from = "organizations";
				where = "founderid = '" + data::User::getCurrentUser()->getPerson().getId() + "'";
				db::PSQL::getInstance()->get(&select, &from, &where, &ov);
				data::User::getCurrentUser()->setOrganizationVec(&ov);
				source_widow->hide();
				destination_window->show();
			}
	}
};

#endif // AUTH_H
