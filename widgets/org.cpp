#include "org.h"
#include "ui_org.h"
#include <QMessageBox>
#include <QTabBar>

Org::Org(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Organization)
{   
	ui->setupUi(this);

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	this->orgInfoPage();
	this->updateLWOrg();
	this->updateLWBranches();

}

Org::~Org()
{
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

	if (db::PSQL::getInstance()->set(&query).empty()) {
			ui->le_org_name->setText("");
			ui->le_org_email->setText("");
			QMessageBox::information(this, "success", "successfully registered new organization");
		}

	data::User::getCurrentUser()->updateOrgVecBusiness();

}

void Org::on_btn_relocate_clicked()
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	std::string query, select, from, where;
	query = "insert into locations (address) values ('" + ui->le_branch_new_address->text().toStdString() + "')";
	select = "*";
	from = "locations";
	where = "address= '"+ui->le_branch_new_address->text().toStdString()+"'";
	db::PSQL::getInstance()->set(&query);
	std::vector<data::Location> lv;
	db::PSQL::getInstance()->get(&select, &from, &where, &lv);
	query = "UPDATE branches SET locationid ='" + lv.at(0).getId() + "' WHERE id ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_manage_branch_relocate->currentIndex()).getId() + "'";
	db::PSQL::getInstance()->set(&query);
}

void Org::on_btn_revoke_clicked()
{
	std::string query = "UPDATE branches SET active = false WHERE id ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch_revoke->currentIndex()).getId() + "'";
	db::PSQL::getInstance()->set(&query);
}

void Org::on_btn_add_branch_clicked()
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

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

	if (db::PSQL::getInstance()->set(&query).empty()) {
			ui->le_add_branch_name->setText("");
			ui->le_add_brannch_code->setText("");
			ui->le_add_branch_country->setText("");
			ui->le_add_branch_city->setText("");
			ui->le_add_branch_address->setText("");
			ui->le_add_branch_contact->setText("");
			ui->le_add_branch_email->setText("");
			QMessageBox::information(this, "success", "successfully added new Branch");
			data::User::getCurrentUser()->updataBranchVec();
			data::User::getCurrentUser()->updateBranchesNamesList();
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

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	ui->lw_organizations->clear();
	for (auto i : data::User::getCurrentUser()->getOrganizationVec()) {
			QString str = QString( (i.getName() + " : " + i.getEmail().getText() ).c_str());
			ui->lw_organizations->addItem(str);
		}
}

void Org::on_lw_organizations_doubleClicked(const QModelIndex &index)
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	data::User::getCurrentUser()->setOrgIndex(index.row());
	QMessageBox::information(this, "current organization changed", "current organization changed to " + QString(data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getEmail().getText().c_str() ) );

	data::User::getCurrentUser()->updateBranchesNamesList();

}


void Org::on_tabWidget_currentChanged(int index)
{
	if (index==0) {
			orgInfoPage();
		}
}

void Org::orgInfoPage() {

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	QTimer::singleShot(100, this, [=] () {
			int index = data::User::getCurrentUser()->getOrgIndex();
			ui->tabWidget_org_and_branch->tabBar()->setStyle(new CustomTabStyle);
			ui->label_org_name->setText(data::User::getCurrentUser()->getOrganizationVec().at(index).getName().c_str());
			ui->label_organization_founder->setText(data::User::getCurrentUser()->getOrganizationVec().at(index).getPerson().getName().c_str());
			ui->label_current_branch->setText(data::User::getCurrentUser()->getBranch().getName().c_str());
			ui->label_current_location->setText(data::User::getCurrentUser()->getBranch().getLocation().getAddress().c_str());
		});
}

void Org::updateLWBranches() {

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	ui->lw_branches->clear();
	for (auto i : data::User::getCurrentUser()->getBranchVec()) {
			QString label = QString ( (i.getCode() + " : " + i.getEmail().getText()).c_str() );
			ui->lw_branches->addItem(label);
		}
}

void Org::on_tabWidget_org_and_branch_currentChanged(int index)
{
	if (index == 1) {
			this->updateLWBranches();
			ui->cb_manage_branch_relocate->clear();
			ui->cb_branch_revoke->clear();
			ui->cb_manage_branch_relocate->addItems(data::User::getCurrentUser()->getBranchesNamesList());
			ui->cb_branch_revoke->addItems(data::User::getCurrentUser()->getBranchesNamesList());
		}
}


void Org::on_lw_branches_doubleClicked(const QModelIndex &index)
{
	data::User::getCurrentUser()->setBranchIndex(index.row());
}

