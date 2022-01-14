#ifndef AUTH_H
#define AUTH_H

#include "address.h"

class Auth : public QObject {
	Q_OBJECT
public:
	inline Auth (QObject* parent = 0) : QObject (parent) {}
	inline ~Auth () {}
	inline Q_INVOKABLE QString signup(QString name, QString email, QString contact, QString cnic, QString password, QString conf_password, QString p_country, QString p_city, QString p_address, QString t_country, QString t_city, QString t_address ) {
		if (password.isEmpty()) return "password not entered";
		if (password != conf_password) return "passwords mismatch";
		if (password.length() < 8) return "password too short";

		Address p_loc;
		p_loc.insert(p_country,p_city,p_address);
		Address t_loc;
		t_loc.insert(t_country,t_city,t_address);

		QString query("BEGIN;");
		query += "INSERT INTO CONTACTS (name) VALUES(" +contact+ ");";
		query += "INSERT INTO EMAILS (name) VALUES ('"+email+"');";
		query += "INSERT INTO CNICS (name) VALUES ('"+cnic+"');";
		query += QString("INSERT INTO PERSONS (name, temp_residence_id, perm_residence_id,email_id,cnic_id,contact_id) VALUES ('%1','%2','%3','%4','%5','%6');").arg(name,t_loc.getId(),p_loc.getId());
		query += "COMMIT;";

		Database db;
		QSqlQuery q = db.rawQuery(query);
		if (q.lastError().text().length()) q.exec("ROLLBACK");
		return q.lastError().text();
	}
};

#endif // AUTH_H
