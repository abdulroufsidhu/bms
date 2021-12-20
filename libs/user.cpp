#include "user.h"

data::User* data::User::currentUser = NULL ;

data::User* data::User::getCurrentUser() {
	return data::User::currentUser ;
}

void data::User::setCurrentUser(std::vector<std::string>* args)  {
	if (data::User::currentUser == NULL) {
			data::User::currentUser = new data::User(args);
		}
}

data::User::User() { }
data::User::User(std::vector<std::string>* args) {
	if (args->size()<1) {QMessageBox::information(0,"caution","no user found"); return;}
	this->id = args->at(0);

	std::string select, from, where;
	select = "*";
	//Person
	if (!args->at(1).empty()) {
			from = "persons";
			where = "id ='" + args->at(1) + "'";
			std::vector<data::Person> p;
			db::PSQL::getInstance()->get(&select, &from, &where, &p);
			this->person = p.at(0);
		}
//job
//	if (!args->at(2).empty()) {
//			from = "jobs";
//			where = "id = '" + args->at(2) + "'";
//			std::vector<data::Job> j;
//			db::PSQL::getInstance()->get(&select, &from, &where, &j);
//			this->job = j.at(0);
//		}
//	//branch
//	if (!args->at(3).empty()) {
//			from = "branches";
//			where = "id = '" + args->at(3) + "'";
//			std::vector<data::Branch> b;
//			db::PSQL::getInstance()->get(&select, &from, &where, &b);
//			this->branch = b.at(0);
//		}

//	this->salary = std::atof( args->at(4).c_str() );

	//    delete args;
}

std::string& data::User::getId() { return this->id; }
data::Person& data::User::getPerson() { return this->person; }
data::Job& data::User::getJob() { return this->job; }
data::Branch& data::User::getBranch() { return this->branch; }
double& data::User::getSalary() { return this->salary; }

std::vector<data::Organization>& data::User::getOrganizationVec() { return this->organizations; }
void data::User::setOrganizationVec(std::vector<data::Organization> *org_vec) { this->organizations = *org_vec; }

void data::User::updateOrgVecBusiness() {
	std::string select, from, where;
	select = "*";
	from = "organizations";
	where = "founderid = '" + data::User::getCurrentUser()->getPerson().getId() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &this->getOrganizationVec());
}

void data::User::updateOrgVecEmployee() {
	std::string select="organizationid", from = "employee", where ="userid = '" + data::User::getCurrentUser()->getId() + "'";
	std::vector<std::string> orgIds, branchIds;
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &orgIds);

	select = "branchid";
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &branchIds);

	select = "*";
	from = "organizations";
	for (auto orgId : orgIds) {
		where = "id = '" + orgId + "'";
		db::PSQL::getInstance()->get(&select, &from, &where, &this->getOrganizationVec());
	}
	from = "branches";
	this->getBranchVec().clear();
	for (auto branchId : branchIds) {
		where = "id = '" + branchId + "'";
		db::PSQL::getInstance()->get(&select, &from, &where, &this->getBranchVec());
	}
	this->updateBranchesNamesList();
}

int& data::User::getOrgIndex() { return this->org_index; }
void data::User::setOrgIndex(int i) { this->org_index = i; }

std::vector<data::Branch>& data::User::getBranchVec() { return this->branches; }
void data::User::setBranchVec(std::vector<data::Branch> *branch_vec) { this->branches= *branch_vec; }

int& data::User::getBranchIndex() { return this->branc_index; }

void data::User::setBranchIndex(int i) { this->branc_index = i; }

void data::User::updateBranchVecBusiness() {
	if (this->getOrganizationVec().size() < 1) return;
	std::string select, from ,where, query;
	this->getBranchVec().clear();
	select = "*";
	from = "branches";
	where = "organizationid = '" + this->getOrganizationVec().at( this->getOrgIndex() ).getId() + "' AND active";
	db::PSQL::getInstance()->get(&select, &from, &where, &this->getBranchVec());
	updateBranchesNamesList();
}

QStringList &data::User::getBranchesNamesList() { return this->branchesNamesList; }

void data::User::updateBranchesNamesList() {
	if (this->getOrganizationVec().size() < 1) return;
	this->branchesNamesList.clear();
	for (short int i = 0 ; i < (short int) this->getBranchVec().size() ; i++ ) {
			this->branchesNamesList.insert( i , QString( this->getOrganizationVec().at ( this->getOrgIndex() ).getName().c_str()) + "\t:\t" + QString ( this->getBranchVec().at(i).getCode().c_str() ) );
		}
}


