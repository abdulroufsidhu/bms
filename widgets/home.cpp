#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Home)
{
	data::User::getCurrentUser()->updataBranchVec();
	data::User::getCurrentUser()->updateBranchesNamesList();
	ui->setupUi(this);
	ui->cb_branch->clear();
	ui->cb_branch->addItems(data::User::getCurrentUser()->getBranchesNamesList());
	this->updateCBattribAddVal();
}

void Home::updateCBattribAddVal() {
	db::PSQL::getInstance()->updateAttribs();
	ui->cb_attrib_add_val->clear();
	for (auto i : db::PSQL::getInstance()->getAttribs()) {
		ui->cb_attrib_add_val->addItem(i.c_str());
	}
}

Home::~Home() { delete ui; }

void Home::on_btn_add_attrib_clicked()
{
	std::string query = "insert into attributes(attrib) values ('" + ui->le_add_attrib->text().toStdString() + "')";
	ui->le_add_attrib->setStyleSheet("color: #F00");
	if (db::PSQL::getInstance()->set(&query).empty()) {
		ui->le_add_attrib->clear();
	}	else {
		ui->le_add_attrib->setStyleSheet("color: #F00");
	}
	this->updateCBattribAddVal();
}

void Home::on_btn_attrib_add_val_clicked()
{
	std::string query;
	std::vector<std::string> attribVec;
	db::PSQL::getInstance()->getVecStr(new std::string("id"), new std::string("attributes"), new std::string("attrib = '"+ ui->cb_attrib_add_val->currentText().toStdString() + "'"), &attribVec);
	query = "insert into attribval(attribid, val, branchid) values ('" + attribVec.at(0) + "','" + ui->le_attrib_add_val->text().toStdString() + "','" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "')";
	db::PSQL::getInstance()->set(&query);
}

