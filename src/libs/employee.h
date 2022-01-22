#include "person.h"
#include "image.h"
#ifndef ORGANIZATION_H
#define ORGANIZATION_H
class Organization {
	Q_GADGET
	Q_PROPERTY( QString id READ getId)
	Q_PROPERTY( QString name READ getName)
	Q_PROPERTY( QString gov_reg_num READ getGovRegNum)
	Q_PROPERTY( Contact contact READ getContact)
	Q_PROPERTY( Address address READ getAddress)
	Q_PROPERTY( Email email READ getEmail)
	Q_PROPERTY( Image logo READ getLogo)
private:
	QString id, name, gov_reg_num;
	Image logo;
	Email email;
	Address address;
	Contact contact;

public:
	inline Organization () {};
	inline ~Organization () {};

	QString getById(QString& id);
	QString getByEmail(QString& email);

	QString& getId();
	QString& getName();
	QString& getGovRegNum();
	Contact& getContact();
	Address& getAddress();
	Email& getEmail();
	Image& getLogo();

	QString insert(const QString& id, const QString& name, const QString& email_id, const QString& contact_id, const QString& reg_num, Address addr, const QString& pathToLocalFile );
	QString insert( const QString& id, const QString& name, const QString& email_id, const QString& contact_id, const QString& reg_num, Address addr, const QUrl& urlToLocalFile );

};

inline QString& Organization::getId() { return this->id; }
inline QString& Organization::getName() { return this->name; }
inline QString& Organization::getGovRegNum() { return this->gov_reg_num; }
inline Contact& Organization::getContact() { return this->contact; }
inline Address& Organization::getAddress() { return this->address; }
inline Email& Organization::getEmail() { return this->email; }
inline Image& Organization::getLogo() { return this->logo; }
inline QString Organization::insert(const QString &id, const QString &name, const QString &email_id, const QString &contact_id, const QString &reg_num, Address addr, const QUrl &urlToLocalFile) {
	return this->insert(id,name,email_id,contact_id,reg_num,addr,urlToLocalFile.toLocalFile());
}
inline QString Organization::insert(const QString &id, const QString &name, const QString &email_id, const QString &contact_id, const QString &reg_num, Address addr, const QString &pathToLocalFile) {
	QSqlDatabase db = Database::getDB();

}

Q_DECLARE_METATYPE(Organization)

#endif //ORGANIZATION_H

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#endif // EMPLOYEE_H

