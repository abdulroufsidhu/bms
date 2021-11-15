#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./libs/api.h"
#include "./libs/user.h"
#include "./widgets/home.h"
#include "./widgets/store.h"
#include "./widgets/org.h"
#include "./widgets/personal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_home_clicked();

    void on_btn_inventory_clicked();

    void on_btn_organization_clicked();

    void on_btn_person_clicked();

private:
    Ui::MainWindow *ui;
    Home* h = NULL;
    Store* s = NULL;
    Org* o = NULL;
    Personal* p = NULL;


};
#endif // MAINWINDOW_H
