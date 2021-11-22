#ifndef EMAIL_H
#define EMAIL_H

#include "./common_headers.h"

namespace data {
	class Email;
}

class data::Email
{
private:
	std::string id, text;
public:
	Email();
	Email(std::vector<std::string>* args);

	std::string& getId();
	std::string& getText();
};

#endif // EMAIL_H
