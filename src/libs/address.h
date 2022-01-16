
#include "db.h"

#ifndef COUNTRY_H
#define COUNTRY_H
class Country: public QObject {
	Q_OBJECT
private:
	QString id, name;
public:
	inline Country(QObject* parent = 0) : QObject(parent) {}
	inline ~Country() {}
	QString& getId();
	QString& getName();
	QString update(QString &country);
	void copy(Country& c);
};

inline QString& Country::getId() { return this->id; }
inline QString& Country::getName() { return this->name; }
inline void Country::copy(Country& c) { this->id = c.id; this->name = c.name; }
inline QString Country::update(QString &country) {
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT id, name FROM COUNTRIES WHERE name = '%1';").arg(country));
	db.close();
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}
	return "insertion successfull";
}

#endif

#ifndef CITY_H
#define CITY_H
class City: public QObject {
	Q_OBJECT
private:
	QString id, name; Country country = Country(this);
public:
	inline City(QObject* parent = 0) : QObject(parent) {}
	inline ~City() {}
	QString& getId();
	QString& getName();
	Country& getCountry();
	QString update(QString& country, QString& city);
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
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("SELECT id, name FROM CITIES WHERE name = '%1' AND country_id = '%2';").arg(city, this->country.getId() ) );
	db.close();
	if (!q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}
	return "";
}
inline QString City::insert(QString &country, QString &city) {
	this->country.update(country);
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString("INSERT INTO CITIES (name, country_id) VALUES ('%1','%2'); ").arg(city, this->country.getId() ) );
	db.close();
	return "";
}
#endif //CITY_H

#ifndef ADDRESS_H
#define ADDRESS_H
class Address: public QObject {
	Q_OBJECT
private:
	QString id,name; City city = City(this);
public:
	inline Address(QObject* parent) : QObject(parent) {}
	inline ~Address() {}
	QString& getId();
	QString& getName();
	City& getCity();
	void copy(Address& a);
	QString update(QString& country, QString& city, QString& address);
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
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.exec( QString( "SELECT id, name FROM LOCATIONS WHERE name = '%1' AND city_id = '%2';").arg(address, this->city.getId() ) );
	db.close();
	if (!q.isValid() || !q.lastError().text().isEmpty()) return q.lastError().text();
	while (q.next()) {
		this->id = q.value(0).toString();
		this->name = q.value(1).toString();
	}
	return "";
}
inline QString Address::insert(QString &country, QString &city, QString &address) {
	this->city.insert(country,city);
	QString err = "";
	err = this->city.update(country,city);
	if (!err.isEmpty()) return err;
	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	qCritical() << this->city.getId();
	qCritical() << this->city.getCountry().getId();
	q.exec( QString("INSERT INTO LOCATIONS (name, city_id) VALUES ('%1','%2');").arg(address, this->city.getId() ) );
	db.close();
	return "";
}

#endif //ADDRESS_H

