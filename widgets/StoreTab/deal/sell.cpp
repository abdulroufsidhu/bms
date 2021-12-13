#include "sell.h"
#include "ui_sell.h"
#include "../../../libs/deal.h"

Sell::Sell(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Sell)
{
	ui->setupUi(this);
}

Sell::~Sell()
{
	delete ui;
}

void Sell::on_btn_sell_clicked()
{
	std::string name = ui->le_name->text().toStdString();
	std::string contact = ui->le_phone->text().toStdString();
	std::string cnic = ui->le_cnic->text().toStdString();
	std::string email = ui->le_email->text().toStdString();
	std::string country = ui->le_country->text().toStdString();
	std::string city = ui->le_city->text().toStdString();
	std::string address = ui->le_address->text().toStdString();
	//	std::string serial = ui->le_serial->text().toStdString();
	//	std::string price = ui->sb_price->text().toStdString();

	std::string select, from, where;

	if (name.empty()) { QMessageBox::critical(this,"error","Please enter name"); return;}
	//	if (email.empty()) { QMessageBox::critical(this,"error","Please enter email");  return;}
	//	if (cnic.empty()) { QMessageBox::critical(this,"error","Please enter cnic");   return;}
	//	if (cnic.length() != 13) { QMessageBox::critical(this,"error","Please use 13 digits for cnic");   return;}
	if (contact.empty()) { QMessageBox::critical(this,"error","Please enter contact");  return;}
	if (country.empty()) { QMessageBox::critical(this,"error","Please enter country");  return;}
	if (city.empty()) { QMessageBox::critical(this,"error","Please enter city");  return;}
	if (address.empty()) { QMessageBox::critical(this,"error","Please enter address");  return;}
	//	if (serial.empty()) { QMessageBox::critical(this,"error","Please enter serial");  return;}
	//	if (price.empty()) { QMessageBox::critical(this,"error","Please enter price");  return;}
	//	if (ui->te_attributes_text->toPlainText().isEmpty()) {QMessageBox::critical(this,"error","Please make sure attributes are written in the text box");  return;}

	for (auto item: iDetQvec) {
		if (item->getSerial().isEmpty()) { QMessageBox::critical(this,"error","Please enter serial");  return;}
		if (item->getPrice().isEmpty()) {QMessageBox::critical(this,"error","Please enter price");  return;}
		if (item->getAttributes().isEmpty()) { QMessageBox::critical(this,"error","Please make sure attributes for serial " + item->getSerial() + " are written in the text box");  return;}

	}

	for (auto item : iDetQvec) {
		select = "*";
		from = "inventory"; where="serial ='" + item->getSerial().toStdString() + "' and quantity > 0";
		std::vector<data::Inventory> invVec;
		db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

		if (invVec.size() < 1) { QMessageBox::critical(this, "ERROR", "Item does not exist."); return; }

		if (invVec.at(0).getQuantity() < item->getQuantity().toInt()) { QMessageBox::critical(this, "ERROR", "Quantity for " + item->getSerial() + " does not exist."); return; }


		std::string cnicId, contactId, emailId, personId, locationId, pass;

		std::string q = "insert into emails(email) values ('" + email +"')";
		db::PSQL::getInstance()->set(&q);
		q = " insert into cnics(cnic) values ('"+ cnic +"')";
		db::PSQL::getInstance()->set(&q);
		q = "insert into contacts (contact) values ('" + contact + "')";
		db::PSQL::getInstance()->set(&q);

		from = "locations";
		where = "city ='"+city+"' and country ='"+country+"' and address = '"+address+"'";

		//		db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
		q = "SELECT id FROM locations WHERE city = '" + city + "' AND country = '"+country+"' and address = '"+address+"'";
		db::PSQL::getInstance()->get(&q, &locationId);
		if (locationId.empty()) {
			q = "insert into locations(city, country, address) values ('" + city + "','" + country + "','" + address +"')";
			db::PSQL::getInstance()->set(&q);

			q = "SELECT id FROM locations WHERE city = '" + city + "' AND country = '"+country+"' and address = '"+address+"'";
			db::PSQL::getInstance()->get(&q, &locationId);
		}

		q = "SELECT id FROM emails WHERE email = '" + email + "'";
		db::PSQL::getInstance()->get(&q, &emailId);

		q = "SELECT id FROM cnics WHERE cnic = '" + cnic + "'";
		db::PSQL::getInstance()->get(&q, &cnicId);

		q = "SELECT id FROM contacts WHERE contact = '" + contact + "'";
		db::PSQL::getInstance()->get(&q, &contactId);

		if (cnicId.empty()) cnicId = "";
		if (contactId.empty()) return;

		q = "insert into persons(name,emailid,contactid,cnicid,locationid) values ('"+name+"','"+emailId+"','"+contactId+"','"+cnicId+"','"+locationId+"')";
		db::PSQL::getInstance()->set(&q);

		q = "SELECT id FROM persons WHERE emailid = '" + emailId + "'";
		db::PSQL::getInstance()->get(&q, &personId);


		q = "UPDATE inventory SET attributes ='" + item->getAttributes().toStdString() + "', colour ='" + item->getColour().toStdString() + "', quantity = quantity - " + item->getQuantity().toStdString() + " WHERE id = '" + invVec.at(0).getId() + "' AND quantity > 0";
		db::PSQL::getInstance()->set(&q);

		double profit =  (( item->getPrice().toDouble() - (item->getDiscount().toDouble() * item->getPrice().toDouble() / 100 ) ) - invVec.at(0).getPrice() ) * item->getQuantity().toLong();

		q = "insert into deals (inventoryid, price, discount, personid, userid, branchid, profit, quantity) values ( '" + invVec.at(0).getId() + "','" + item->getPrice().toStdString() + "','" + item->getDiscount().toStdString() + "','" + personId + "','" + data::User::getCurrentUser()->getId() + "','" + invVec.at(0).getBranch().getId() + "'," + QString::number( profit ).toStdString() + "," + item->getQuantity().toStdString() + ")";
		db::PSQL::getInstance()->set(&q);

		q = "INSERT INTO reports(profit, branchid) \
				 SELECT " + QString::number(profit).toStdString() + " , \
				 '" + invVec.at(0).getBranch().getId() + "' \
				 WHERE NOT EXISTS (SELECT time FROM reports WHERE to_char(time, 'yyyymm')=to_char(CURRENT_DATE,'yyyymm') ) "	;
		db::PSQL::getInstance()->set(&q);
		q = "UPDATE reports SET \
				 profit = profit + " + QString::number(profit).toStdString() + " \
				 WHERE to_char(time,'yyyymm')=to_char(CURRENT_DATE,'yyyymm') ";
		db::PSQL::getInstance()->set(&q);
	}

	if (iDetQvec.size() > 0) {
		ui->le_name->clear();
		ui->le_phone->clear();
		ui->le_cnic->clear();
		ui->le_email->clear();
		ui->le_address->clear();
		qDeleteAll (iDetQvec);
		iDetQvec.clear();
	}


	//		ui->le_serial->clear();
	//		ui->sb_price->clear();
	//		ui->le_colour->clear();
	//		ui->sb_discount->clear();
	//		db::PSQL::clearLayout(ui->v_layout_tab_selectors);
	//		qDeleteAll(avwQvec);
	//		avwQvec.clear();
	//		ui->te_attributes_text->clear();


}


void Sell::on_pushButton_clicked()
{
	iDetQvec.append(new ItemDetails());
	this->ui->v_layout_item_details->addWidget(iDetQvec.last());
}


void Sell::on_pushButton_2_clicked()
{
	delete this->iDetQvec.last();
	this->iDetQvec.removeLast();
}

