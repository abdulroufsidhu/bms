#include "email.h"

data::Email::Email() { }

data::Email::Email(std::vector<std::string>* args) {
    this->id = args->at(0);
    this->text = args->at(1);

//    delete args;
}

std::string& data::Email::getId() { return this->id; }
std::string& data::Email::getText() { return this->text; }
