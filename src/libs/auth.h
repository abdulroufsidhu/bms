#ifndef AUTHWRAPER_H
#define AUTHWRAPER_H

#include "user.h"

class AuthWraper : public QObject {
	Q_OBJECT
public:
	inline AuthWraper (QObject* parent = 0) : QObject (parent) { }
	inline ~AuthWraper () {  }

signals:
	void logedIn(QString );
	void signedUp(QString );
	void orgRegistered(QString );
public slots:
	void login(QString email, QString password);
	void signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address );
	void register_organization(QString user_id, QString name, QString email, QString contact, QString regNum, QString country, QString city, QString address, QUrl url);

};

inline void AuthWraper::login(QString email, QString password) {
	qCritical() << "loging in";
	QString err = User::getCurrentUser()->updateByEmail(email.toUpper(),password);
	emit logedIn(err);
	return;
}
inline void AuthWraper::signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address ) {
	if (password.isEmpty()) {emit signedUp("password not entered"); return;}
	if (password != conf_password) {emit signedUp("passwords mismatch"); return;}
	if (password.length() < 8) { emit signedUp("password too short"); return;}

	Address p_addr = Address();
	QString err = p_addr.insert(p_country.toUpper(),p_city.toUpper(),p_address.toUpper());
	if (!err.isEmpty()) qCritical() << err;
	Address t_addr = Address();
	err = t_addr.insert(t_country.toUpper(),t_city.toUpper(),t_address.toUpper());
	if (!err.isEmpty()) qCritical() << err;

	Person p = Person();
	err = p.insert( name,
						email.toUpper(),
						cnic,
						contact,
						p_addr,
						t_addr
					 );
	if (err.length()) { emit signedUp(err); return; }
	err = p.updateByEmail(email.toUpper());
	if (err.length()) { emit signedUp(err); return; }
	User u = User();
	err = u.insert(p,password);
	User::getCurrentUser()->updateByEmail(email.toUpper(),password);

	emit signedUp(err);
	return;

}
inline void AuthWraper::register_organization(QString user_id, QString name, QString email, QString contact, QString regNum, QString country, QString city, QString address, QUrl url) {
	qCritical () << "setting up address";
	Address a;
	QString err = a.insert(country, city, address);
	if (a.getId().isEmpty()) { emit orgRegistered (err); return;}
	err = Organization::insert(user_id,name,email,contact,regNum,a, url);
	emit orgRegistered(err);
	return;
}

#endif // AUTHWRAPER_H

#ifndef AUTH_H
#define AUTH_H

class Auth : public QObject {
	Q_OBJECT
signals:
	void login(QString, QString);
	void logedIn(QString);

	void signup(QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString );
	void signedUp(QString );

	void register_organization(QString , QString , QString , QString , QString , QString , QString , QString , QUrl );
	void orgRegistered(QString );

private:
	QThread *reg_auth_thread;
	AuthWraper *auth_wrapper;
public:
	inline explicit Auth(QObject* parent = nullptr) : QObject(parent) {
		qCritical () << "initializing Auth";
		auth_wrapper = new AuthWraper();
		reg_auth_thread = new QThread();
		auth_wrapper->moveToThread(reg_auth_thread);

		connect(this,SIGNAL(login(QString , QString )),auth_wrapper,SLOT(login(QString , QString )));
		connect(auth_wrapper, SIGNAL(logedIn(QString )), this, SIGNAL(logedIn(QString )));

		connect(this, SIGNAL(signup(QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString )),
						auth_wrapper, SLOT(signup(QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString , QString )));
		connect(auth_wrapper,SIGNAL(signedUp(QString)),
						this, SIGNAL(signedUp(QString)));

		connect(this, SIGNAL(register_organization(QString , QString , QString , QString , QString , QString , QString , QString , QUrl )),
						auth_wrapper, SLOT(register_organization(QString , QString , QString , QString , QString , QString , QString , QString , QUrl )) );
		connect(auth_wrapper, SIGNAL(orgRegistered(QString )),
						this, SIGNAL(orgRegistered(QString )));

		reg_auth_thread->start();

	};
	inline ~Auth() {
		reg_auth_thread->quit();
		reg_auth_thread->wait();
		delete auth_wrapper; delete reg_auth_thread;
	}

};

#endif //AUTH_H





