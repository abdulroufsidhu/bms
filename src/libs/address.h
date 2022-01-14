#include "db.h"

#ifndef COUNTRY_H
#define COUNTRY_H

class Country : public QObject {
	Q_OBJECT

private:
	QString id;
	QString name;

public:
	inline Country(QObject* parent = 0) : QObject(parent) {}
	inline ~Country() {};
	inline QString& getId() {return this->id;}
	inline QString& getName() {return this->name;}
	inline void update(QString& name) {
		Database db = Database (this);
		QSqlQuery q = db.rawQuery("SELECT * FROM COUNTRIES WHERE name = '" + name + "');");
		if (!q.isValid()) return;
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}

};

#endif // COUNTRY_H

#ifndef CITY_H
#define CITY_H

class City : public QObject {
	Q_OBJECT
public:
	inline City(QObject *parent = 0) : QObject(parent) {}
	inline ~City() {}
	inline QString& getId() {return this->id;}
	inline QString& getName() {return this->name;}
	inline Country& getCountry() {return this->country;}

	inline void update(QString& country, QString& city) {
		this->country.update(country);
		Database db;
		QSqlQuery q = db.rawQuery("SELECT id,name FROM CITIES WHERE country_id = '" + this->country.getId() + "' AND name = '"+city+"';");
		if (!q.isValid()) return;
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}

	inline bool insert(QString& country, QString& city) {
		this->country.update(country);
		QString query;
		query = QString(" BEGIN; INSERT INTO CITIES (county_id, name) SELECT '%1','%2' WHERE NOT EXISTS ( SELECT country_id, name WHERE country_id = '%1' AND name = '%2' ); COMMIT;").arg(this->country.getId(), city.toUpper());
		Database db;
		QSqlQuery q = db.rawQuery(query);
		if (q.lastError().text().isEmpty()) {
			this->update(country,city);
			return true;
		}
		q.exec("ROLLBACK;");
		return false;
	}


private:
	QString id;
	QString name;
	Country country;
};

#endif // CITY_H


#ifndef ADDRESS_H
#define ADDRESS_H

class Address: public QObject {
	Q_OBJECT
public:
	inline Address(QObject *parent = 0) : QObject(parent) {}
	inline ~Address() {}
	inline QString& getId() {return this->id;}
	inline QString& getName() {return this->name;}
	inline City& getCity() {return this->city;}

	inline void update(QString country, QString city, QString location) {
		this->city.update(country,city);
		Database db;
		QString query;
		query=QString("SELECT id, name FROM LOCATIONS WHERE city_id = '%1' AND name = '%2'; ").arg(this->city.getId(),location.toUpper());
		QSqlQuery q = db.rawQuery(query);
		if (!q.isValid()) return;
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}

	inline bool insert(QString country, QString city, QString location) {
		this->city.insert(country,city);
		this->city.update(country,city);
		Database db;
		QSqlQuery q = db.rawQuery( QString("BEGIN; INSERT INTO LOCATIONS (city_id, name) SELECT '%1','&2' WHERE NOT EXISTS (SELECT city_id, name FROM LOCATIONS WHERE city_id = '%1' AND name = '%2'); COMMIT; ").arg(this->city.getId(),location.toUpper() ) );
		if (q.lastError().text().isEmpty()){
			this->update(country,city,location);
			return true;
		}
		q.exec("ROLLBACK;");
		return false;
	}

private:
	QString id;
	QString name;
	City city;
};

#endif // ADDRESS_H
