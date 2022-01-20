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
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

class Database : public QObject {
	Q_OBJECT
//	QThread db_thread; // does not integrate well with the data handeling so making auth, branch, organization and user separate threaded instead

public:
	inline Database(QObject *parent = 0) : QObject(parent) {
//		db_thread.start();
		open_connection();
		close_connection();
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

	inline static QSqlQuery rawQuery(QString query) {
		if (db.isOpen()) db.close();
		db.open();
		QSqlQuery q(db);
		q.exec(query);
		db.close();
		return q;
	}

	inline static QSqlDatabase& getDB() {
		if (db.isOpen()) db.close();
		db.open();
		return Database::db;
	}

private:
	inline static QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
	inline Q_INVOKABLE void close_connection() {
		db.close();
	}

	inline Q_INVOKABLE bool open_connection() {
		db.setHostName("127.0.0.1");
		db.setDatabaseName("bmst");
		db.setUserName("bmst_user");
		db.setPassword("allah");
		return db.open();
	}

};

#endif // DB_H


