#pragma once
#include "db.h"
#include <QPixmap>
#include <QImage>
#include <QBuffer>

#ifndef IMAGE_H
#define IMAGE_H

struct Image {
	Q_GADGET
	Q_PROPERTY( QByteArray data READ getData )
private:
	QByteArray data;

public:
	inline Image () { };
	inline Image (const QByteArray& pathToFile) {this->data = pathToFile;}
	inline ~Image () { };
	bool uploadImage(const QString& pathToFile, QString& owner_id);
	QByteArray& getData() ;
	void loadImage(QString& owner_id);

};

inline bool Image::uploadImage(const QString &pathToFile, QString &owner_id) {
	QPixmap img;
	img.load(pathToFile);
	QByteArray qba;

	if (img.width() >500 || img.height() > 500)
		img = img.scaled(500,500, Qt::AspectRatioMode::KeepAspectRatio);

	QBuffer buffer(&qba);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "PNG", 90);

	QSqlDatabase db = Database::getDB();
	QSqlQuery q(db);
//	q.prepare( QString("INSERT INTO images (owner_id) SELECT :id WHERE NOT EXISTS ( SELECT id FROM images WHERE owner_id = :id ) ; " ) );
//	q.bindValue(":id",owner_id);
	if (!q.exec( QString("INSERT INTO IMAGES (owner_id) SELECT '%1' WHERE NOT EXISTS ( SELECT id FROM IMAGES WHERE owner_id = '%1' ); ").arg(owner_id) ) || q.lastError().text().length()) {
		qCritical() << q.lastQuery() << "    >--->>    " << q.lastError().text();
		// db.close();
		return false;
	}
	q.clear();
	q.prepare("UPDATE IMAGES SET data = :data WHERE owner_id = :id;");
	q.bindValue(":id",owner_id);
	q.bindValue(":data", qba);
	if (!q.exec() || q.lastError().text().length()) {
		qCritical() << q.lastQuery() << "    >--->>    " << q.lastError().text();
		// db.close();
		return false;
	}
	// // db.close();
	qCritical() << "image processed successfully";

	return true;
}
inline QByteArray& Image::getData() { return this->data; }
inline void Image::loadImage(QString& owner_id) {
	QSqlQuery q = Database::rawQuery( QString("SELECT data FROM IMAGES WHERE owner_id = '%1';").arg(owner_id) );
	if (q.lastError().text().length() || q.size() < 1) {
		return ;
	}
	while (q.next()) {
		if (q.value("data").toByteArray().size() < 1) return;
		this->data = "data:image/png;base64," + q.value("data").toByteArray().toBase64();
	}
}

Q_DECLARE_METATYPE(Image)

#endif // IMAGE_H
