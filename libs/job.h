#ifndef JOB_H
#define JOB_H

#include "./common_headers.h"

namespace data {
	class Job;
}

class data::Job
{
private:
	std::string id
	, designation
	, grade
	;

public:
	Job();
	Job(std::vector<std::string> *args);

	std::string& getId();
	std::string& getDesignation();
	std::string& getGrade();
};

#endif // JOB_H
