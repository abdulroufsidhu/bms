#include "api.h"

db::PSQL *db::PSQL::instance = NULL;

db::PSQL::PSQL() {
	try {
		db::PSQL::getConInfo();
		pqxx::connection C(this->conInfo);
		if (!C.is_open()) {
				delete this;
			}
	}  catch (std::exception& e) {
		qCritical () << e.what();
	}
}
db::PSQL* db::PSQL::getInstance() {
	if (db::PSQL::instance == NULL) { db::PSQL::instance = new db::PSQL(); }
	return db::PSQL::instance;
}

std::ifstream db::PSQL::getFile(std::string* name) {
	std::ifstream f;
	f.open(name->c_str());
	return f;
}

void db::PSQL::clearLayout(QLayout* l) {
	QLayoutItem* item;
	while ( (item = l->takeAt(0)) ) {
			delete item;
		}
}

void db::PSQL::getConInfo(std::string* file_name) {
	std::string file ;
	file_name->length() ? file = file_name->c_str() : file = "con.conf" ;
	std::string line = "";
	std::ifstream f = db::PSQL::getFile( &file );
	while (std::getline(f,line)) {
			QString l = line.c_str();
			qCritical() << l;
			if(l.contains("user = ")) { this->usr = line;}
			if (l.contains("password = ")) { this->pswd = line; }
			if (l.contains("hostaddr = ")) { this->h_addr = line; }
			if (l.contains("port = ")) { this->port = line; }
			if (l.contains("dbname = ")) { this->db = line; }
		}
	delete file_name;
	this->conInfo = this->db + " " + this->usr + " " + this->pswd + " " + this->h_addr + " " + this->port;
}

std::string db::PSQL::set(std::string *query) {
	std::string err = "";
	try {
		pqxx::connection C(this->conInfo);
		if (!C.is_open()) {
				QMessageBox::critical(0, "db error" , "database connection not established");
				return err;
			}
		pqxx::work W(C);
		W.exec(query->c_str());
		W.commit();
		qInfo() << "operation successfull";
	}  catch (std::exception& e) {
		qCritical() << e.what();
		err = e.what();
		QMessageBox::critical(0,"error updating data", e.what());
	}
	return err;
}

std::vector<std::string> &db::PSQL::getAttribs() {
	return this->attribs;
}

void db::PSQL::updateAttribs() {
	this->attribs.clear();
	std::string select, from, where;
	select = "attrib"; from = "attributes"; where = "";
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &this->getAttribs());
}


