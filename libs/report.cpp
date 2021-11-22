#include "report.h"

data::Report::Report() { }
data::Report::Report(std::vector<std::string> *args) {
	this->id = args->at(0);
	//branch
	std::string select, from, where;
	select = "*";
	from = "branches";
	where = "id = '" + args->at(1) + "'";
	std::vector<data::Branch> b;
	db::PSQL::getInstance()->get(&select, &from, &where, &b);
	this->branch = b.at(0);

	this->profit = std::atof( args->at(2).c_str() );
	this->time = args->at(3);

	//    delete args;
}

std::string& data::Report::getId() {return this->id;}
std::string& data::Report::getTime() { return this->time; }
double& data::Report::getProfit() { return this->profit;}
data::Branch& data::Report::getBranch() { return this->branch; }
