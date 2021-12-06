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
	ui->cb_branch_list->clear();
	ui->cb_branch_list->addItems(data::User::getCurrentUser()->getBranchesNamesList());
	ui->cb_branches_remove_attr->clear();
	ui->cb_branches_remove_attr->addItems(data::User::getCurrentUser()->getBranchesNamesList());
	ui->cb_branches_remove_attr_val->clear();
	ui->cb_branches_remove_attr_val->addItems(data::User::getCurrentUser()->getBranchesNamesList());
	ui->cb_branch_add_attribs->clear();
	ui->cb_branch_add_attribs->addItems(data::User::getCurrentUser()->getBranchesNamesList());
	this->updateCBattribAddVal();
}

void Home::updateCBattribAddVal() {
	db::PSQL::getInstance()->updateAttribs(&data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch_add_attribs->currentIndex()).getId());
	ui->cb_attrib_add_val->clear();
	ui->cb_attrib_remove_val->clear();
	for (auto i : db::PSQL::getInstance()->getAttribs()) {
		ui->cb_attrib_add_val->addItem(i.c_str());
		ui->cb_attrib_remove_val->addItem(i.c_str());
	}
}

Home::~Home() { delete ui; }

void Home::on_btn_add_attrib_clicked()
{
	std::string query = "insert into attributes(attrib) values ('" + ui->le_add_attrib->text().toStdString() + "')";
	ui->le_add_attrib->setStyleSheet("");
	if (db::PSQL::getInstance()->set(&query).empty()) {
		ui->le_add_attrib->clear();
	}	else {
		ui->le_add_attrib->setStyleSheet("color: #F00");
	}
	this->on_btn_attrib_add_val_clicked(ui->le_add_attrib->text().toStdString());
	this->updateCBattribAddVal();
}

void Home::on_btn_attrib_add_val_clicked(std::string attrib)
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	QString val = ui->le_attrib_add_val->text();
	if (val.isEmpty()) val = " Choose Your Value Sire";

	QMessageBox::information(this, "attrib", attrib.c_str());
	if (attrib.empty()){ attrib = ui->cb_attrib_add_val->currentText().toStdString(); }

	std::string query, attribid;
	query = "SELECT id FROM attributes WHERE attrib ='" + attrib + "'";
	db::PSQL::getInstance()->get(&query, &attribid);

//	db::PSQL::getInstance()->getVecStr(new std::string("id"), new std::string("attributes"), new std::string("attrib = '"+ attrib + "'"), &attribVec);

	//	query = "insert into attribval(attribid, val, branchid) values ('" + attribVec.at(0) + "','" + ui->le_attrib_add_val->text().toStdString() + "','" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "')";

	query = "INSERT INTO attribval (attribid, val, branchid) SELECT '" + attribid + "','" + val.toStdString() + "','" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "' WHERE NOT EXISTS (SELECT attribid, val, branchid FROM attribval WHERE attribid='" + attribid + "' AND val ='" + val.toStdString() + "' AND branchid ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branch->currentIndex()).getId() + "')";

	db::PSQL::getInstance()->set(&query);
	ui->le_attrib_add_val->clear();
}


void Home::on_cb_branch_list_currentIndexChanged(int index)
{
	std::string p, q;
//	select = "profit"; from = "reports"; where = "branchid = '" + data::User::getCurrentUser()->getBranchVec().at(index).getId() + "' and to_char(time,'yyyymm') = to_char(CURRENT_DATE,'yyyymm') ";
	q = "SELECT profit FROM reports WHERE branchid ='" + data::User::getCurrentUser()->getBranchVec().at(index).getId() + "' and to_char(time,'yyyymm') = to_char(CURRENT_DATE,'yyyymm') ";
	db::PSQL::getInstance()->get(&q, &p);
	ui->label_profit->setText(p.c_str());
}


void Home::on_btn_remove_attrib_clicked()
{
	std::string q, attr;
	q = "SELECT id FROM attributes WHERE attrib = '" + ui->le_remove_attrib->text().toStdString() + "'";
	db::PSQL::getInstance()->get(&q, &attr);
	q = "DELETE * FROM attribval WHERE attribid = '" + attr + "' AND branchid = '" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branches_remove_attr->currentIndex()).getId() + "'";
	this->updateCBattribAddVal();
}


void Home::on_btn_attrib_remove_val_clicked()
{
	std::string q, attr;
	q = "SELECT id FROM attributes WHERE attrib = '" + ui->le_remove_attrib->text().toStdString() + "'";
	db::PSQL::getInstance()->get(&q, &attr);
	q = "DELETE * FROM attribval WHERE attribid = '" + attr + "' AND branchid = '" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_branches_remove_attr_val->currentIndex()).getId() + "' AND val ='" + ui->le_attrib_remove_val->text().toStdString() + "'";
	this->updateCBattribAddVal();
}

