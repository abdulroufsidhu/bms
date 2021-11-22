#include "job.h"

data::Job::Job() { }

data::Job::Job(std::vector<std::string> *args) {
	this->id = args->at(0);
	this->designation = args->at(1);
	this->grade = args->at(2);

	//    delete args;
}

std::string& data::Job::getId() {return this->id;}
std::string& data::Job::getDesignation() {return this->designation; }
std::string& data::Job::getGrade() {return this->grade; }
