#ifndef DEAL_H
#define DEAL_H

#include "./common_headers.h"
#include "./inventory.h"
#include "./branch.h"
#include "./person.h"
#include "./user.h"
#include "./api.h"

namespace data {
    class Deal;
}

class data::Deal
{
private:
    std::string id
//                , inventory
//                , price
//                , discount
//                , person
//                , user
//                , quantity
//                , branch
//                , profit
                , time
                ;
    double price;
    float discount;
    int quantity;
    double profit;
    data::Person person;
    data::User user;
    data::Branch branch;
    data::Inventory inventory;
public:
    Deal();
    Deal(std::vector<std::string> *args);

    std::string& getId();
    std::string& getTime();
    double& getPrice();
    float& getDiscount();
    double& getProfit();
    int& getQuantity();
    data::Person& getPerson();
    data::User& getUser();
    data::Branch& getBranch();
    data::Inventory& getInventory();

};

#endif // DEAL_H
