#pragma once
#include "address.h"

#ifndef EMAIL_H
#define EMAIL_H
class Email {
private:
	QString id, text;
public:
	inline Email () {}
	inline ~Email () {}
	QString getId() const;
	QString getText() const;
	QString update( QString& email);
	QString updateById(QString& id);
	void copy(Email& e);
	void setText(const QString &newText);
};
inline QString Email::getId() const { return this->id; }
inline QString Email::getText() const { return this->text; }
inline void Email::setText(const QString &newText) {
	if (this->text == newText) return;
	this->text = newText;
}
inline void Email::copy(Email &e) { this->id = e.id; this->text = e.text; }
inline QString Email::update(QString& email) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM EMAILS WHERE name = '%1' ;").arg(email) );
	if (!q.lastError().text().isEmpty() ) return "invalid email ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
inline QString Email::updateById(QString& id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM EMAILS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}
#endif //EMAIL_H

#ifndef CNIC_H
#define CNIC_H
class CNIC {
	Q_GADGET
	Q_PROPERTY(QString text READ getText WRITE setText)
private:
	QString id, text;
public:
	inline CNIC () {}
	inline ~CNIC () {}
	QString& getId();
	QString& getText();
	QString update(QString & number);
	QString updateById(QString& id);
	void copy(CNIC& e);
	void setText(const QString &newText);
};
inline void CNIC::setText(const QString &newText) {
	if (this->text == newText) return;
	this->text = newText;
}
inline QString& CNIC::getId() { return this->id; }
inline QString& CNIC::getText() { return this->text; }
inline void CNIC::copy(CNIC &e) { this->id = e.id; this->text = e.text; }
inline QString CNIC::update(QString& number) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM CNICS WHERE name = '%1' ;").arg(number) );
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid cnic ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
inline QString CNIC::updateById(QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM CNICS WHERE id = '%1'").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}
#endif //CNIC_H

#ifndef CONTACT_H
#define CONTACT_H
class Contact {
private:
	QString id, text;
public:
	inline Contact () {}
	inline ~Contact () {}
	QString& getId();
	QString& getText();
	QString update(QString& contact);
	QString updateById(QString& id);
	void copy(Contact& e);
	void setText(const QString &newText);
};
inline QString& Contact::getId() { return this->id; }
inline QString& Contact::getText() { return this->text; }
inline void Contact::setText(const QString &newText) {
	if (this->text == newText) return;
	this->text = newText;
}
inline void Contact::copy(Contact &e) { this->id = e.id; this->text = e.text; }
inline QString Contact::update(QString& number) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM CONTACTS WHERE name = '%1' ;").arg(number) );
	if (!q.isValid() || !q.lastError().text().isEmpty() ) return "invalid contact ";
	while (q.next()) {
		this->id = q.value(0).toString();
		this->text = q.value(1).toString();
	}
	return q.lastError().text();
}
inline QString Contact::updateById(QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM CONTACTS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while(q.next()) {
		this->text = q.value(0).toString();
	}
	return "";
}
#endif //CONTACT_H

#ifndef PERSON_H
#define PERSON_H
class Person {
Q_GADGET
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
	Q_INVOKABLE QString& getId();
	Q_INVOKABLE QString& getName();
	Q_INVOKABLE CNIC& getCNIC();
	Q_INVOKABLE Contact& getContact();
	Q_INVOKABLE Email& getEmail();

	QString insert ( QString& name,
									 QString& email,
									 QString& cnic,
									 QString& contact,
									 Address& p_addr,
									 Address& t_addr
									 );
	QString updateByEmail(QString email);
	QString updateById(QString id);
	void copy(Person& p);

	void setName(const QString &newName);
	void setCNIC( CNIC &newCnic);
	void setEmail( Email &newEmail);
	void setContact( Contact &newContact);
	Address &getPermanentAddr() ;
	void setPermanent_addr( Address &newPermanent_addr);
	Address &getTempraryAddr() ;
	void setTemprary_addr( Address &newTemprary_addr);

};
inline Address& Person::getTempraryAddr() { return this->temprary_addr;}
inline void Person::setTemprary_addr(Address &newTemprary_addr) {
	if (newTemprary_addr.getId().isEmpty()) return;
	if (this->temprary_addr.getId() == newTemprary_addr.getId()) return;
	this->temprary_addr.copy(newTemprary_addr);
}
inline Address& Person::getPermanentAddr() { return this->permanent_addr;}
inline void Person::setPermanent_addr(Address &newPermanent_addr) {
	if (newPermanent_addr.getId().isEmpty()) return;
	if (this->permanent_addr.getId() == newPermanent_addr.getId()) return;
	this->permanent_addr.copy(newPermanent_addr);
}
inline QString& Person::getId() { return this->id; }
inline QString& Person::getName() { return this->name; }
inline void Person::setName(const QString &newName) {
	if (this->name == newName) return;
	this->name = newName;
}
inline void Person::setCNIC( CNIC &newCnic) {
	if (newCnic.getId().isEmpty() || newCnic.getText().isEmpty()) return;
	if (this->cnic.getText() == newCnic.getText() ) return;
	this->cnic.copy(newCnic);
}
inline CNIC& Person::getCNIC() { return this->cnic; }
inline Contact& Person::getContact() { return this->contact; }
inline void Person::setContact(Contact &newContact) {
	if (newContact.getId().isEmpty() || newContact.getText().isEmpty()) return;
	if (this->contact.getText() == newContact.getText()) return;
	this->contact.copy(newContact);
}
inline Email& Person::getEmail() { return this->email; }
inline void Person::setEmail(Email &newEmail) {
	if (newEmail.getId().isEmpty() || newEmail.getText().isEmpty()) return;
	if(this->email.getText() == newEmail.getText()) return;
	this->email.copy(newEmail);
}
inline void Person::copy(Person &p) {
	this->id = p.id;
	this->name = p.name;
	this->email.copy(p.email);
	this->cnic.copy(p.cnic);
	this->contact.copy(p.contact);
}
inline QString Person::updateById(QString id) {
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
inline QString Person::updateByEmail(QString email) {
	Email e;
	e.update(email);
	if (e.getId().isEmpty()) qCritical() << "Update person email id is empty";
	QString err = "", cid = "", pid = "", eid = "", t_l = "", p_l = "" ;
	QSqlQuery q = Database::rawQuery( QString("SELECT * FROM PERSONS WHERE email_id = '%1' ;").arg(e.getId()) );
	if (!q.isValid()) qCritical() << "update persone by email query is not valid" ;
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
		QString& name,
		QString& email,
		QString& cnic,
		QString& contact,
		Address& p_addr,
		Address& t_addr
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
		 db.close();
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
		 db.close();
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
		 db.close();
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
		db.close();
		return err;
	}
	while (q.next()) {
		this->id = q.value(0).toString();
	}
	q.exec("COMMIT;");
	db.close();
// ----------------------------------------------
	return err;
}

#endif //PERSON_H
