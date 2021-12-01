#include "updateproduct.h"
#include "ui_updateproduct.h"

UpdateProduct::UpdateProduct(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UpdateProduct)
{
	ui->setupUi(this);
}

UpdateProduct::~UpdateProduct()
{
	delete ui;
}

void UpdateProduct::on_le_update_serial_returnPressed()
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

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


void UpdateProduct::on_btn_update_item_clicked()
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	std::string query;
	query = "UPDATE inventory SET branchid = '" + data::User::getCurrentUser()->getBranchVec().at(ui->cb_update_branch->currentIndex()).getId() + "', price = " + ui->sb_update_price->text().toStdString() + " WHERE serial = '" + ui->le_update_serial->text().toStdString() + "'";

	if (db::PSQL::getInstance()->set(&query).empty()) {
			ui->le_update_serial->clear();
			ui->sb_update_price->clear();
		}
}

