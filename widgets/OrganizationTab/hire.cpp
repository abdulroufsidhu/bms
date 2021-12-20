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

	ui->cb_branch->installEventFilter(new DisableMouseScroll());
	ui->sb_grade->installEventFilter(new DisableMouseScroll());
	ui->db_salary->installEventFilter(new DisableMouseScroll());

}

Hire::~Hire()
{
	delete ui;
}

void Hire::on_btn_hire_clicked()
{

//	try {


		QString name, email, cnic, phone, country, city, address, jobTitle, grade, salary, password;
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
		password = ui->le_password->text();

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
		if (password.isEmpty()) { QMessageBox::critical(this, "error", "password is not entered"); return;}

		std::string query, select, from, where, personid, jobid, locationid, cnicid, contactid, emailid, uid;
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

		query = "INSERT INTO locations (city, country, address) SELECT \
							'" + city.toStdString() + "','" + country.toStdString() + "','" + address.toStdString() + "' \
							 WHERE NOT EXISTS ( SELECT * FROM locations \
										WHERE city = '"+ city.toStdString() +"' AND \
													country = '" + country.toStdString() + "' AND \
													address = '"+address.toStdString()+"' \
										)";
		db::PSQL::getInstance()->set(&query);

		qDebug() << "LOCATION ID IS:";
		query = "SELECT id FROM locations WHERE city = '"+ city.toStdString() +"' AND country = '" + country.toStdString() + "' AND address = '"+address.toStdString()+"'";
		db::PSQL::getInstance()->get(&query,&locationid);

		query = "SELECT id FROM emails WHERE email ='" + email.toStdString() + "'";
		db::PSQL::getInstance()->get(&query, &emailid);

		query = "SELECT id FROM contacts WHERE contact ='" + phone.toStdString() + "'";
		db::PSQL::getInstance()->get(&query, &contactid);

		query = "SELECT id FROM cnics WHERE cnic ='" + cnic.toStdString() + "'";
		db::PSQL::getInstance()->get(&query, &cnicid);

		query = "insert into persons(emailid, contactid, cnicid, locationid, name) values ('"+emailid+"','"+contactid+"','"+ cnicid + "','" + locationid +"','" + name.toStdString() + "')";
		if (!db::PSQL::getInstance()->set(&query).empty()) qDebug() << "unable to add person";

		query = "SELECT id FROM persons where contactid ='" + contactid + "'";
		db::PSQL::getInstance()->get(&query, &personid);

		query = "SELECT id FROM jobs WHERE designation ='" + jobTitle.toStdString() + "'" ;
		db::PSQL::getInstance()->get(&query, &jobid);

		query = "insert into users(personid) values ('" + personid + "')";
		db::PSQL::getInstance()->set(&query);

		query = "select id from users where personid = '" + personid + "'";
		db::PSQL::getInstance()->get(&query,&uid);

		query = "insert into auth(password, emailid) values ('" + password.toStdString() + "','" + emailid + "')";
		db::PSQL::getInstance()->set(&query);

		query = "insert into employee (userid, jobid, branchid, salary) values ( '"+uid+"','"+jobid+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId()+"'," + salary.toStdString() + " )";

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


//	}  catch (std::exception &e) {
//		qDebug() << e.what();
//	}

}

