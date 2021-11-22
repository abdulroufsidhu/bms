#ifndef EXPENSE_H
#define EXPENSE_H

#include "./common_headers.h"
#include "./branch.h"
#include "./api.h"

namespace data {
	class Expense;
}

class data::Expense
{
public:
	std::string id
	//                , branch
	, reason
	//                , cost
	, time
	;
	float cost;
	data::Branch branch;
public:
	Expense();
	Expense(std::vector<std::string> *args);

	std::string& getId();
	std::string& getReason();
	float& getCost();
	std::string& getTime();

	data::Branch& getBranch();

};

#endif // EXPENSE_H
