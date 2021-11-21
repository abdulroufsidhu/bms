#include "personal.h"
#include "ui_personal.h"
#include "../libs/user.h"

Personal::Personal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    ui->label_name->setText(data::User::getCurrentUser()->getPerson().getName().c_str());
    ui->label_email->setText(data::User::getCurrentUser()->getPerson().getEmail().getText().c_str());
    ui->label_cnic->setText(data::User::getCurrentUser()->getPerson().getCnic().getText().c_str());
    ui->label_address->setText(data::User::getCurrentUser()->getPerson().getLocation().getAddress().c_str());
    ui->label_contact->setText(data::User::getCurrentUser()->getPerson().getContact().getText().c_str());
    ui->label_city->setText(data::User::getCurrentUser()->getPerson().getLocation().getCity().c_str());
    ui->label_country->setText(data::User::getCurrentUser()->getPerson().getLocation().getCountry().c_str());
    ui->label_address->setText(data::User::getCurrentUser()->getPerson().getLocation().getAddress().c_str());


}

Personal::~Personal()
{
//    QMessageBox::information(this,"destroying", "personal destroyed");
    delete ui;
}
