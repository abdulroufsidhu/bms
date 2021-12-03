#include "hire.h"
#include "ui_hire.h"

Hire::Hire(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Hire)
{
	ui->setupUi(this);
}

Hire::~Hire()
{
	delete ui;
}
