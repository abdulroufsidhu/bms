#include "org.h"
#include "ui_org.h"

Org::Org(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Org)
{
    ui->setupUi(this);
}

Org::~Org()
{
//    QMessageBox::information(this,"destroying", "org destroyed");
    delete ui;
}
