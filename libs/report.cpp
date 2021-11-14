#include "report.h"

data::Report::Report() { }
data::Report::Report(std::vector<std::string> *args) {
    this->id = args->at(0);
    //branch
    this->profit = std::atof( args->at(2).c_str() );
    this->time = args->at(3);

//    delete args;
}

std::string& data::Report::getId() {return this->id;}
std::string& data::Report::getTime() { return this->time; }
double& data::Report::getProfit() { return this->profit;}
data::Branch& data::Report::getBranch() { return this->branch; }
