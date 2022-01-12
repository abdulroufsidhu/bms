#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtWidgets/QWidget>

class DB : public QObject {
	Q_OBJECT

private:
	static DB* instance;

private:
	inline DB (QObject *parent = 0) : QObject(parent) { }
public:
	DB* getInstance() {
		if (DB::instance == nullptr) {
			DB::instance = new DB();
		}
		return DB::instance;
	}

};

DB *instance = nullptr;

#endif // DB_H
