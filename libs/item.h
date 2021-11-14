#ifndef ITEM_H
#define ITEM_H

#include "./common_headers.h"

namespace data {
    class Item;
}

class data::Item
{
private:
    std::string id
                , itemType
                , company
                , name
                , modal
                , version
                , vendor
                ;
public:
    Item();
    Item(std::vector<std::string> *args);

    std::string& getId();
    std::string& getItemType();
    std::string& getCompany();
    std::string& getName();
    std::string& getModal();
    std::string& getVersion();
    std::string& getVendor();
};

#endif // ITEM_H
