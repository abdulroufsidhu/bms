#include "org.h"
#include "ui_org.h"
#include <QTabBar>

Org::Org(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Organization)
{
    ui->setupUi(this);
    ui->tabWidget_org_and_branch->tabBar()->setStyle(new CustomTabStyle);
    ui->label_org_name->setText(data::User::getCurrentUser()->getBranch().getOrganization().getName().c_str());
    ui->label_organization_founder->setText(data::User::getCurrentUser()->getBranch().getOrganization().getPerson().getName().c_str());
    ui->label_current_branch->setText(data::User::getCurrentUser()->getBranch().getName().c_str());
    ui->label_current_location->setText(data::User::getCurrentUser()->getBranch().getLocation().getAddress().c_str());
}

Org::~Org()
{
//    QMessageBox::information(this,"destroying", "org destroyed");
    delete ui;
}

void Org::on_btn_register_clicked()
{
    std::string name, email, query, select, from, where;
    name = ui->le_org_name->text().toStdString();
    email = ui->le_org_email->text().toStdString();

    select = "*";
    from = "emails";
    where = "email = '" + email + "'";
    query = "insert into emails(email) values ('" + email + "')";
    db::PSQL::getInstance()->set(&query);

    std::vector<data::Email> ev;
    db::PSQL::getInstance()->get(&select , &from , &where, &ev );
    query = "insert into organizations(name, emailid, founderid) values ('" + name + "','" + ev.at(0).getId() + "','" + data::User::getCurrentUser()->getPerson().getId() + "')";
    db::PSQL::getInstance()->set(&query);
}

void Org::on_btn_relocate_clicked()
{

}

void Org::on_btn_revoke_clicked()
{

}

void Org::on_btn_add_branch_clicked()
{

}

void Org::on_btn_hire_clicked()
{

}

