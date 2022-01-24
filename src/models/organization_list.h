#include "../libs/user.h"
#include <QAbstractListModel>

#ifndef ORGANIZATION_LIST_H
#define ORGANIZATION_LIST_H

class OrganizationListModel : public QAbstractListModel {
	Q_OBJECT
	Q_ENUMS(Roles)
	QThread orgListThread;
public:
	enum Roles {
		NameRole = Qt::UserRole,
		IdRole,
		EmailRole,
		CountryRole,
		AddressRole,
		ContactRole
	};
	inline explicit OrganizationListModel(QObject *parent = nullptr) : QAbstractListModel (parent) {
		orgListThread.start();
		this->update();
	}
	inline ~OrganizationListModel() {orgListThread.quit(); orgListThread.wait();}
	void refresh();
	int rowCount(const QModelIndex& parent) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
	QHash<int, QByteArray> roleNames() const override;
public slots:
	QString update();
private: //members
	QHash<int,QByteArray> hash {
		{NameRole, "name"},
		{IdRole, "id"},
		{EmailRole, "email"},
		{ContactRole, "contact"}
	};
	QVector<Organization> m_data;

};

inline QHash<int, QByteArray> OrganizationListModel::roleNames() const { return this->hash; }
inline int OrganizationListModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid())
		return 0;
	return m_data.size();
}
inline QVariant OrganizationListModel::data(const QModelIndex &index, int role) const {
	if ( !index.isValid() )
		return QVariant();

	const Organization& org = m_data.at(index.row() );
	if ( role == NameRole )
		return org.getName() ;
	else if ( role == IdRole )
		return org.getId();
	else if ( role == EmailRole )
		return org.getEmail().getText();
	else if ( role == AddressRole )
		return org.getAddress().getName();
	else if ( role == ContactRole )
		return org.getContact().getText();
	else if ( role == CountryRole )
		return org.getAddress().getCity().getCountry().getName();
	else
		return QVariant();
}
inline void OrganizationListModel::refresh() {
	//	this->setQuery(OrganizationListModel::SQL_SELECT);
}
inline QString OrganizationListModel::update() {
	QSqlQuery q = Database::rawQuery( QString("SELECT o.* FROM EMPLOYEES e, BRANCHES b, ORGANIZATIONS o WHERE e.user_id = '%1' AND e.branch_id = b.id AND b.organization_id = o.id;").arg(User::getCurrentUser()->getId()) );
	if (q.lastError().text().length()) return q.lastError().text();
	this->m_data.clear();
	int row = 0;
	while (q.next()) {
		Email e;
		Address a;
		Contact c;
		QString id, name, reg_num;
		id = q.value("id").toString();
		name = q.value("name").toString();
		reg_num = q.value("gov_reg_num").toString();
		c.updateById(q.value("contact_id").toString());
		a.updateById(q.value("location_id").toString());
		e.updateById(q.value("email_id").toString());
		this->m_data << (Organization(id,name,reg_num,c,e,a));

		const Organization data = m_data.last();
		const int rowOfInsert = row;

		beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
		m_data.insert(rowOfInsert, data);
		endInsertRows();
		++row;
		qCritical() << this->m_data.last().getName()
								<< this->m_data.last().getEmail().getText();
	}
	return "";
}
inline bool OrganizationListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
		return false;
	this->update();
	emit dataChanged(index,index, {role} );
	return true;
}

#endif // ORGANIZATION_LIST_H
