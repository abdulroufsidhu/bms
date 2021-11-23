#include "store.h"
#include "ui_store.h"
#include "../libs/user.h"
#include "../libs/item.h"
#include "../libs/inventory.h"
#include <QUuid>

Store::Store(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Store)
{
	data::User::getCurrentUser()->updataBranchVec();
	ui->setupUi(this);
	ui->cb_add_item_branch->clear();
	QStringList items ;
	for (unsigned long i = 0 ; i < data::User::getCurrentUser()->getBranchVec().size() ; i++ ) {
			items.insert(i, QString (data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getName().c_str()) + "\t:\t" + QString(data::User::getCurrentUser()->getBranchVec().at(i).getCode().c_str()) );
		}
	ui->cb_add_item_branch->addItems(items);
}

Store::~Store()
{
	//    QMessageBox::information(this,"destroying", "store destroyed");
	delete ui;
}

void Store::on_btn_generate_uuid_clicked()
{
	QUuid uid = QUuid::createUuid();
	//0 default for uuid enclosed in curly braces with dashes 1 for with dashes without curly braces and 3 for without dashes as well this 3rd cannot be reused with QUuid class
	ui->le_serial->setVisible(true);
	ui->le_serial->setText(uid.toString(QUuid::StringFormat(1)));
}


void Store::on_tabWidget_currentChanged(int index)
{
	if (index == 1) { return; }
}


void Store::on_btn_add_inventory_clicked()
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
					" SELECT '" + name.toStdString() + "'"
								",'" + manufacturer.toStdString() + "'"
								 ",'" + itemType.toStdString() + "'"
								 ",'" +modal.toStdString() + "'"
								 ",'" + version.toStdString() + "'"
								 ",'" + vendor.toStdString() + "'"
												" WHERE "
															"NOT EXISTS ( "
																					"SELECT name"
																							", company"
																							", itemtype"
																							 ", modal"
																							 ", version"
																							 ", vendor"
																							 " FROM items "
																					 "WHERE name = '" + name.toStdString() + "'"
																				 " AND COMPANY = '" + manufacturer.toStdString() + "'"
																				 " AND itemtype = '" + itemType.toStdString() + "'"
																				 " AND modal = '" + modal.toStdString() + "'"
																				 " AND version = '" + version.toStdString() + "'"
																				 " AND vendor = '" + vendor.toStdString() + "'"
")";

	db::PSQL::getInstance()->set(&query);

	select = "*";
	from = "items";
	where = "itemtype = '" + itemType.toStdString() +"' AND company ='" + manufacturer.toStdString() + "' AND name ='" + name.toStdString() + "' AND modal ='" + modal.toStdString() + "' AND vendor ='" + vendor.toStdString() + "' AND version ='" + version.toStdString() +"'";

	//	QMessageBox::information(this,"query", QString(("select " + select + " from " + from + " where " + where).c_str()));

	std::vector<data::Item> iv;
	db::PSQL::getInstance()->get(&select, &from, &where, &iv);
	//	QMessageBox::information(this,"item", iv.at(0).getId().c_str());

	//	query = "INSERT INTO inventory(itemid, serial, branchid, price) values ( '"+iv.at(0).getId()+"','"+serial.toStdString()+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_add_item_branch->currentIndex()).getId()+"'," +price.toStdString()+") ON CONFLICT (serial) DO UPDATE set price = " + price.toStdString() + " , branchid = '"+ data::User::getCurrentUser()->getBranchVec().at(ui->cb_add_item_branch->currentIndex()).getId() +"'";

	query = "INSERT INTO inventory(itemid, serial, branchid, price) values ( '"+iv.at(0).getId()+"','"+serial.toStdString()+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_add_item_branch->currentIndex()).getId()+"'," +price.toStdString()+")" ;

	//	QMessageBox::information(this,"query", QString((query).c_str()));

	db::PSQL::getInstance()->set(&query);

}


void Store::on_btn_list_filter_clicked()
{
	std::string select, from, where;
	select = "*";
	from = "items";
	where = ui->cb_list_filter->currentText().toStdString() + " = '" + ui->le_list_filter->text().toStdString() + "'";

	std::vector<data::Item> iv;
	db::PSQL::getInstance()->get(&select, &from, &where, &iv);

	ui->lw_items->clear();
	for (short int i=0; i< (short int) iv.size(); i++) {
			QMessageBox::information(this, QString(i) ,iv.at(i).getId().c_str());
			from = "inventory";
			where = "itemid = '" + iv.at(i).getId() + "'";
			std::vector<data::Inventory> invVec;
			db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

			for (auto i : invVec) {
					ui->lw_items->addItem( QString( ( i.getItem().getCompany() + " : " + i.getItem().getName() + " : " + i.getItem().getModal() + i.getItem().getVersion() + " : " + i.getItem().getVendor()  ).c_str() ) );
				}

		}


}

