#ifndef PSQL_H
#define PSQL_H

#include "./common_headers.h"
#include <pqxx/pqxx>
#include <qlayout.h>
#include <fstream>
#include <QDebug>
#include <QMessageBox>

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

public:
    static db::PSQL* getInstance();

    void set(std::string* query);

    std::ifstream getFile(std::string* name);
    void clearLayout(QLayout *l);
    void getConInfo(std::string *file_name = new std::string(""));

    template <typename T>
    inline void get(std::string * select, std::string* from, std::string* where, std::vector<T>* data) {
        try {
            if (!select->length()
                    || !from->length()
                    ) { throw " select or from is missing "; return; }
            pqxx::connection C(this->conInfo);
            if (!C.is_open()) {
                QMessageBox::information(0, "db error" , "database connection not established");
                throw "database connection not established";
                return;
            }
            std::string query = "SELECT " + (std::string) select->c_str()
                    + " FROM " + (std::string) from->c_str();
            if (where->length()) { query += " WHERE " + (std::string) where->c_str(); }
            pqxx::nontransaction N(C);
            pqxx::result R (N.exec(query));
            if (R.size() < 1) {
                QMessageBox::information(0,"get transaction error", "no record found ") ;
                throw "no record found ";
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
                    }
                    QMessageBox::information(0, "recieved data" , i[j].c_str() );
                }

                data->insert(data->begin() + tempindex , T(&str));
                tempindex ++;
            }

        }  catch (std::exception& e) {
            qCritical() << e.what();
        }
//        delete select;
//        delete from;
//        delete where;
    }
};

#endif // PSQL_H
