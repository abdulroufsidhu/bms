#pragma once
#ifndef DB_H
#define DB_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QThread>
#include <QSqlError>

class Database : public QObject {
	Q_OBJECT
//	QThread db_thread;

public:
	inline Database(QObject *parent = 0) : QObject(parent) {
//		db_thread.start();
	}
	inline ~Database() {
//		db_thread.quit();db_thread.wait();
	}
	inline Q_INVOKABLE QString insert(QString query) {
		open_connection();
		if (!db.isOpen()) return "unable to connect to database";
		QSqlQuery q(db);
		q.exec(query);
		close_connection();
		return q.lastError().text();
	}

	inline void begin() {
		if (db.isOpen()) return;
		open_connection();
		QSqlQuery q("BEGIN;", db);
	}

	inline QString commit() {
		QSqlQuery q("COMMIT;", db);
		if (!q.isValid()) {
			q.exec("ROLLBACK;");
		}
		if (db.isOpen()) close_connection();
		return q.lastError().text();

	}

	inline QSqlQuery rawQuery(QString query) {
		QSqlQuery q(db);
		q.exec(query);
		return q;
	}

	inline static QSqlDatabase& getDB() {
		if (!db.isOpen()) {
			db.setHostName("127.0.0.1");
			db.setDatabaseName("bmst");
			db.setUserName("abdul");
			db.setPassword("allah");
			db.open();
		}
		return db;
	}

private:
	inline static QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
	inline Q_INVOKABLE void close_connection() {
		db.close();
	}

	inline Q_INVOKABLE bool open_connection() {
		db.setHostName("127.0.0.1");
		db.setDatabaseName("bmst");
		db.setUserName("abdul");
		db.setPassword("allah");
		return db.open();
	}

};

#endif // DB_H


