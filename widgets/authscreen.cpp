#include "authscreen.h"
#include "ui_authscreen.h"

AuthScreen::AuthScreen(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AuthScreen)
{
	ui->setupUi(this);
	ui->layout_login->addWidget(new Login);
	ui->layout_signup->addWidget(new Signup);

	std::string query = "CREATE EXTENSION IF NOT EXISTS \"uuid-ossp\"";
	db::PSQL::getInstance()->set(&query);
	query = " create table contacts (id uuid default uuid_generate_v4() primary key, contact text not null unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table cnics (id uuid default uuid_generate_v4() primary key, cnic text unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table emails (id uuid default uuid_generate_v4() primary key, email text unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table auth (\
							id uuid default uuid_generate_v4() primary key, \
							password text not null, \
							emailid uuid references emails(id) unique, \
							active boolean default true not null\
							)";
	db::PSQL::getInstance()->set(&query);
	query = "create table jobs (id uuid default uuid_generate_v4() primary key, designation text not null unique, grade integer not null)";
	db::PSQL::getInstance()->set(&query);
	query = "create table cities (id uuid default uuid_generate_v4() primary key, city text not null unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table countries (id uuid default uuid_generate_v4() primary key, country text not null unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table locations (id uuid default uuid_generate_v4() primary key, city text, country text, address text unique)";
	db::PSQL::getInstance()->set(&query);
	query = "create table persons (\
					 id uuid default uuid_generate_v4() primary key\
					 , emailid uuid references emails(id)\
					 , contactid uuid references contacts(id) unique\
					 , cnicid uuid references cnics(id)\
					 , locationid uuid references locations(id)\
					 , name text not null, age integer\
					)";
	db::PSQL::getInstance()->set(&query);
	query = "create table organizations (id uuid default uuid_generate_v4() primary key, name text not null, founderid uuid references persons(id) not null, emailid uuid references emails(id) not null unique	, logo BYTEa	, desclaimer text)";
	db::PSQL::getInstance()->set(&query);
	query = "create table branches (\
			id uuid default uuid_generate_v4() primary key\
			, name text not null\
			, code text not null\
			, locationid uuid References locations(id) not null\
			, organizationid uuid not null references organizations (id)\
			, contactid uuid references contacts(id)\
			, emailid uuid references emails(id) not null unique\
			, active boolean not null default true\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table users (\
			id uuid default uuid_generate_v4() primary key\
			, personid uuid references persons(id) unique\
			, active BOOL not null default true\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table employee (\
			id uuid default uuid_generate_v4() primary key\
			, userid uuid references users(id) not null\
			, jobid uuid references jobs(id)\
			, branchid uuid references branches(id)\
			, organizationid uuid references organizations(id)\
			, salary text default '0' not null\
			, active BOOL not null default true\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table items (\
			id uuid default uuid_generate_v4() primary key\
			, itemtype text not null\
			, company text not null\
			, name text not null\
			, modal text not null\
			, version text\
			, vendor text\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table inventory (\
			id uuid default uuid_generate_v4() primary key\
			, itemid uuid references items(id)\
			, attributes text\
			, colour text\
			, serial text unique not null\
			, branchid uuid references branches(id)\
			, quantity numeric not null default 1\
			, price numeric not null\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table deals (\
			id uuid default uuid_generate_v4() primary key\
			, inventoryid uuid references inventory(id)\
			, price numeric not null\
			, discount numeric not null default 0\
			, personid uuid references persons(id) not null\
			, userid uuid references users(id) not null\
			, quantity integer default 1\
			, branchid uuid references branches(id) not null\
			, profit numeric not null\
			, time date not null default CURRENT_DATE	\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table expensis (\
			id uuid default uuid_generate_v4() primary key\
			, branchid uuid references branches(id) not null\
			, reason text not null\
			, expense numeric not null\
			, time date not null default CURRENT_DATE\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table reports (\
			id uuid default uuid_generate_v4() primary key\
			, branchid uuid references branches(id) not null\
			, profit numeric not null default 0\
			, time date not null default CURRENT_DATE\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table attributes (\
			id uuid default uuid_generate_v4() primary key\
			, attrib text not null unique\
			)";
	db::PSQL::getInstance()->set(&query);
	query = "create table attribval (\
			id uuid default uuid_generate_v4() primary key\
			, attribid uuid references attributes(id) not null\
			, val text not null\
			, branchid uuid references branches(id) not null\
			)";
	db::PSQL::getInstance()->set(&query);

}

AuthScreen::~AuthScreen()
{
	delete ui;
}
