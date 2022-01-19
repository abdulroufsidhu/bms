#ifndef AUTH_H
#define AUTH_H

#include "user.h"

class Auth : public QObject {
	Q_OBJECT
	QThread auth_thread;
public:
	inline Auth (QObject* parent = 0) : QObject (parent) { auth_thread.start(); }
	inline ~Auth () { auth_thread.quit(); auth_thread.wait(); }
	Q_INVOKABLE QString login(QString email, QString password);
	Q_INVOKABLE QString signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address );
};
inline QString Auth::login(QString email, QString password) {
	return User::getCurrentUser()->updateByEmail(email,password);
}

inline QString Auth::signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address ) {
	if (password.isEmpty()) return "password not entered";
	if (password != conf_password) return "passwords mismatch";
	if (password.length() < 8) return "password too short";

	Address p_addr = Address();
	QString err = p_addr.insert(p_country,p_city,p_address);
	if (!err.isEmpty()) qCritical() << err;

	Address t_addr = Address();
	err = t_addr.insert(t_country,t_city,t_address);
	if (!err.isEmpty()) qCritical() << err;

	Person p = Person();
	err = p.insert( name,
						email,
						cnic,
						contact,
						p_addr,
						t_addr
					 );
	if (err.length()) qCritical() << err;

	err = p.updateByEmail(email);

	if (err.length()) return err;
	User u = User();
	err = u.insert(p,password);
	User::getCurrentUser()->updateByEmail(email,password);
	return err;

}



#endif // AUTH_H
