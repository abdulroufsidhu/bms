#pragma once
#include "address.h"
#include <QMetaType>
#include <QMetaObject>

#ifndef EMAIL_H
#define EMAIL_H
struct Email {
	Q_GADGET
	Q_PROPERTY(QString text READ getText )
private:
	QString id, text;
public:
	inline Email () {}
	inline ~Email () {}
	const QString& getId() const;
	const QString& getText() const;
	QString update(const QString& email) ;
	QString updateById(const QString& id)  ;
	void copy(Email& e);
};
inline const QString& Email::getId() const { return this->id; }
inline const QString& Email::getText() const { return this->text; }
inline void Email::copy(Email &e) { this->id = e.id; this->text = e.text; }
inline QString Email::update(const QString& email) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM EMAILS WHERE name = '%1' ;").arg(email) );
	if (!q.lastError().text().isEmpty() ) return "invalid email ";
	while (q.next()) {
		this->id = q.value("id").toString();
		this->text = q.value("name").toString();
	}
	return q.lastError().text();
}
inline QString Email::updateById(const QString& id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM EMAILS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}

Q_DECLARE_METATYPE(Email);
#endif //EMAIL_H

#ifndef CNIC_H
#define CNIC_H
struct CNIC {
	Q_GADGET
	Q_PROPERTY(QString text READ getText)
private:
	QString id, text;
public:
	inline CNIC () {}
	inline ~CNIC () {}
	const QString& getId()const ;
	const QString& getText()const ;
	QString update(const QString & number);
	QString updateById(const QString& id);
	void copy(CNIC& e);
};
inline const QString& CNIC::getId()const  { return this->id; }
inline const QString& CNIC::getText()const  { return this->text; }
inline void CNIC::copy(CNIC &e) { this->id = e.id; this->text = e.text; }
inline QString CNIC::update(const QString& number) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM CNICS WHERE name = '%1' ;").arg(number) );
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid cnic ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
inline QString CNIC::updateById(const QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM CNICS WHERE id = '%1'").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}

Q_DECLARE_METATYPE(CNIC);
#endif //CNIC_H

#ifndef CONTACT_H
#define CONTACT_H
struct Contact {
	Q_GADGET
	Q_PROPERTY(QString text READ getText)
private:
	QString id, text;
public:
	inline Contact () {}
	inline ~Contact () {}
	const QString& getId()const ;
	const QString& getText()const ;
	QString update(const QString& contact);
	QString updateById(const QString& id);
	void copy(Contact& e);
};
inline const QString& Contact::getId()const  { return this->id; }
inline const QString& Contact::getText()const  { return this->text; }
inline void Contact::copy(Contact &e) { this->id = e.id; this->text = e.text; }
inline QString Contact::update(const QString& number) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM CONTACTS WHERE name = '%1' ;").arg(number) );
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid contact ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
inline QString Contact::updateById(const QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM CONTACTS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while(q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}

Q_DECLARE_METATYPE(Contact);
#endif //CONTACT_H

#ifndef PERSON_H
#define PERSON_H
struct Person {
Q_GADGET
Q_PROPERTY(QString id READ getId)
Q_PROPERTY(QString name READ getName)
Q_PROPERTY(Email email READ getEmail)
Q_PROPERTY(CNIC cnic READ getCNIC)
Q_PROPERTY(Contact contact READ getContact)
Q_PROPERTY(Address permanent_addr READ getPermanentAddr)
Q_PROPERTY(Address temprary_addr READ getTempraryAddr)
private:
	QString id, name;
	Email email = Email();
	CNIC cnic = CNIC();
	Contact contact = Contact();
	Address permanent_addr = Address();
	Address temprary_addr = Address();

public:
	inline Person() {};
	inline ~Person () {}
	const QString& getId()const ;
	const QString& getName()const ;
	const CNIC& getCNIC()const ;
	const Contact& getContact()const ;
	const Email& getEmail()const ;
	const Address &getPermanentAddr()const  ;
	const Address &getTempraryAddr()const  ;

	QString insert (const  QString& name,
									const  QString& email,
									const  QString& cnic,
									const  QString& contact,
									const  Address& p_addr,
									const  Address& t_addr
									 );
	QString updateByEmail(const QString& email);
	QString updateById(const QString& id);
	void copy(Person& p);

};

inline const Address& Person::getTempraryAddr()const  { return this->temprary_addr;}
inline const Address& Person::getPermanentAddr()const  { return this->permanent_addr;}
inline const QString& Person::getId()const  { return this->id; }
inline const QString& Person::getName()const  { return this->name; }
inline const CNIC& Person::getCNIC()const  { return this->cnic; }
inline const Contact& Person::getContact()const  { return this->contact; }
inline const Email& Person::getEmail()const  { return this->email; }
inline void Person::copy(Person &p) {
	this->id = p.id;
	this->name = p.name;
	this->email.copy(p.email);
	this->cnic.copy(p.cnic);
	this->contact.copy(p.contact);
}
inline QString Person::updateById(const QString& id) {
	QString err = "";
	QString cid = "", pid = "", eid = "", t_l = "", p_l = "";
	QSqlQuery q = Database::rawQuery( QString("SELECT * FROM PERSONS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value("id").toString();
		this->name = q.value("name").toString();
		cid = q.value("cnic_id").toString();
		pid = q.value("contact_id").toString();
		eid = q.value("email_id").toString();
		t_l = q.value("temp_residence_id").toString();
		p_l = q.value("parm_residence_id").toString();
	}
	err = this->contact.updateById(pid);
	if (err.length()) return err;
	err = this->cnic.updateById(cid);
	if (err.length()) return err;
	err = this->email.updateById(eid);
	if (err.length()) return err;
	err = this->temprary_addr.updateById(t_l);
	if (err.length()) return err;
	err = this->permanent_addr.updateById(p_l);
	return err;
}
inline QString Person::updateByEmail(const QString& email) {
	Email e;
	e.update(email);
	if (e.getId().isEmpty()) qCritical() << "Update person email id is empty";
	QString err = "", cid = "", pid = "", eid = "", t_l = "", p_l = "" ;
	QSqlQuery q = Database::rawQuery( QString("SELECT * FROM PERSONS WHERE email_id = '%1' ;").arg(e.getId()) );
	if (!q.isValid()) qCritical() << "update person by email query is not valid" ;
	if (q.lastError().text().length()) return q.lastError().text();
	if (q.size() < 1) return "No record found for person having this email";
	while (q.next()) {
		this->id = q.value("id").toString();
		this->name = q.value("name").toString();
		cid = q.value("cnic_id").toString();
		pid = q.value("contact_id").toString();
		eid = q.value("email_id").toString();
		t_l = q.value("temp_residence_id").toString();
		p_l = q.value("parm_residence_id").toString();
	}
	err = this->contact.updateById(pid);
	if (err.length()) return err;
	err = this->cnic.updateById(cid);
	if (err.length()) return err;
	err = this->email.updateById(eid);
	if (err.length()) return err;
	err = this->temprary_addr.updateById(t_l);
	if (err.length()) return err;
	err = this->permanent_addr.updateById(p_l);
	return err;
}
inline QString Person::insert(
		const QString& name,
		const QString& email,
		const QString& cnic,
		const QString& contact,
		const Address& p_addr,
		const Address& t_addr
		) {
// data checks
	if (name.isEmpty()) return "Please enter a name";
	if (name.length() < 5) return "Please enter original full name";
	if (email.isEmpty()) return "Please enter email";
	if (!email.contains('@') || !email.contains('.')) return "please enter a valid email address";
	if (cnic.isEmpty()) return "Please enter your national identity number";
	if (!cnic.toULongLong()) return "Please enter numbers only for national identity";
	if (contact.isEmpty()) return "Please enter your contact";
	if (!contact.toULongLong()) return "Please enter numbers only for cotact";

// ----------------------------------------------

	QString err = "" ;
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);

	q.exec("BEGIN;");

// email insertion
	q.exec( QString("INSERT INTO EMAILS (name) VALUES ('%1') RETURNING id;").arg(email) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 // db.close();
		 return err;
	}
	QString eid = "";
	while (q.next()) {
		eid = q.value(0).toString();
	}
// ----------------------------------------------
// cnic insertion
	q.exec( QString("INSERT INTO CNICS (name) VALUES ('%1') RETURNING id;").arg(cnic) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 // db.close();
		 return err;
	}
	QString cid = "";
	while (q.next()) {
		cid = q.value(0).toString();
	}
// ----------------------------------------------
// contact insertion
	q.exec( QString("INSERT INTO CONTACTS (name) VALUES ('%1') RETURNING id;").arg(contact) );
	if (!q.lastError().text().isEmpty()) {
		 err = q.lastError().text();
		 q.exec("ROLLBACK;");
		 // db.close();
		 return err;
	}
	QString pid = "";
	while (q.next()) {
		pid = q.value(0).toString();
	}
// ----------------------------------------------
// person insertion
	q.exec( QString("INSERT INTO PERSONS (name, email_id, contact_id, cnic_id, temp_residence_id,parm_residence_id) VALUES ( '%1','%2','%3','%4','%5','%6') returning id;").arg(name,eid,pid,cid,t_addr.getId(),p_addr.getId() ) );
	if (!q.lastError().text().isEmpty()) {
		err = q.lastError().text();
		q.exec("ROLLBACK;");
		// db.close();
		return err;
	}
	while (q.next()) {
		this->id = q.value(0).toString();
	}
	q.exec("COMMIT;");
	// db.close();
// ----------------------------------------------
	return err;
}

Q_DECLARE_METATYPE(Person);

#endif //PERSON_H
