#ifndef CONTACT_H
#define CONTACT_H

#include "./common_headers.h"

namespace data {
    class Contact;
}

class data::Contact
{
private:
    std::string id, text;

public:
    Contact();
    Contact(std::vector<std::string>* args);

    std::string& getId();
    std::string& getText();
    
};

#endif // CONTACT_H
