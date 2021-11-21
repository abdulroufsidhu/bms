#include "org.h"
#include "ui_org.h"
#include <QTabBar>

Org::Org(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Organization)
{
    ui->setupUi(this);
    int index = data::User::getCurrentUser()->getIndex();
    ui->tabWidget_org_and_branch->tabBar()->setStyle(new CustomTabStyle);
    ui->label_org_name->setText(data::User::getCurrentUser()->getOrganization().at(index).getName().c_str());
    ui->label_organization_founder->setText(data::User::getCurrentUser()->getOrganization().at(index).getPerson().getName().c_str());
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
    QString name, code, country, city, address, contact, email;
    name = ui->le_add_branch_name->text();
    code = ui->le_add_brannch_code->text();
    country = ui->le_add_branch_country->text();
    city = ui->le_add_branch_city->text();
    address = ui->le_add_branch_address->text();
    contact = ui->le_add_branch_contact->text();
    email = ui->le_add_branch_email->text();

    std::string select, from, where, query;
    select = "*";
    query = "insert into emails(email) values ('" + email.toStdString() + "')";
    db::PSQL::getInstance()->set(&query);
    query = "insert into contacts(contact) values ('" + contact.toStdString() + "')";
    db::PSQL::getInstance()->set(&query);
    query = "insert into cities(city) values ('" + city.toStdString() + "')";
    db::PSQL::getInstance()->set(&query);
    query = "insert into countries(country) values ('" + country.toStdString() + "')";
    db::PSQL::getInstance()->set(&query);
    query = "insert into locations(city, country, address) values ('" + city.toStdString() + "','" + country.toStdString() + "','" + address.toStdString() + "')";
    db::PSQL::getInstance()->set(&query);

    std::vector<data::Email> ev;
    from = "emails";
    where = "email = '" + email.toStdString() + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &ev);

    std::vector<data::Contact> cv;
    from = "contacts";
    where = "contact = '" + contact.toStdString() + "'";
    db::PSQL::getInstance()->get(&select, &from, &where, &cv);

    std::vector<data::Location> lv;
    from = "locations";
    where = "city ='" + city.toStdString() + "' and country = '" + country.toStdString() + "' and address ='" + address.toStdString() + "'" ;
    db::PSQL::getInstance()->get(&select, &from, &where, &lv);

    query = "insert into branches (name, code, locationid, organizationid, contactid, emailid) values ('" + name.toStdString() + "','" + code.toStdString() + "','" + lv.at(0).getId() + "','" + data::User::getCurrentUser()->getOrganization().at(data::User::getCurrentUser()->getIndex()).getId() + "','" + cv.at(0).getId() + "','" + ev.at(0).getId() + "')";
    db::PSQL::getInstance()->set(&query);
}

void Org::on_btn_hire_clicked()
{

}

