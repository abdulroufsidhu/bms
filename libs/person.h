#ifndef PERSON_H
#define PERSON_H

#include "./common_headers.h"
#include "./email.h"
#include "./location.h"
#include "./contact.h"
#include "./cnic.h"
#include "./api.h"

namespace data {
	class Person;
}

class data::Person
{
private:
	std::string id, name;
	data::Email email;
	data::Contact contact;
	data::CNIC cnic;
	data::Location location;
public:
	Person();
	Person(std::vector<std::string>* args);

	data::Email& getEmail();
	data::Contact& getContact();
	data::CNIC& getCnic();
	data::Location& getLocation();
	std::string& getName();
	std::string& getId();

};

#endif // PERSON_H
