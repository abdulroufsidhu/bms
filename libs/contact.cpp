#include "contact.h"

data::Contact::Contact() { }

data::Contact::Contact(std::vector<std::string>* args) {
	this->id = args->at(0);
	this->text = args->at(1);

	//    delete args;
}

std::string& data::Contact::getId() { return this->id; }
std::string& data::Contact::getText() { return this->text; }


