#pragma once
#include "address.h"

#ifndef EMAIL_H
#define EMAIL_H
class Email: public QObject {
	Q_OBJECT
private:
	QString id, text;
public:
	inline Email (QObject *parent = 0) : QObject(parent) {}
	inline ~Email () {}
	QString& getId();
	QString& getText();
	QString update( QString& email);
	void copy(Email& e);
};
inline QString& Email::getId() { return this->id; }
inline QString& Email::getText() { return this->text; }
inline void Email::copy(Email &e) { this->id = e.id; this->text = e.text; }
inline QString Email::update(QString& email) {
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT id, name FROM EMAILS WHERE name = '%1' ;").arg(email) );
	db.close();
	qCritical() << q.lastError().text();
	if (!q.lastError().text().isEmpty() ) return "invalid email ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	qCritical() << this->text;
	return q.lastError().text();
}

#endif //EMAIL_H

#ifndef CNIC_H
#define CNIC_H
class CNIC: public QObject {
	Q_OBJECT
private:
	QString id, text;
public:
	inline CNIC (QObject *parent = 0) : QObject(parent) {}
	inline ~CNIC () {}
	QString& getId();
	QString& getText();
	QString update(QString & number);
	void copy(CNIC& e);
};
inline QString& CNIC::getId() { return this->id; }
inline QString& CNIC::getText() { return this->text; }
inline void CNIC::copy(CNIC &e) { this->id = e.id; this->text = e.text; }
inline QString CNIC::update(QString& number) {
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT id, name FROM CNICS WHERE name = '%1' ;").arg(number) );
	db.close();
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid cnic ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
#endif //CNIC_H

#ifndef CONTACT_H
#define CONTACT_H
class Contact: public QObject {
	Q_OBJECT
private:
	QString id, text;
public:
	inline Contact (QObject *parent = 0) : QObject(parent) {}
	inline ~Contact () {}
	QString& getId();
	QString& getText();
	QString update(QString& contact);
	void copy(Contact& e);
};
inline QString& Contact::getId() { return this->id; }
inline QString& Contact::getText() { return this->text; }
inline void Contact::copy(Contact &e) { this->id = e.id; this->text = e.text; }
inline QString Contact::update(QString& number) {
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT id, name FROM CONTACTS WHERE name = '%1' ;").arg(number) );
	db.close();
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid contact ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
#endif //CONTACT_H

#ifndef PERSON_H
#define PERSON_H
class Person: public QObject {
	Q_OBJECT
private:
	QString id, name;
	Email email = Email(this);
	CNIC cnic = CNIC(this);
	Contact contact = Contact(this);
	Address permanent_addr = Address(this);
	Address temprary_addr = Address(this);

public:
	inline Person(QObject* parent = 0) : QObject(parent) {};
	inline ~Person () {}
	QString& getId();
	QString& getName();
	CNIC& getCNIC();
	Contact& getContact();
	Email& getEmail();

	QString insert ( QString& name,
									 QString& email,
									 QString& cnic,
									 QString& contact,
									 Address& p_addr,
									 Address& t_addr
									 );
	QString update(QString email);
	void copy(Person& p);

};
inline QString& Person::getId() { return this->id; }
inline QString& Person::getName() { return this->name; }
inline CNIC& Person::getCNIC() { return this->cnic; }
inline Contact& Person::getContact() { return this->contact; }
inline Email& Person::getEmail() { return this->email; }
inline void Person::copy(Person &p) {
	this->id = p.id;
	this->name = p.name;
	this->email.copy(p.email);
	this->cnic.copy(p.cnic);
	this->contact.copy(p.contact);
}

inline QString Person::insert(QString& name, QString& email, QString& cnic, QString& contact, Address& p_addr, Address& t_addr) {
	QString err = "" ;
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);

	q.exec("BEGIN;");

// email insertion
	q.exec( QString("INSERT INTO EMAILS (name) VALUES ('%1') RETURNING id;").arg(email) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 db.close();
		 return err;
	}
	QString eid = "";
	while (q.next()) {
		eid = q.value(0).toString();
	}
	qCritical () << eid;
// cnic insertion
	q.exec( QString("INSERT INTO CNICS (name) VALUES ('%1') RETURNING id;").arg(cnic) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 db.close();
		 return err;
	}
	QString cid = "";
	while (q.next()) {
		cid = q.value(0).toString();
	}
	qCritical () << cid;
// contact insertion
	q.exec( QString("INSERT INTO CONTACTS (name) VALUES ('%1') RETURNING id;").arg(contact) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 db.close();
		 return err;
	}
	QString pid = "";
	while (q.next()) {
		pid = q.value(0).toString();
	}
	qCritical() << pid;

	q.exec("COMMIT;");
	db.close();

	this->permanent_addr.copy(p_addr);
	this->temprary_addr.copy(t_addr);

	return err;
}

inline QString Person::update(QString email) {
	return this->email.update(email);
}
#endif //PERSON_H
