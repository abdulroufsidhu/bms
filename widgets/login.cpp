#include "login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    std::string select, from, where ,query;
    std::string email = ui->le_email->text().toLower().toStdString();
    std::string password = ui->le_password->text().toStdString();

    data::Auth a = data::Auth(&email,&password);

}
