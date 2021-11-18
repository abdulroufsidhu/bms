#include "org.h"
#include "ui_org.h"
#include <QTabBar>

Org::Org(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Organization)
{
    ui->setupUi(this);
    ui->tabWidget_org_and_branch->tabBar()->setStyle(new CustomTabStyle);
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

    data::Email e;
    std::vector<data::Email> ev;
    db::PSQL::getInstance()->get(&select , &from , &where, &ev );
    e = ev.at(0);
    query = "insert into organizations(name, emailid, founderid) values ('" + name + "','" + e.getId() + "','" + data::User::getCurrentUser()->getId() + "')";
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

