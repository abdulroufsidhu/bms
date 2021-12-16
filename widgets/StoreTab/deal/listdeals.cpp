#include "listdeals.h"
#include "ui_listdeals.h"

#include <QMessageBox>

ListDeals::ListDeals(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ListDeals)
{
	ui->setupUi(this);
}

ListDeals::~ListDeals()
{
	delete ui;
}

void ListDeals::on_btn_search_clicked()
{
	this->ui->listWidget->clear();
	this->dv.clear();
	std::string select = "*", from, where;

	switch (this->ui->cb_column->currentIndex()) {
		case 0: {
			from = "deals"; where = "id = '" + this->ui->le_text->text().toStdString() + "'";
			db::PSQL::getInstance()->get(&select, &from, &where, &this->dv);
			for(auto deal: this->dv) {
				this->ui->listWidget->addItem(deal.getId().c_str());
			}
			break;
		}	case 1: {
			std::string q = "SELECT id FROM contacts WHERE contact = '" + this->ui->le_text->text().toStdString() + "'", id;
			db::PSQL::getInstance()->get(&q,&id);
			q = "SELECT id FROM persons WHERE contactid = '" + id + "'";
			db::PSQL::getInstance()->get(&q,&id);
			from = "deals"; where = "personid = '" + id + "'";
			db::PSQL::getInstance()->get(&select, &from, &where, &dv);
			for(auto deal: dv) {
				this->ui->listWidget->addItem(deal.getId().c_str());
			}
			break;
		} case 2: {
			std::string q = "SELECT id FROM emails WHERE email = '" + this->ui->le_text->text().toStdString() + "'", id;
			db::PSQL::getInstance()->get(&q,&id);
			q = "SELECT id FROM persons WHERE emailid = '" + id + "'";
			db::PSQL::getInstance()->get(&q,&id);
			from = "deals"; where = "personid = '" + id + "'";
			db::PSQL::getInstance()->get(&select, &from, &where, &dv);
			for(auto deal: dv) {
				this->ui->listWidget->addItem(deal.getId().c_str());
			}
			break;
		} case 3: {
			std::string q = "SELECT id FROM cnics WHERE cnic = '" + this->ui->le_text->text().toStdString() + "'", id;
			db::PSQL::getInstance()->get(&q,&id);
			q = "SELECT id FROM persons WHERE cnicid = '" + id + "'";
			db::PSQL::getInstance()->get(&q,&id);
			from = "deals"; where = "personid = '" + id + "'";
			db::PSQL::getInstance()->get(&select, &from, &where, &dv);
			for(auto deal: dv) {
				this->ui->listWidget->addItem(deal.getId().c_str());
			}
			break;
		} case 4: {
			from = "deals"; where = "inventoryid = '" + this->ui->le_text->text().toStdString() + "'";
			db::PSQL::getInstance()->get(&select, &from, &where, &dv);
			for(auto deal: dv) {
				this->ui->listWidget->addItem(deal.getId().c_str());
			}
			break;
		} case 5: {
			from = "items"; where = "name = '" + this->ui->le_text->text().toStdString() + "'";
			std::vector<data::Item> iv;
			db::PSQL::getInstance()->get(&select, &from, &where, &iv);

			if (iv.size()<1) {
				QMessageBox::warning(this, "Warning", "no data found");
				return;
			}

			for (auto item: iv) {
				std::string q = "SELECT id FROM inventory WHERE itemid = '" + item.getId() + "'", id;
				db::PSQL::getInstance()->get(&q, &id);
				from = "deals"; where = "inventoryid = '" + id + "'";
				db::PSQL::getInstance()->get(&select, &from, &where, &dv);

				for (short int i=0; i < (short int) dv.size(); i++) {
					this->ui->listWidget->addItem(dv.at(i).getId().c_str());
				}
			}
		} default:
			break;

	}



}

