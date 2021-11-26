#include "store.h"
#include "ui_store.h"
#include "../libs/user.h"
#include "../libs/item.h"
#include "../libs/inventory.h"
#include <QTimer>
#include <QUuid>

Store::Store(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Store)
{
	ui->setupUi(this);

	QTimer::singleShot(10000,this,SLOT(initiate()));

}

void Store::initiate() {

	data::User::getCurrentUser()->updataBranchVec();

	data::User::getCurrentUser()->updateBranchesNamesList();



	this->updateItemsList();

}

Store::~Store()
{
	delete ui;
}

void Store::on_tabWidget_currentChanged(int index)
{
	if (index == 1) {
			this->updateItemsList();
		}
}



void Store::on_btn_list_filter_clicked()
{


}


void Store::on_cb_list_branches_currentIndexChanged(const QString &arg1)
{
	this->updateItemsList();
}




void Store::on_le_update_serial_returnPressed()
{
	ui->cb_update_branch->clear();
	ui->sb_update_price->clear();
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

