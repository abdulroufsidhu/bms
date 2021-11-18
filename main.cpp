#include "mainwindow.h"
#include "./widgets/authscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthScreen auth;
    auth.show();
//    MainWindow w;
//    w.show();
    return a.exec();
}
