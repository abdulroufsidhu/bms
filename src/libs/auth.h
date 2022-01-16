#ifndef AUTH_H
#define AUTH_H

#include "person.h"

class Auth : public QObject {
	Q_OBJECT
	QThread auth_thread;
public:
	inline Auth (QObject* parent = 0) : QObject (parent) { auth_thread.start(); }
	inline ~Auth () { auth_thread.quit(); auth_thread.wait(); }
	Q_INVOKABLE QString signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address );
};

inline QString Auth::signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address ) {
	if (password.isEmpty()) return "password not entered";
	if (password != conf_password) return "passwords mismatch";
	if (password.length() < 8) return "password too short";

	Address p_addr = Address(this);
	QString err = p_addr.insert(p_country,p_city,p_address);
	if (!err.isEmpty()) return err;

	Address t_addr = Address(this);
	err = t_addr.insert(t_country,t_city,t_address);
	if (!err.isEmpty()) return err;

	Person p = Person(this);
	p.insert( name,
						email,
						cnic,
						contact,
						p_addr,
						t_addr
					 );
	p.update(email);
	return p.getEmail().getText();

}

#endif // AUTH_H
