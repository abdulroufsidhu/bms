#include "org.h"
#include "ui_org.h"
#include <QMessageBox>
#include <QTabBar>

Org::Org(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Organization)
{   
	ui->setupUi(this);

	orgInfoPage();

	updateLWOrg();

	updateLWBranches();

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

	std::vector<data::Organization> ov;
	from = "organizations";
	where = "founderid = '" + data::User::getCurrentUser()->getPerson().getId() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &ov);
	data::User::getCurrentUser()->setOrganizationVec(&ov);

	if (ov.at(ov.size()-1).getEmail().getText() == email ) {
			ui->le_org_name->setText("");
			ui->le_org_email->setText("");
			QMessageBox::information(this, "success", "successfully registered new organization");
		}
}

void Org::on_btn_relocate_clicked()
{

}

void Org::on_btn_revoke_clicked()
{
	QString email = ui->le_branch_email_revoke->text();
	std::string select, from, where, query;

	std::vector<data::Email> ev;
	select = "*";
	from = "emails";
	where = "email ='" + email.toStdString() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &ev);

	query = "UPDATE branches SET active = false WHERE emailid ='" + ev.at(0).getId() + "'";
	ui->le_branch_email_revoke->setText("");

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

	query = "insert into branches (name, code, locationid, organizationid, contactid, emailid) values ('" + name.toStdString() + "','" + code.toStdString() + "','" + lv.at(0).getId() + "','" + data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getId() + "','" + cv.at(0).getId() + "','" + ev.at(0).getId() + "')";
	db::PSQL::getInstance()->set(&query);

	std::vector<data::Branch> bv;
	select = "*";
	from = "branches";
	where = "organizationid = '" + data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getId() + "' AND active";
	db::PSQL::getInstance()->get(&select, &from, &where, &bv);

	if (bv.at(bv.size()-1).getCode() == code.toStdString() ) {
			ui->le_add_branch_name->setText("");
			ui->le_add_brannch_code->setText("");
			ui->le_add_branch_country->setText("");
			ui->le_add_branch_city->setText("");
			ui->le_add_branch_address->setText("");
			ui->le_add_branch_contact->setText("");
			ui->le_add_branch_email->setText("");
			QMessageBox::information(this, "success", "successfully added new organization");
		}
}

void Org::on_btn_hire_clicked()
{

}


void Org::on_tabWidget_2_currentChanged(int index)
{
	if (index == 0) {
			updateLWOrg();
		}
}

void Org::updateLWOrg() {
	ui->lw_organizations->clear();
	for (auto i : data::User::getCurrentUser()->getOrganizationVec()) {
			QString str = QString((i.getName() + " : " + i.getEmail().getText() ).c_str());
			ui->lw_organizations->addItem(str);
		}
}

void Org::on_lw_organizations_doubleClicked(const QModelIndex &index)
{
	data::User::getCurrentUser()->setOrgIndex(index.row());
	QMessageBox::information(this, "current organization changed", "current organization changed to " + QString(data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getEmail().getText().c_str() ) );
}


void Org::on_tabWidget_currentChanged(int index)
{
	if (index==0) {
			orgInfoPage();
		}
}

void Org::orgInfoPage() {
	int index = data::User::getCurrentUser()->getOrgIndex();
	ui->tabWidget_org_and_branch->tabBar()->setStyle(new CustomTabStyle);
	ui->label_org_name->setText(data::User::getCurrentUser()->getOrganizationVec().at(index).getName().c_str());
	ui->label_organization_founder->setText(data::User::getCurrentUser()->getOrganizationVec().at(index).getPerson().getName().c_str());
	ui->label_current_branch->setText(data::User::getCurrentUser()->getBranch().getName().c_str());
	ui->label_current_location->setText(data::User::getCurrentUser()->getBranch().getLocation().getAddress().c_str());
}

void Org::updateLWBranches() {

	std::vector<data::Branch> bv;
	std::string select, from ,where, query;
	select = "*";
	from = "branches";
	where = "organizationid = '" + data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getId() + "' AND active";
	db::PSQL::getInstance()->get(&select, &from, &where, &bv);
	data::User::getCurrentUser()->setBranchVec(&bv);

	ui->lw_branches->clear();

	for (auto i : data::User::getCurrentUser()->getBranchVec()) {
			QString label = QString ( (i.getCode() + " : " + i.getEmail().getText()).c_str() );
			ui->lw_branches->addItem(label);
		}
}

void Org::on_tabWidget_3_currentChanged(int index)
{
	if (index == 0) {
			updateLWBranches();
		}
}

void Org::on_tabWidget_org_and_branch_currentChanged(int index)
{
	if (index == 1) {
			updateLWBranches();
		}
}

