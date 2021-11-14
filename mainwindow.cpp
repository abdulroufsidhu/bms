#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_set_clicked()
{
    std::string str = ui->le_set->text().toStdString();
    db::PSQL::getInstance()->set( &str );
}


void MainWindow::on_btn_get_clicked()
{
    std::string select = ui->le_select->text().toStdString();
    std::string from = ui->le_from->text().toStdString();
    std::string where = ui->le_where->text().toStdString();

    std::vector<data::Branch> u;
    db::PSQL::getInstance()->get(&select,&from, &where, &u);

//    QMessageBox::information(this, "u" , u.at(0).getId().c_str());

}

