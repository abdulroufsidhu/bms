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

	QString getById( const QString& id) ;
	QString getByEmail( const QString& email) ;

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

inline QString Organization::getById(const QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name, email_id, contact_id, location_id, gov_reg_num FROM ORGANIZATIONS WHERE id = '%1';").arg(id) );
	if (q.lastError().text().length()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->email.updateById(q.value("email_id").toString());
		this->contact.updateById(q.value("contact_id").toString());
		this->address.updateById(q.value("location_id").toString());
		this->name = q.value("name").toString();
		this->gov_reg_num = q.value("gov_reg_num").toString();
	}
	return "";
}
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
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		eid = q.value(0).toString();
	}
	qCritical() << " :inserting contact";
	if (!q.exec( QString("INSERT INTO CONTACTS (name) VALUES (%1) RETURNING id;").arg(contact) ) || q.lastError().text().length()) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while(q.next()) {
		pid = q.value(0).toString();
	}
	qCritical() << "inserting organization details";
	if (!q.exec( QString("INSERT INTO ORGANIZATIONS (name, email_id, contact_id, gov_reg_num, location_id) VALUES ('%1','%2','%3','%4','%5') RETURNING id ; " ).arg(name, eid, pid, reg_num, addr.getId() ) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		id = q.value("id").toString();
	}
	qCritical() << "inserting main branch";
	if (!q.exec( QString("INSERT INTO BRANCHES (name, code, email_id, contact_id, organization_id, location_id) VALUES ('main','B-786','%1','%2','%3', '%4') RETURNING id; ").arg(eid,pid,id,addr.getId()) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
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
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		jid = q.value(0).toString();
	}
	qCritical() << "inserting employee";
	if (!q.exec( QString("INSERT INTO EMPLOYEES ( user_id, branch_id, job_id, currency_id) SELECT '%1','%2','%3', id FROM CURRENCY WHERE name = 'Pakistani Rupees'; ").arg(user_id,bid,jid) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	qCritical() << "ending transaction";
	if (!q.exec("COMMIT;") || q.lastError().text().length()) {
		q.exec("ROLLBACK;");
		// db.close();
		return q.lastError().text();
	}
	qCritical() << "organization insertion performed new id :-> " << id ;
	qCritical() << "uploading image";
	Image i;
	if (!i.uploadImage(pathToLocalFile,id)) qCritical () << "image uploading failed";
	else qCritical() << "image upload successfull";

	return "";
}

#endif // ORGANIZATION_H

#ifndef BRANCH_H
#define BRANCH_H
struct Branch {
private:
	QString id, name, code;
	Contact contact;
	Address address;
	Email email;
	Image image;
	Organization organization;

public:
	inline Branch() {};
	inline Branch(QString id, QString name, QString code, Contact contact, Address addr, Email email, Organization organization ) {
		this->id = id;
		this->name = name;
		this->code = code;
		this->contact.copy(contact);
		this->address.copy(addr);
		this->email.copy(email);
		this->organization = organization;
	}
	inline const QString& getId() const { return this->id; }
	inline const QString& getName() const { return this->name; }
	inline const QString& getCode() const { return this->code; }
	inline const Contact& getContact() const { return this->contact; }
	inline const Address& getAddress() const { return this->address; }
	inline const Email& getEmail() const { return this->email; }
	inline const Image& getImage() const { return this->image; }
	inline const Organization& getOrg() const { return this->organization; }

	QString getById(const QString& id) ;
	QString getByEmail(const QString& email);

	QString insert(const Organization& org, const QString& name, const QString& code, const QString& email, const QString& contact, const Address& address, const QUrl& urlToLocalFile);
		QString insert(const Organization& org, const QString& name, const QString& code, const QString& email, const QString& contact, const Address& address, const QString& pathToLocalFile);

};

inline QString Branch::insert(const Organization& org, const QString &name, const QString &code, const QString &email, const QString &contact, const Address &address, const QUrl &urlToLocalFile) {
	return this->insert(org,name,code,email,contact,address,urlToLocalFile.toLocalFile());
}
inline QString Branch::insert(const Organization& org, const QString &name, const QString &code, const QString &email, const QString &contact, const Address &address, const QString &pathToLocalFile) {
	QString id, pid, eid;
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	if (!q.exec("BEGIN;") || q.lastError().text().length()) {
		// // db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	qCritical() << "Starting transaction to register branch";
	qCritical() << "inserting contact";
	if (!q.exec(QString("INSERT INTO CONTACTS (name) VALUES ('%1') RETURNING id;").arg(contact) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while(q.next()) {
		pid = q.value("id").toString();
	}
	qCritical() << "inserting email";
	if (!q.exec( QString("INSERT INTO EMAILS (name) VALUES ('%1') RETURNING id;").arg(email) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		eid = q.value("id").toString();
	}

	qCritical() << "inserting branch";
	if (!q.exec( QString("INSERT INTO BRANCHES(name, code, email_id, contact_id, organization_id, location_id ) VALUES ( '%1','%2','%3','%4','%5','%6' ) RETURNING id ; ").arg(name,code,eid,pid,org.getId(),address.getId()) ) || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	while (q.next()) {
		id = q.value("id").toString();
	}
	if (!q.exec("COMMIT;") || q.lastError().text().length() ) {
		q.exec("ROLLBACK;");
		// db.close();
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	// db.close();
	this->image.uploadImage(pathToLocalFile,id);
	qCritical() << "operation successfully completed";

	return "";
}


#endif // BRANCH_H

#ifndef JOB_H
#define JOB_H

struct Job {
private:
	QString id, name;
public:
	Job() {}
	Job(QString id, QString name) : id(id), name(name) {}

	const QString& getId() const { return this->id; }
	const QString& getName() const { return this->name; }

	static QString upload(const QString& name);
	QString getByName(const QString& name);
	QString getById(const QString& id);

};
inline QString Job::upload(const QString &name) {
	QSqlQuery q = Database::rawQuery( QString("INSERT INTO JOBS (name) VALUES ('%1');").arg(name) );
	if (q.lastError().text().length()) {
		qCritical() << q.lastError().text();
		return q.lastError().text();
	}
	return "";
}
inline QString Job::getById(const QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM JOBS WHERE id = '%1'; ").arg(id) );
	if (q.lastError().text().length() || q.size() < 1) {
		qCritical() <<"unable to retrieve job data" + q.lastError().text();
		return "unable to retrieve job data: " + q.lastError().text();
	}
	this->id = id;
	while (q.next()) {
		this->name = q.value("name").toString();
	}
	return "";
}
inline QString Job::getByName(const QString &name) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id FROM JOBS WHERE name = '%1'").arg(name) );
	if (q.lastError().text().length()) return q.lastError().text();
	if (q.size()<1) return "no data found";
	this->name = name;
	while (q.next()) {
		this->id = q.value("id").toString();
	}
	return "";
}

#endif // JOB_H

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

struct Employee {
private:
	QString id, salary, currency, curr_symbol;
	Job job;
	Branch branch;
public:
	inline const Job& getJob() const { return this->job; }
	inline const QString& getId() const { return this->id; }
	inline const Branch& getBranch() const { return this->branch; }
	inline const QString& getSalary() const { return this->salary; }
	inline const QString& getCurrency() const { return this->currency; }
	inline const QString& getCurrSymbol() const { return this->curr_symbol; }

	QString getByEmail ( const QString& email ) ;
	QString getByBranchId( const QString& bid) ;
	QString getByOrgId( const QString& oid ) ;
	QString getById( const QString& id ) ;

};

inline QString Employee::getById(const QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT * FROM EMPLOYEES WHERE id = '%1'").arg(id) );
	if (q.lastError().text().length()) return q.lastError().text();
	if (q.size()<1) return "no data found";
	while (q.next()) {
		this->id = q.value("id").toString();
		this->salary = q.value("salary").toString();
		this->branch.getById( q.value("branch_id").toString());
		this->job.getById(q.value("job_id").toString());
	}
	return "";
}


#endif

