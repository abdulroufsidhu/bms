#include "person.h"
#include <QPixmap>
#include <QBuffer>
#include <QtWidgets/QMessageBox>

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

	QByteArray getImage();
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
	return "";

}
inline bool User::setImage(QUrl url) {
	QPixmap img;
	img.load(url.toLocalFile());
	QByteArray qba;

	if (img.width() >500 || img.height() > 500)
		img = img.scaled(500,500, Qt::AspectRatioMode::KeepAspectRatio);

	QBuffer buffer(&qba);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "PNG", 90);

	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
	q.prepare( QString("INSERT INTO images (owner_id) SELECT :id WHERE NOT EXISTS(SELECT id FROM IMAGES WHERE owner_id = :id ); " ) );
	q.bindValue(":id",this->id);
	if (!q.exec() || q.lastError().text().length()) {
		qCritical() << q.lastQuery() << "    >--->>    " << q.lastError().text();
		db.close();
		return false;
	}
	q.clear();
	q.prepare("UPDATE IMAGES SET data = :data WHERE owner_id = :id;");
	q.bindValue(":id",this->id);
	q.bindValue(":data", qba);
	if (!q.exec() || q.lastError().text().length()) {
		qCritical() << q.lastQuery() << "    >--->>    " << q.lastError().text();
		db.close();
		return false;
	}
	db.close();
	this->loadImage();

	return true;
}

inline QByteArray User::getImage() {
	return this->image;
}

inline void User::loadImage() {
	QSqlQuery q = Database::rawQuery( QString("SELECT data FROM IMAGES WHERE owner_id = '%1';").arg(this->id) );
	if (q.lastError().text().length() || q.size() < 1) {
		return ;
	}
	while (q.next()) {
		if (q.value("data").toByteArray().size() < 1) return;
		this->image = "data:image/png;base64," + q.value("data").toByteArray().toBase64();
	}
	emit imageChanged();
}

#endif // USER_H
