#ifndef REPORT_H
#define REPORT_H

#include "./common_headers.h"
#include "./branch.h"
#include "./api.h"

namespace data {
    class Report;
}

class data::Report
{
private:
    std::string id
//                , branch
//                , profit
                , time
                ;
    double profit;
    data::Branch branch;

public:
    Report();
    Report(std::vector<std::string> *args);

    std::string& getId();
    std::string& getTime();
    double& getProfit();
    data::Branch& getBranch();

};

#endif // REPORT_H
