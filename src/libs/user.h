#include "person.h"
#include "employee.h"
#include "image.h"

#ifndef USER_H
#define USER_H
class User: public QObject {
	Q_OBJECT
	Q_PROPERTY(QString id READ getId )
	Q_PROPERTY(Person person READ getPerson NOTIFY personChanged)
	Q_PROPERTY(QByteArray image READ getImage NOTIFY imageChanged )
private:
	QString id;
	Person person = Person();
	QByteArray image = "qrc:/icons/icons/user-profile 1.svg";

	inline static User *current_user = nullptr;

signals:
	void personChanged();
	void imageChanged();

public:
	inline User(QObject* parent = 0) : QObject(parent) {}
	inline ~User() {}
	inline static User* getCurrentUser() {
		if (current_user == nullptr) current_user = new User();
		return current_user;
	}
	QString getId() const;
	void setId(QString id);

	QString insert(Person& p, QString& password);
	QString updateByEmail(QString& email, QString& password);
	QString updateByPersonId(QString& pid, QString& password);
	void copy(User& u);

	Person &getPerson() ;
	void setPerson(Person &newPerson);

	QByteArray& getImage();
	Q_INVOKABLE bool setImage(QUrl url) ;

	void loadImage();

};
inline Person& User::getPerson() { return this->person; }
inline void User::setPerson(Person &newPerson) {
	if (newPerson.getId().isEmpty()) return;
	if (this->person.getId() == newPerson.getId()) return;
	this->person.copy(newPerson);
}
inline QString User::getId() const { return this->id; }
inline void User::setId(QString id) {
	if (this->id == id) return;
	this->id = id;
}
inline void User::copy(User &u) {
	this->id = u.id;
	this->person.copy(u.person);
}
inline QString User::insert(Person &p, QString& password) {
	QSqlQuery q = Database::rawQuery( QString("INSERT INTO USERS (person_id, password) VALUES ('%1','%2') RETURNING id; ").arg(p.getId(),password) );
	if (q.lastError().text().length()) return q.lastError().text();
	this->person.copy(p);
	while(q.next()) {
		this->id = q.value("id").toString();
	}

	return "";
}
inline QString User::updateByEmail(QString &email, QString& password) {
	QString err = this->person.updateByEmail(email);
	if (err.length()) return "account does not exists";
	QSqlQuery q = Database::rawQuery( QString("SELECT id FROM USERS WHERE person_id = '%1' and password = '%2' ;").arg(this->person.getId(), password ) );
	if (q.lastError().text().length()) return "Credentals are not correct";
	if (q.size() < 1) return "Credentials are not correct";
	while (q.next()) {
		this->id = q.value("id").toString();
	}
	this->loadImage();
	return "";
}
inline QString User::updateByPersonId(QString &pid, QString &password) {
	QString err = this->person.updateById(pid);
	if (err.length()) return err;
	QSqlQuery q = Database::rawQuery( QString("SELECT id FROM USERS WHERE person_id = '%1' and password = '%2';").arg(pid, password) );
	if (q.lastError().text().length()) return "Credenials are not correct";
	while (q.next()) {
		this->id = q.value("id").toString();
	}
	this->loadImage();
	return "";

}
inline bool User::setImage(QUrl url) {
	Image i = Image(url.toLocalFile().toStdString().c_str());
	bool b = i.uploadImage(url.toLocalFile(),this->id);
	if (b) {
		i.loadImage(this->id);
		this->image = i.getData();
		emit imageChanged();
	}
	return b;
}

inline QByteArray& User::getImage() {
	return this->image;
}

inline void User::loadImage() {
	Image i = Image("qrc:/icons/icons/user-profile 1.svg");
	i.loadImage(this->id);
	this->image = i.getData();
	emit imageChanged();
}

#endif // USER_H
