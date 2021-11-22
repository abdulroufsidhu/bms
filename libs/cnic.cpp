#include "cnic.h"

data::CNIC::CNIC() { }

data::CNIC::CNIC(std::vector<std::string>* args) {
	this->id = args->at(0);
	this->text = args->at(1);

	//    delete args;
}

std::string& data::CNIC::getId() { return this->id; }
std::string& data::CNIC::getText() { return this->text; }
