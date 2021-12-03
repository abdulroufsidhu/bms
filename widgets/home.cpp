#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Home)
{
	ui->setupUi(this);

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	data::User::getCurrentUser()->updataBranchVec();
	data::User::getCurrentUser()->updateBranchesNamesList();
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

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	std::string query;
	std::vector<std::string> attribVec;
	db::PSQL::getInstance()->getVecStr(new std::string("id"), new std::string("attributes"), new std::string("attrib = '"+ ui->cb_attrib_add_val->currentText().toStdString() + "'"), &attribVec);
//	query = "insert into attribval(attribid, val, branchid) values ('" + attribVec.at(0) + "','" + ui->le_attrib_add_val->text().toStdString() + "','" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "')";
	query = "INSERT INTO attribval (attribid, val, branchid) SELECT '" + attribVec.at(0) + "','" + ui->le_attrib_add_val->text().toStdString() + "','" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "' WHERE NOT EXISTS (SELECT attribid, val, branchid FROM attribval WHERE attribid='" + attribVec.at(0) + "' AND val ='" + ui->le_attrib_add_val->text().toStdString() + "' AND branchid ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "')";

	db::PSQL::getInstance()->set(&query);
	ui->le_attrib_add_val->clear();
}


void Home::on_cb_branch_list_currentIndexChanged(int index)
{
	std::vector<std::string> pv;
	std::string select, from, where;
	select = "profit"; from = "reports"; where = "branchid = '" + data::User::getCurrentUser()->getBranchVec().at(index).getId() + "' and to_char(time,'yyyymm') = to_char(CURRENT_DATE,'yyyymm') ";
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &pv);
	ui->label_profit->setText(pv.at(0).c_str());
}

