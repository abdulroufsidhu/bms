#include "hire.h"
#include "ui_hire.h"

#include <QMessageBox>

Hire::Hire(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Hire)
{
	ui->setupUi(this);

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	data::User::getCurrentUser()->updateBranchesNamesList();
	ui->cb_branch->addItems(data::User::getCurrentUser()->getBranchesNamesList());

}

Hire::~Hire()
{
	delete ui;
}

void Hire::on_btn_hire_clicked()
{
	QString name, email, cnic, phone, country, city, address, jobTitle, grade, salary;
	name = ui->le_name->text();
	email = ui->le_email->text();
	cnic = ui->le_cnic->text();
	phone = ui->le_phone->text();
	country = ui->le_country->text();
	city = ui->le_address->text();
	address = ui->le_address->text();
	jobTitle = ui->le_job->text();
	grade = ui->sb_grade->text();
	salary = ui->db_salary->text();

	if (name.isEmpty()) { QMessageBox::critical(this, "error", "name is not entered"); return;}
	if (email.isEmpty()) { QMessageBox::critical(this, "error", "email is not entered"); return;}
	if (cnic.isEmpty()) { QMessageBox::critical(this, "error", "cnic is not entered"); return;}
	if (phone.isEmpty()) { QMessageBox::critical(this, "error", "phone is not entered"); return;}
	if (country.isEmpty()) { QMessageBox::critical(this, "error", "country is not entered"); return;}
	if (city.isEmpty()) { QMessageBox::critical(this, "error", "city is not entered"); return;}
	if (address.isEmpty()) { QMessageBox::critical(this, "error", "address is not entered"); return;}
	if (jobTitle.isEmpty()) { QMessageBox::critical(this, "error", "job is not entered"); return;}
	if (grade.isEmpty()) { QMessageBox::critical(this, "error", "grade is not entered"); return;}
	if (salary.isEmpty()) { QMessageBox::critical(this, "error", "salary is not entered"); return;}

	std::vector<data::Email> ev;
	std::vector<data::Contact> cv;
	std::vector<data::CNIC> cnicV;
	std::vector<data::Location> lv;
	std::vector<data::Person> pv;
	std::vector<data::Job> jv;

	std::string query, select, from, where;
	select = "*";
	query = "insert into emails (email) values ('" + email.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);
	query = "insert into contacts (contact) values ('" + phone.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);
	query = "insert into cnics (cnic) values ('" + cnic.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);
	query = "insert into cities (city) values ('" + city.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);
	query = "insert into countries (country) values ('" + country.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);
	query = "insert into jobs (designation, grade) values ('" + jobTitle.toStdString() + "','"+ grade.toStdString() +"')";
	db::PSQL::getInstance()->set(&query);

	select = "*";
	from = "locations";
	where = "city ='"+city.toStdString()+"' and country ='"+country.toStdString()+"' and address = '"+address.toStdString()+"'";

	db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
	if (lv.size() < 1) {
			query = "insert into locations(city, country, address) values ('" + city.toStdString() + "','" + country.toStdString() + "','" + address.toStdString() +"')";
			db::PSQL::getInstance()->set(&query);
			db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
		}
	from = "emails"; where = "email = '" + email.toStdString() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where ,&ev);
	from = "contacts"; where = "contact = '" + phone.toStdString() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where ,&cv);
	from = "cnics"; where = "cnic = '" + cnic.toStdString() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where ,&cnicV);

	query = "insert into persons(emailid, contactid, cnicid, locationid, name) values ('"+ev.at(0).getId()+"','"+cv.at(0).getId()+"','"+cnicV.at(0).getId() + "','" + lv.at(0).getId()+"','" + name.toStdString() + "')";
	db::PSQL::getInstance()->set(&query);

	from = "jobs"; where = "job = '" + jobTitle.toStdString() + "' AND grade = " + grade.toStdString() ;
	db::PSQL::getInstance()->get(&select, &from, &where ,&jv);

	query = "insert into users(personid) values ('" + pv.at(0).getId() + "')";
	db::PSQL::getInstance()->set(&query);

	std::string uid;
	query = "select id from users where personid = '" + pv.at(0).getId() + "')";
	db::PSQL::getInstance()->get(&query,&uid);

	query = "insert into employee (userid, jobid, branchid, salary) values ( '"+uid+"','"+jv.at(0).getId()+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId()+"'," + salary.toStdString() + " )";
	if (db::PSQL::getInstance()->set(&query).empty() ) {
			ui->le_name->clear();
			ui->le_email->clear();
			ui->le_cnic->clear();
			ui->le_phone->clear();
			ui->le_country->clear();
			ui->le_address->clear();
			ui->le_address->clear();
			ui->le_job->clear();
			ui->sb_grade->clear();
			ui->db_salary->clear();
			QMessageBox::information(this, "Employee successfully hired", "Employee successfully hired");
		}

}

