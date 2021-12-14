#include "attrvalwdgt.h"
#include "ui_attrvalwdgt.h"
#include "../libs/api.h"

AttrValWdgt::AttrValWdgt(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AttrValWdgt)
{
	ui->setupUi(this);
	for (auto i: db::PSQL::getInstance()->getAttribs()) {
		ui->cb_attr->insertItem(0,i.c_str());
	}
	ui->cb_attr->installEventFilter(new DisableMouseScroll());
	ui->cb_attr->setCurrentIndex(0);
}

AttrValWdgt::~AttrValWdgt()
{
	delete ui;
}

void AttrValWdgt::on_cb_attr_currentIndexChanged(const QString &arg1)
{
	this->attr = arg1.toStdString();
	std::vector<std::string> vals;

	std::vector<std::string> attribVec;
	db::PSQL::getInstance()->getVecStr(new std::string("id"), new std::string("attributes"), new std::string("attrib = '"+ this->attr + "'"), &attribVec);

	std::string select, from, where;
	select = "val"; from = "attribval"; where = "attribid ='" + QString(attribVec.at(0).c_str()).toStdString() + "'";
	db::PSQL::getInstance()->getVecStr(&select, &from, &where, &vals);
	ui->cb_val->clear();
	for (int i=0; (int) i< (int) vals.size(); i++) {
		ui->cb_val->insertItem(0, vals.at(i).c_str());
	}
	ui->cb_val->setCurrentIndex(0);
}

void AttrValWdgt::on_cb_val_currentIndexChanged(const QString &arg1)
{
	this->val = arg1.toStdString();
}
