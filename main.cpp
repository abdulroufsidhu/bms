#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <QQmlContext>
#include "./src/libs/auth.h"
#include "./src/models/list_models.h"

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
	OrganizationListModel organization_list;
	BranchListModel branch_list;
	User *current_user = User::getCurrentUser();
	QStringList _row_to_search = { "Item ID" , "Item Menufecturer" , "Item Vendor" , "Item Serial" , "Item Price" , "Item Name" , "Customer Name" , "Customer Contact" , "Customer National ID" };
	QStringList _country_list = {};
	QSqlDatabase qdb = db->getDB();
	QSqlQuery q(qdb) ;
	q.exec("SELECT name FROM COUNTRIES ORDER BY name;");
	qdb.close();
	while(q.next()) {
		_country_list.append(q.value(0).toString());
	}
	engine.rootContext()->setContextProperty("_db",db);
	engine.rootContext()->setContextProperty("_auth",&auth);
	engine.rootContext()->setContextProperty("_row_to_search", QVariant::fromValue(_row_to_search));
	engine.rootContext()->setContextProperty("_current_user", QVariant::fromValue(current_user) ) ;
	engine.rootContext()->setContextProperty("_country_list",QVariant::fromValue(_country_list));
	engine.rootContext()->setContextProperty("_organization_list",&organization_list);
	engine.rootContext()->setContextProperty("_branch_list",&branch_list);
	return app.exec();
}
