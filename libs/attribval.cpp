#include "attribval.h"

data::AttribVal::AttribVal() {}

data::AttribVal::AttribVal(std::vector<std::string>* args) {
	this->id=args->at(0);
	std::string select, from, where;
	std::vector<std::string> attrVec;
	select="attrib"; from = "attributes"; where = "id = '"+ args->at(1) + "'";
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &attrVec);
	this->attribute = attrVec.at(0);
	this->value = args->at(2);
}

std::string& data::AttribVal::getId() { return this->id; }
std::string& data::AttribVal::getAttribute() { return this->attribute; }
std::string& data::Va

