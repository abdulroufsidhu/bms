#include "deal.h"

data::Deal::Deal() { }

data::Deal::Deal(std::vector<std::string> *args) {
    this->id = args->at(0);
//    std::vector
    //         inventory   at(1)
    this->price = std::atof( args->at(2).c_str() );
    this->discount = std::atof( args->at(3).c_str() );
    //         person      at(4)
    //         user        at(5)
    this->quantity = std::atoi( args->at(6).c_str() );
    //         branch      at(7)
    this->profit = std::atof ( args->at(8).c_str() );
    this->time = args->at(9);

//    delete args;

}

std::string& data::Deal::getId() { return this->id; }
std::string& data::Deal::getTime() { return this->time; }
double& data::Deal::getPrice() { return this->price; }
float& data::Deal::getDiscount() { return this->discount; }
int& data::Deal::getQuantity() { return this->quantity; }
double& data::Deal::getProfit() { return this->profit; }

