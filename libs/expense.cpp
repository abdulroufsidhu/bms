#include "expense.h"

data::Expense::Expense() { }

data::Expense::Expense(std::vector<std::string> *args) {
    this->id = args->at(0);
//    branch at(1)
    std::string select, from, where;
    select = "*";
    from = "branches";
    where = "id = '" + args->at(1) + "'";
    std::vector<data::Branch> b;
    db::PSQL::getInstance()->get(&select, &from, &where, &b);
    this->branch = b.at(0);

    this->reason = args->at(2);
    this->cost = std::atof( args->at(3).c_str() );
    this->time = args->at(4);

//    delete args;

}

std::string& data::Expense::getId() { return this->id; }
std::string& data::Expense::getReason() { return this->reason; }
float& data::Expense::getCost() { return this->cost; }
std::string& data::Expense::getTime() { return this->time; }
data::Branch& data::Expense::getBranch() { return this->branch; }
