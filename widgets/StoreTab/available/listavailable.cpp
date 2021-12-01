#include "listavailable.h"
#include "ui_listavailable.h"

ListAvailable::ListAvailable(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ListAvailable)
{
	ui->setupUi(this);

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;
	ui->cb_list_branches->addItems(data::User::getCurrentUser()->getBranchesNamesList() );

}

ListAvailable::~ListAvailable()
{
	delete ui;
}

void ListAvailable::on_btn_list_filter_clicked()
{
	std::string where = "";
	if (!ui->le_list_filter->text().isEmpty()) {
			where = ui->cb_list_filter->currentText().toStdString() + " = '" + ui->le_list_filter->text().toStdString() + "'";
		}
	updateItemsList( where);
}

void ListAvailable::on_cb_list_branches_currentIndexChanged(int index)
{
		this->updateItemsList();
}

void ListAvailable::updateItemsList( std::string where) {

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

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



