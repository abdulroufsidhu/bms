#ifndef LOCATION_H
#define LOCATION_H

#include "./common_headers.h"

namespace data {
	class Location;
}

class data::Location
{
private:
	std::string id, city, country, address;
public:
	Location();
	Location(std::vector<std::string>* args);

	std::string& getId();
	std::string& getCity();
	std::string& getCountry();
	std::string& getAddress();

};

#endif // LOCATION_H
