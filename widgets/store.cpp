#include "store.h"
#include "ui_store.h"

#include <QUuid>

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

void Store::on_btn_generate_uuid_clicked()
{
    QUuid uid = QUuid::createUuid();
    //0 default for uuid enclosed in curly braces with dashes 1 for with dashes without curly braces and 3 for without dashes as well this 3rd cannot be reused with QUuid class
    ui->le_serial->setText(uid.toString(QUuid::StringFormat(3)));
}

