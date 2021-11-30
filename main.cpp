#include "mainwindow.h"
#include "./widgets/authscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFont f = a.font();
			f.setPointSize(14);
			a.setFont(f);
	AuthScreen auth;
	auth.show();
//			MainWindow w;
//			w.show();
	return a.exec();
}
