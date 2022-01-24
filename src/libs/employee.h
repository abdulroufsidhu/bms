#pragma once
#include "person.h"
#include "image.h"
#ifndef ORGANIZATION_H
#define ORGANIZATION_H
struct Organization {
//	Q_GADGET
//	Q_PROPERTY( QString id READ getId)
//	Q_PROPERTY( QString name READ getName)
//	Q_PROPERTY( QString gov_reg_num READ getGovRegNum)
//	Q_PROPERTY( Contact contact READ getContact)
//	Q_PROPERTY( Address address READ getAddress)
//	Q_PROPERTY( Email email READ getEmail)
//	Q_PROPERTY( Image logo READ getLogo)
private:
	QString id, name, gov_reg_num;
	Image logo;
	Email email;
	Address address;
	Contact contact;

public:
	inline Organization () {};
	inline Organization (QString id,QString name,QString reg_num,Contact contact,Email email,Address address) {
		this->id = id;
		this->name = name;
		this->gov_reg_num = reg_num;
		this->contact.copy(contact);
		this->email.copy(email);
		this->address.copy(address);
	}
	inline ~Organization () {};

	QString getById(QString& id);
	QString getByEmail(QString& email);

	const QString& getId() const ;
	const QString& getName() const ;
	const QString& getGovRegNum() const ;
	const Contact& getContact() const ;
	const Address& getAddress() const ;
	const Email& getEmail() const ;
	const Image& getLogo() const ;

	static QString insert(const QString &user_id, const QString& name, const QString& email, const QString& contact, const QString& reg_num, Address addr, const QString& pathToLocalFile );
	static QString insert(const QString &user_id, const QString& name, const QString& email, const QString& contact, const QString& reg_num, Address addr, const QUrl& urlToLocalFile );

};

inline const QString& Organization::getId() const { return this->id; }
inline const QString& Organization::getName() const { return this->name; }
inline const QString& Organization::getGovRegNum() const { return this->gov_reg_num; }
inline const Contact& Organization::getContact() const { return this->contact; }
inline const Address& Organization::getAddress() const { return this->address; }
inline const Email& Organization::getEmail() const { return this->email; }
inline const Image& Organization::getLogo() const { return this->logo; }
inline QString Organization::insert(const QString &user_id, const QString &name, const QString &email_id, const QString &contact_id, const QString &reg_num, Address addr, const QUrl &urlToLocalFile) {
	return Organization::insert(user_id,name,email_id,contact_id,reg_num,addr,urlToLocalFile.toLocalFile());
}
inline QString Organization::insert(const QString &user_id, const QString &name, const QString &email, const QString &contact, const QString &reg_num, Address addr, const QString &pathToLocalFile) {
	QString id,eid,pid,jid,bid;
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	qCritical() << "starting transaction";
	if (!q.exec("BEGIN;") || q.lastError().text().length()) return q.lastError().text();
	qCritical() << "inserting email";
	if (!q.exec( QString("INSERT INTO EMAILS (name) VALUES ('%1') RETURNING id;").arg(email))  || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		eid = q.value(0).toString();
	}
	qCritical() << " :inserting contact";
	if (!q.exec( QString("INSERT INTO CONTACTS (name) VALUES (%1) RETURNING id;").arg(contact) ) || q.lastError().text().length()) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while(q.next()) {
		pid = q.value(0).toString();
	}
	qCritical() << "inserting organization details";
	if (!q.exec( QString("INSERT INTO ORGANIZATIONS (name, email_id, contact_id, gov_reg_num, location_id) VALUES ('%1','%2','%3','%4','%5') RETURNING id ; " ).arg(name, eid, pid, reg_num, addr.getId() ) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		id = q.value("id").toString();
	}
	qCritical() << "inserting main branch";
	if (!q.exec( QString("INSERT INTO BRANCHES (name, code, email_id, contact_id, organization_id) VALUES ('main','B-786','%1','%2','%3') RETURNING id; ").arg(eid,pid,id) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		bid = q.value(0).toString();
	}
	qCritical() << "inserting job";
	q.exec( "INSERT INTO JOBS(name) SELECT 'OWNER' WHERE NOT EXISTS (SELECT name FROM JOBS WHERE name = 'OWNER') ;" );
	if (!q.exec( QString("SELECT id FROM JOBS WHERE name = 'OWNER';") ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		jid = q.value(0).toString();
	}
	qCritical() << "inserting employee";
	if (!q.exec( QString("INSERT INTO EMPLOYEES ( user_id, branch_id, job_id, currency_id) SELECT '%1','%2','%3', id FROM CURRENCY WHERE name = 'Pakistani Rupees'; ").arg(user_id,bid,jid) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	qCritical() << "ending transaction";
	if (!q.exec("COMMIT;") || q.lastError().text().length()) {
		q.exec("ROLLBACK;");
		db.close();
		return q.lastError().text();
	}
	qCritical() << "organization insertion performed new id :-> " << id ;
	qCritical() << "uploading image";
	Image i;
	if (!i.uploadImage(pathToLocalFile,id)) qCritical () << "image uploading failed";
	else qCritical() << "image upload successfull";

	return "";
}

Q_DECLARE_METATYPE(Organization)

#endif //ORGANIZATION_H

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#endif // EMPLOYEE_H

