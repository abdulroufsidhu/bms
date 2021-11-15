#include "store.h"
#include "ui_store.h"

Store::Store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Store)
{
    ui->setupUi(this);
}

Store::~Store()
{
//    QMessageBox::information(this,"destroying", "store destroyed");
    delete ui;
}
