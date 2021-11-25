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
//	QStringList items ;
	for (short int i = 0 ; i < (short int) data::User::getCurrentUser()->getBranchVec().size() ; i++ ) {
			QString qstr = QString(data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getName().c_str()) + "\t:\t" + QString(data::User::getCurrentUser()->getBranchVec().at(i).getCode().c_str() );
			ui->cb_add_item_branch->addItem(qstr);
			ui->cb_list_branches->addItem(qstr);
//			items.insert(i, QString (data::User::getCurrentUser()->getOrganizationVec().at(data::User::getCurrentUser()->getOrgIndex()).getName().c_str()) + "\t:\t" + QString(data::User::getCurrentUser()->getBranchVec().at(i).getCode().c_str()) );
		}
//	ui->cb_add_item_branch->addItems(items);
//	ui->cb_list_branches->addItems(items);

	this->updateItemsList();

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
	if (index == 1) {
			this->updateItemsList();
		}
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

void Store::on_btn_list_filter_clicked()
{
	std::string where = "";
	if (!ui->le_list_filter->text().isEmpty()) {
			where = ui->cb_list_filter->currentText().toStdString() + " = '" + ui->le_list_filter->text().toStdString() + "'";
		}
	updateItemsList( where);

}

void Store::updateItemsList( std::string where) {
	std::string select, from;
	select = "*";
	from = "items";
	ui->lw_items->clear();
	if (!where.empty()) {
			std::vector<data::Item> iv;
			db::PSQL::getInstance()->get(&select, &from, &where, &iv);
			for (short int i=0; i< (short int) iv.size(); i++) {
					from = "inventory";
					where = "itemid = '" + iv.at(i).getId() + "' AND branchid ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_list_branches->currentIndex()).getId() + "'";
					std::vector<data::Inventory> invVec;
					db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

					for (auto i : invVec) {
							ui->lw_items->addItem( QString( ( i.getItem().getCompany() + " : " + i.getItem().getName() + " : " + i.getItem().getModal() + i.getItem().getVersion() + " : " + i.getItem().getVendor()  ).c_str() ) );
						}

				}
		} else {
			from = "inventory";
			where = " branchid ='" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_list_branches->currentIndex()).getId() + "'";
			std::vector<data::Inventory> invVec;
			db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

			for (auto i : invVec) {
					ui->lw_items->addItem( QString( ( i.getItem().getCompany() + " : " + i.getItem().getName() + " : " + i.getItem().getModal() + i.getItem().getVersion() + " : " + i.getItem().getVendor()  ).c_str() ) );
				}
		}

}


void Store::on_cb_list_branches_currentIndexChanged(const QString &arg1)
{
	this->updateItemsList();
}




void Store::on_le_update_serial_returnPressed()
{
	ui->cb_update_branch->clear();
	ui->sb_price->clear();
	std::vector<data::Inventory> invVec;
	std::string select, from, where;
	select = "*";
	from = "inventory";
	where = "serial ='" + ui->le_update_serial->text().toStdString() + "'";

	db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

	if (invVec.empty()) return;
	int k = 0;
	for (short int i = 0 ; i < (short int) data::User::getCurrentUser()->getBranchVec().size() ; i++) {
			ui->cb_update_branch->addItem( ( data::User::getCurrentUser()->getBranchVec().at(i).getOrganization().getName() + "\t:\t" + data::User::getCurrentUser()->getBranchVec().at(i).getCode() ).c_str() );
			if (invVec.at(0).getBranch().getId() == data::User::getCurrentUser()->getBranchVec().at(i).getId()) {
					k = i;
				}
		}
	ui->cb_update_branch->setCurrentIndex(k);
	ui->sb_update_price->setValue(invVec.at(0).getPrice());

}


void Store::on_btn_update_item_clicked()
{
	std::string query;
	query = "UPDATE inventory SET branchid = '" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_update_branch->currentIndex()).getId() + "', price = " + ui->sb_update_price->text().toStdString() + " WHERE serial = '" + ui->le_update_serial->text().toStdString() + "'";

	if (db::PSQL::getInstance()->set(&query).empty()) {
			ui->le_update_serial->clear();
			ui->sb_update_price->clear();
		}

}

