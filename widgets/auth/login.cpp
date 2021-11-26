#include "login.h"
#include "../authscreen.h"

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

	MainWindow* w = new MainWindow(0);
	data::Auth a = data::Auth(&email,&password, ((AuthScreen*) this->parent()->parent()->parent()->parent()->parent()->parent()->parent()) , w);


}


