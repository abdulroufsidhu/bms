#pragma once

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QVariant>
#include <QThread>
#include <QSqlError>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

#ifndef DB_H
#define DB_H

class Database : public QObject {
	Q_OBJECT
public:
	inline Database(QObject *parent = nullptr) : QObject(parent) { open_connection(); }
	inline ~Database() {  }

	inline static QSqlQuery rawQuery(QString query) {
		if (!db.isOpen() )
		db.open();
		QSqlQuery q(db);
		q.exec(query);
		return q;
	}
	inline static QSqlDatabase& getDB() {
		if (!db.isOpen())
		db.open();
		return Database::db;
	}

private:
	inline static QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
	inline Q_INVOKABLE void close_connection() { db.close(); }

	inline Q_INVOKABLE bool open_connection() {
		db.setHostName("localhost");
		db.setDatabaseName("bmst");
		db.setUserName("bmst_user");
		db.setPassword("allah");
		return db.open();
	}

};

#endif // DB_H


