#include "../libs/employee.h"
#include <QAbstractListModel>

#ifndef ORGANIZATION_LIST_H
#define ORGANIZATION_LIST_H

class OrganizationListModel : public QAbstractListModel {
	Q_OBJECT
private:
//	enum Roles {
//					NameRole = Qt::UserRole,
//					IdRole,
//					EmailRole
//			};

//	inline explicit OrganizationListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

//			int rowCount(const QModelIndex& parent) const override;
//			QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
//			QHash<int, QByteArray> roleNames() const override;

//	public slots:
//			void duplicateData(int row);
//			void removeData(int row);

//	private slots:
////			void growPopulation();

//	private: //members
//			QVector< Organization > m_data;
};

#endif // ORGANIZATION_LIST_H
