#include "authscreen.h"
#include "ui_authscreen.h"

AuthScreen::AuthScreen(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AuthScreen)
{
	ui->setupUi(this);
	ui->layout_login->addWidget(new Login);
	ui->layout_signup->addWidget(new Signup);
}

AuthScreen::~AuthScreen()
{
	delete ui;
}
