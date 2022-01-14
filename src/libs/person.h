#include "address.h"
#pragma once
#ifndef EMAIL_H
#define EMAIL_H

class Email : public QObject {
	Q_OBJECT
public:
	inline Email (QObject *parent = 0) : QObject(parent) {}
	inline ~Email () {}
	inline QString& getId() {return this->id;}
	inline QString& getText() {return this->text;}

	inline void update(QString& email) {
		Database db;
		QSqlQuery q = db.rawQuery(QString("SELECT id,name FROM EMAILS WHERE name = '%1';").arg(email));
		if (!q.isValid()) return;
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}

	inline bool insert(QString& email) {
		Database db;
		QSqlQuery q = db.rawQuery(QString(" INSERT INTO EMAILS (name) VALUES('%1'); ").arg(email));
		if (q.lastError().text().isEmpty()) {
			this->update(email);
			return true;
		}
		return false;
	}

private:
	QString id;
	QString text;
};

#endif // EMAIL_H

#ifndef CNIC_H
#define CNIC_H

class CNIC : public QObject {
	Q_OBJECT
private:
	QString id;
	QString text;

public:
	inline CNIC (QObject *parent = 0) : QObject(parent) {}
	inline ~CNIC() {}
	inline QString& getId() {return this->id;}
	inline QString& getText() {return this->text;}

	inline void update(QString& cnic) {
		Database db;
		QSqlQuery q = db.rawQuery( QString("SELECT id, name FROM CNICS WHERE name = '%1';").arg(cnic) );
		if (!q.isValid()) return;
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}

	inline bool insert (QString& cnic) {
		Database db;
		QSqlQuery q = db.rawQuery( QString(" INSERT INTO CNICS(name)VALUES('%1') ;").arg(cnic) );
		if (!q.isValid() || !q.lastError().text().isEmpty()) {
			q.exec("ROLLBACK;");
			return false;
		}
		this->update(cnic);
		return true;
	}

};

#endif // CNIC_H

#ifndef CONTACT_H
#define CONTACT_H

class Contact : public QObject {
	Q_OBJECT
private:
	QString id, text;
public:
	inline Contact (QObject* parent = 0) : QObject(parent) {}
	inline ~Contact () {};
	inline QString& getId() {return this->id;}
	inline QString& getText() {return this->text;}
	inline void update(QString& number) {
		Database db;
		QSqlQuery q = db.rawQuery( QString("SELECT id, name FROM CONTACTS WHERE name = '%1';").arg(number) );
		if (!q.isValid() || !q.lastError().text().isEmpty()) return;
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	inline bool insert (QString& number) {
		Database db;
		QSqlQuery q = db.rawQuery( QString("INSERT INTO CONTACTS(name) VALUES ('%1'); ").arg(number) );
		if (!q.isValid() || !q.lastError().text().isEmpty()) return false;
		this->update(number);
		return true;
	}

};

#endif // CONTACT_H

#ifndef PERSON_H
#define PERSON_H

#endif // PERSON_H
