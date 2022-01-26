#include "../libs/user.h"
#include <QSqlQueryModel>
#include <QHash>

#ifndef ORGANIZATION_LIST_H
#define ORGANIZATION_LIST_H
class OrganizationListModel : public QSqlQueryModel {
	Q_OBJECT
	QThread orgListThread;
public:
	inline explicit OrganizationListModel(QObject *parent = nullptr) : QSqlQueryModel (parent) {
		orgListThread.start();
		roleNames();
		this->refresh();
	}
	inline ~OrganizationListModel() {orgListThread.quit(); orgListThread.wait();}
	QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
	QHash<int, QByteArray> roleNames() const override;
public slots:
	void refresh();
private: //members
	inline static const char* COLUMN_NAMES[] = { "id", "name", "email", "contact", "gov_reg_num", "country", "city", "address" };
	inline static QString SQL_SELECT = QString( " \
SELECT \
		o.id as id, o.name as name, email.name as email, contact.name as contact, \
		o.gov_reg_num as gov_reg_num, c.name as country, city.name as city, l.name as address \
FROM \
		organizations o, branches b, contacts contact, emails email, locations l, \
		cities city, countries c, employees e \
WHERE \
		e.user_id = '%1' \
		AND b.id = e.branch_id \
		AND contact.id = o.contact_id \
		AND email.id = o.email_id\
		AND o.id = b.organization_id AND \
		l.id = o.location_id \
		AND city.id = l.city_id \
		AND c.id = city.country_id \
		; ").arg(User::getCurrentUser()->getId()) ;

};

inline QHash<int, QByteArray> OrganizationListModel::roleNames()const {
	int idx = 0;
	QHash<int, QByteArray> hash;
	while( COLUMN_NAMES[idx]) {
		 hash[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
		 idx++;
	}
	return hash;
}
inline QVariant OrganizationListModel::data(const QModelIndex &index, int role)const {
	QVariant value = QSqlQueryModel::data(index, role);
	if(!index.isValid())
	{
		return QVariant();
	}
	if ( role < Qt::UserRole ) {
		value = QSqlQueryModel::data(index, role);
	}
	else
	{
		int columnIdx = role - Qt::UserRole - 1;
		QModelIndex modelIndex = this->index(index.row(), columnIdx);
		value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
		qCritical() << Qt::DisplayRole ;
	}
	qCritical() << index << ":-:" << role << ":-:" << value;
	return value;
}
inline void OrganizationListModel::refresh() {
	SQL_SELECT = QString( "SELECT o.id as id, o.name as name, email.name as email, contact.name as contact,  o.gov_reg_num as gov_reg_num, c.name as country, city.name as city, l.name as address  FROM  organizations o, branches b, contacts contact, emails email, locations l,  cities city, countries c, employees e  WHERE  e.user_id = '%1'  AND b.id = e.branch_id  AND contact.id = o.contact_id  AND email.id = o.email_id AND o.id = b.organization_id AND  l.id = o.location_id  AND city.id = l.city_id  AND c.id = city.country_id  ; ").arg(User::getCurrentUser()->getId()) ;

	this->roleNames();
	this->setQuery(SQL_SELECT,Database::getDB());
}

#endif // LIST_MODELS_H

#ifndef BRANCH_LIST_H
#define BRANCH_LIST_H
class BranchListModel : public QSqlQueryModel {
	Q_OBJECT
	QThread branchListThread;
public:
	inline explicit BranchListModel(QObject *parent = nullptr) : QSqlQueryModel (parent) {
		branchListThread.start();
	}
	inline ~BranchListModel() {branchListThread.quit(); branchListThread.wait();}
	QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
	QHash<int, QByteArray> roleNames() const override;
public slots:
	QString refresh( const QString& id );
private: //members
	inline static const char* COLUMN_NAMES[] = { "id", "name", "email", "contact", "organization" };
	inline static QString SQL_SELECT = QString( "SELECT \
b.id as id, b.name as name,  email.name as email, c.name as contact, o.name as organization \
FROM \
		EMPLOYEES emp \
LEFT JOIN BRANCHES b ON emp.branch_id = b.id \
LEFT JOIN ORGANIZATIONS o ON b.organization_id = o.id \
LEFT JOIN CONTACTS c ON b.contact_id = c.id \
LEFT JOIN EMAILS email ON b.email_id = email.id \
WHERE \
		emp.user_id = '%1' \
		AND b.organization_id = '%2' \
		; ").arg(User::getCurrentUser()->getId(), "") ;

};

inline QHash<int, QByteArray> BranchListModel::roleNames()const {
	int idx = 0;
	QHash<int, QByteArray> hash;
	while( COLUMN_NAMES[idx]) {
		 hash[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
		 idx++;
	}
	return hash;
}
inline QVariant BranchListModel::data(const QModelIndex &index, int role)const {
	QVariant value = QSqlQueryModel::data(index, role);
	if(!index.isValid())
	{
		return QVariant();
	}
	if ( role < Qt::UserRole ) {
		value = QSqlQueryModel::data(index, role);
	}
	else
	{
		int columnIdx = role - Qt::UserRole - 1;
		QModelIndex modelIndex = this->index(index.row(), columnIdx);
		value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
		qCritical() << Qt::DisplayRole ;
	}
	qCritical() << index << ":-:" << role << ":-:" << value;
	return value;
}
inline QString BranchListModel::refresh( const QString& oid ) {
	SQL_SELECT = QString( "SELECT \
	b.id as id, b.name as name, email.name as email, c.name as contact, o.name as organization \
	FROM \
			EMPLOYEES emp \
	LEFT JOIN BRANCHES b ON emp.branch_id = b.id \
	LEFT JOIN ORGANIZATIONS o ON b.organization_id = o.id \
	LEFT JOIN CONTACTS c ON b.contact_id = c.id \
	LEFT JOIN EMAILS email ON b.email_id = email.id \
	WHERE \
			emp.user_id = '%1' \
			AND b.organization_id = '%2' \
			; ").arg(User::getCurrentUser()->getId(), oid) ;
	this->roleNames();
	this->setQuery(SQL_SELECT,Database::getDB());
	qCritical() << SQL_SELECT;
	if (this->query().lastError().text().length()) {
		return this->query().lastError().text();
	}
	return "";
}

#endif
