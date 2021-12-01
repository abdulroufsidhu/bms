#ifndef PSQL_H
#define PSQL_H

#include "./common_headers.h"
#include <pqxx/pqxx>
#include <qlayout.h>
#include <fstream>
#include <QDebug>
#include <QMessageBox>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <typeinfo>

namespace db {
	class PSQL;
}

class db::PSQL
{
private:
	PSQL();

private:
	static db::PSQL* instance;
	std::string db, usr, pswd, h_addr, port;
	std::string conInfo;
	std::vector<std::string> attribs;

public:
	static db::PSQL* getInstance();

	std::vector<std::string> &getAttribs();
	void updateAttribs();

	std::string set(std::string* query);

	std::ifstream getFile(std::string* name);
	static void clearLayout(QLayout *l);
	void getConInfo(std::string *file_name = new std::string(""));

	template <typename T >
	inline void get(std::string * select
									, std::string* from
									, std::string* where
									, std::vector<T>* data
									/*, statusbar *s*/
									) {
		try {
			if (!select->length()
					|| !from->length()
					) { QMessageBox::critical(0,"error", " select or from is missing "); return; }
			pqxx::connection C(this->conInfo);
			if (!C.is_open()) {
					QMessageBox::critical(0, "db error" , "database connection not established");
					return;
				}
			std::string query = "SELECT " + (std::string) select->c_str()
					+ " FROM " + (std::string) from->c_str();
			if (where->length()) { query += " WHERE " + (std::string) where->c_str(); }
			pqxx::nontransaction N(C);
			pqxx::result R (N.exec(query));
			if (R.size() < 1) {
					QMessageBox::information(0,"get transaction error", "no record found ") ;
					return;
				}
			short int tempindex = 0;
			for (auto i : R) {
					std::vector<std::string> str;
					for (int j=0; j< i.size(); j++) {
							try {
								str.insert(str.begin() + j, i[j].as<std::string>());

							}  catch (std::exception& e) {
								qCritical () << e.what();
								str.insert(str.begin() + j, "");
								qCritical() << QString(i[j].name()) + " : " + QString(e.what());
							}
						}
					data->insert(data->begin() + tempindex , T(&str));
					tempindex ++;
				}

		}  catch (std::exception& e) {
			qCritical() << e.what();
			QMessageBox::critical(0,from->c_str(),e.what());
		}
	}

	inline void getVecStr(std::string * select
												, std::string* from
												, std::string* where
												, std::vector<std::string>* data
												/*, statusbar *s*/
												) {
		try {
			if (!select->length()
					|| !from->length()
					) { QMessageBox::critical(0,"error", " select or from is missing "); return; }
			pqxx::connection C(this->conInfo);
			if (!C.is_open()) {
					QMessageBox::critical(0, "db error" , "unable to connect to database");
					return;
				}
			std::string query = "SELECT " + (std::string) select->c_str()
					+ " FROM " + (std::string) from->c_str();
			if (where->length()) { query += " WHERE " + (std::string) where->c_str(); }
			pqxx::nontransaction N(C);
			pqxx::result R (N.exec(query));
			if (R.size() < 1) {
					QMessageBox::critical(0,"get transaction error", "no record found ") ;
					return;
				}
			for (auto i : R) {
					for (int j=0; j< i.size(); j++) {
							try {
								data->insert(data->begin() + j, i[j].as<std::string>());

							}  catch (std::exception& e) {
								qCritical () << e.what();
								data->insert(data->begin() + j, "");

								qCritical() << QString(i[j].name()) + " : " + QString(e.what());
							}
						}
				}

		}  catch (std::exception& e) {
			qCritical() << e.what();
			//            QMessageBox::information(0,"error",e.what());
			qCritical() << e.what() ;
		}
	}

	inline void get(std::string *query
									, std::string *destination
									) {
		if(query->empty()) return;
		if (destination == NULL) return;
		try {
			pqxx::connection C(this->conInfo);
			if (!C.is_open()) QMessageBox::critical(0, "error", "unable to connect to database");
			pqxx::nontransaction N (C);
			pqxx::result R (N.exec(*query));
			if (R.size() < 1) QMessageBox::information(0, "caution", "no record found");
			for (auto c: R) {
					*destination = c[0].as<std::string>();
				}

		}  catch (std::exception &e) {
			qCritical() << e.what();
		}

	}
};

class CustomTabStyle : public QProxyStyle {
public:
	QSize sizeFromContents(ContentsType type, const QStyleOption* option,
												 const QSize& size, const QWidget* widget) const {
		QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
		if (type == QStyle::CT_TabBarTab) {
				s.transpose();
			}
		return s;
	}

	void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
		if (element == CE_TabBarTabLabel) {
				if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
						QStyleOptionTab opt(*tab);
						opt.shape = QTabBar::RoundedNorth;
						QProxyStyle::drawControl(element, &opt, painter, widget);
						return;
					}
			}
		QProxyStyle::drawControl(element, option, painter, widget);
	}
};

#endif // PSQL_H
