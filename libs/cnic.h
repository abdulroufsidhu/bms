#ifndef CNIC_H
#define CNIC_H

#include "./common_headers.h"


namespace data {
	class CNIC;
}

class data::CNIC
{
private:
    std::string id, text;

public:
    CNIC();
    CNIC(std::vector<std::string>* args );

    std::string& getId();
    std::string& getText();

};

#endif // CNIC_H
