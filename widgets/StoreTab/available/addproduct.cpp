#include "addproduct.h"
#include "ui_addproduct.h"

AddProduct::AddProduct(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddProduct)
{
	ui->setupUi(this);

	ui->cb_add_item_branch->addItems(data::User::getCurrentUser()->getBranchesNamesList() );

}

AddProduct::~AddProduct()
{
	delete ui;
}

void AddProduct::on_btn_add_inventory_clicked()
{
	std::string select, from, where, query;
	QString itemType, name, modal, manufacturer, vendor, serial, version, price;
	itemType = ui->cb_item_type->currentText();
	name = ui->le_item_name->text();
	modal = ui->le_modal->text();
	manufacturer = ui->le_manufecturer->text();
	vendor = ui->le_vendor->text();
	serial = ui->le_serial->text();
	price = ui->sb_price->text();
	version = ui->le_version->text();

	query = "INSERT INTO items"
					"(name, company, itemtype, modal, version, vendor)"
					" SELECT '" + name.toStdString() + "','" + manufacturer.toStdString() + "','" + itemType.toStdString() + "','" +modal.toStdString() + "','" + version.toStdString() + "','" + vendor.toStdString() + "' WHERE NOT EXISTS ( SELECT name, company, itemtype, modal, version, vendor FROM items WHERE name = '" + name.toStdString() + "' AND COMPANY = '" + manufacturer.toStdString() + "' AND itemtype = '" + itemType.toStdString() + "' AND modal = '" + modal.toStdString() + "' AND version = '" + version.toStdString() + "' AND vendor = '" + vendor.toStdString() + "')";

	db::PSQL::getInstance()->set(&query);

	select = "*";
	from = "items";
	where = "itemtype = '" + itemType.toStdString() +"' AND company ='" + manufacturer.toStdString() + "' AND name ='" + name.toStdString() + "' AND modal ='" + modal.toStdString() + "' AND vendor ='" + vendor.toStdString() + "' AND version ='" + version.toStdString() +"'";

	std::vector<data::Item> iv;
	db::PSQL::getInstance()->get(&select, &from, &where, &iv);

	query = "INSERT INTO inventory(itemid, serial, branchid, price) values ( '"+iv.at(0).getId()+"','"+serial.toStdString()+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_add_item_branch->currentIndex()).getId()+"'," +price.toStdString()+")" ;

	std::string err = db::PSQL::getInstance()->set(&query);

	if (err.length()) {
			ui->le_serial->setStyleSheet("color: #f00");
			return;
		}
	ui->le_serial->setStyleSheet("");
	ui->cb_item_type->setCurrentIndex(0);
	ui->le_item_name->clear();
	ui->le_modal->clear();
	ui->le_manufecturer->clear();
	ui->le_vendor->clear();
	ui->le_serial->clear();
	ui->sb_price->clear();
	ui->le_version->clear();




}

void AddProduct::on_btn_generate_uuid_clicked()
{

	QUuid uid = QUuid::createUuid();
	//0 default for uuid enclosed in curly braces with dashes 1 for with dashes without curly braces and 3 for without dashes as well this 3rd cannot be reused with QUuid class
	ui->le_serial->setVisible(true);
	ui->le_serial->setText(uid.toString(QUuid::StringFormat(1)));
}

