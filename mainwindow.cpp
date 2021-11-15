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

void MainWindow::on_btn_home_clicked()
{
    delete s; s = NULL;
    delete o; o = NULL;
    delete p; p = NULL;
    if (h==NULL) h = new Home();
    db::PSQL::clearLayout(ui->output_layout);
    ui->output_layout->addWidget(h);
}


void MainWindow::on_btn_inventory_clicked()
{
    delete h; h = NULL;
    delete o; o = NULL;
    delete p; p = NULL;
    if (s==NULL) s = new Store();
    db::PSQL::clearLayout(ui->output_layout);
    ui->output_layout->addWidget(s);

}


void MainWindow::on_btn_organization_clicked()
{
    delete h; h = NULL;
    delete s; s = NULL;
    delete p; p = NULL;
    if (o==NULL) o = new Org();
    db::PSQL::clearLayout(ui->output_layout);
    ui->output_layout->addWidget(o);
}


void MainWindow::on_btn_person_clicked()
{
    delete h; h = NULL;
    delete o; o = NULL;
    delete s; s = NULL;
    if (p==NULL) p = new Personal();
    db::PSQL::clearLayout(ui->output_layout);
    ui->output_layout->addWidget(p);
}

