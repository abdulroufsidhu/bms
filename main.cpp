#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <QQmlContext>
#include "./src/libs/auth.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
									 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	Database *db = new Database();
	Auth auth;
	QStringList _row_to_search = { "Item ID" , "Item Menufecturer" , "Item Vendor" , "Item Serial" , "Item Price" , "Item Name" , "Customer Name" , "Customer Contact" , "Customer National ID" };
	QStringList _country_list = {};
	db->begin();
	QSqlQuery q = db->rawQuery("SELECT name FROM COUNTRIES");
	db->commit();
	while(q.next()) {
		_country_list.append(q.value(0).toString());
	}

	engine.rootContext()->setContextProperty("_db",db);
	engine.rootContext()->setContextProperty("_auth",&auth);
	engine.rootContext()->setContextProperty("_row_to_search", QVariant::fromValue(_row_to_search));
	engine.rootContext()->setContextProperty("_country_list",QVariant::fromValue(_country_list));

	return app.exec();
}
