
#include "db.h"

#ifndef COUNTRY_H
#define COUNTRY_H
class Country {
	Q_GADGET
private:
	QString id, name;
public:
	inline Country() {}
	inline ~Country() {}
	QString updateById(QString& id);
	QString& getId();
	QString& getName();
	QString update(QString &country);
	void copy(Country& c);
};

inline QString& Country::getId() { return this->id; }
inline QString& Country::getName() { return this->name; }
inline void Country::copy(Country& c) { this->id = c.id; this->name = c.name; }
inline QString Country::update(QString &country) {
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM COUNTRIES WHERE name = '%1';").arg(country));
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}
	return "insertion successfull";
}
inline QString Country::updateById(QString &id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT name FROM COUNTRIES WHERE id = '%1'; ").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = id;
		this->name = q.value("name").toString();
	}
	return "";
}
#endif

#ifndef CITY_H
#define CITY_H
class City {
private:
	QString id, name; Country country = Country();
public:
	inline City() {}
	inline ~City() {}
	QString& getId();
	QString& getName();
	Country& getCountry();
	QString update(QString& country, QString& city);
	QString updateById(QString& id);
	QString insert(QString& country, QString& city);
	void copy(City& c);
};

inline QString& City::getId() { return this->id; }
inline QString& City::getName() { return this->name; }
inline Country& City::getCountry() { return this->country; }
inline void City::copy(City &c) {
	this->id = c.id;
	this->name = c.name;
	this->country.copy(c.country);
}
inline QString City::update(QString &country, QString &city) {
	this->country.update(country);
	QSqlQuery q = Database::rawQuery( QString("SELECT id, name FROM CITIES WHERE name = '%1' AND country_id = '%2';").arg(city, this->country.getId() ) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value("id").toString();
		this->name = q.value("name").toString();
	}
	return "";
}
inline QString City::updateById(QString &id) {
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT name, country_id FROM CITIES WHERE id = '%1'").arg(id) );
	db.close();
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	QString t_cid = "";
	while (q.next()) {
		this->name = q.value("name").toString();
		t_cid = q.value("country_id").toString();
	}
	QString err = this->country.updateById(t_cid);
	return err;
}
inline QString City::insert(QString &country, QString &city) {
	this->country.update(country);
	QSqlQuery q = Database::rawQuery( QString("INSERT INTO CITIES (name, country_id) VALUES ('%1','%2'); ").arg(city, this->country.getId() ) );
	return q.lastError().text();
}
#endif //CITY_H

#ifndef ADDRESS_H
#define ADDRESS_H
class Address {
	Q_GADGET
private:
	QString id,name; City city = City();
public:
	inline Address() {}
	inline ~Address() {}
	QString& getId();
	QString& getName();
	City& getCity();
	void copy(Address& a);
	QString update(QString& country, QString& city, QString& address);
	QString updateById(QString& id);
	QString insert(QString& country, QString& city, QString& address);
};

inline QString& Address::getId() { return this->id; }
inline QString& Address::getName() { return this->name; }
inline City& Address::getCity() { return this->city; }
inline void Address::copy(Address &a) {
	this->id = a.id;
	this->name = a.name;
	this->city.copy(a.city);
}
inline QString Address::update(QString &country, QString &city, QString &address) {
	this->city.update(country,city);
	QSqlQuery q = Database::rawQuery( QString( "SELECT id, name FROM LOCATIONS WHERE name = '%1' AND city_id = '%2';").arg(address, this->city.getId() ) );
	if (!q.isValid() || !q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}
	return "";
}
inline QString Address::updateById(QString &id) {
	QString cid = "";
	QSqlQuery q = Database::rawQuery( QString ("SELECT name, city_id FROM LOCATIONS WHERE id = '%1';").arg(id) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	this->id = id;
	while (q.next()) {
		this->name = q.value("name").toString();
		cid = q.value("city_id").toString();
	}
	return this->city.updateById(cid);
}
inline QString Address::insert(QString &country, QString &city, QString &address) {
	QString err = "";
	err = this->city.insert(country,city);
	if (err.length()) qCritical() << err;
	err = this->city.update(country,city);
	if (!err.isEmpty()) return err;
	QSqlQuery q = Database::rawQuery( QString("INSERT INTO LOCATIONS (name, city_id) VALUES ('%1','%2') ;" ).arg(address, this->city.getId() ) );
	q = Database::rawQuery( QString("SELECT id FROM LOCATIONS WHERE name = '%1' AND city_id = '%2'; ").arg(address, this->city.getId() ) );
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
	}
	this->name = address;
	return "";
}

#endif //ADDRESS_H

