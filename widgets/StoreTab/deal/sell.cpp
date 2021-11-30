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

void Sell::on_btn_plus_clicked()
{
	this->avwQvec.append( new AttrValWdgt());
	ui->v_layout_tab_selectors->addWidget(this->avwQvec.last());
}


void Sell::on_pushButton_clicked()
{
	ui->te_attributes_text->clear();
	ui->te_attributes_text->toHtml();
	QString t = QString("<table>");
	for (auto i : this->avwQvec) {
			t+=( ("<tr> <td>" + i->attr + " :- </td>" + "<td> " + i->val + "</td></tr> ").c_str() );
		}
	t += ("</table>");
	ui->te_attributes_text->textCursor().insertHtml(t);
	ui->tab_widget_attributes->setCurrentIndex(1);
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
	std::string serial = ui->le_serial->text().toStdString();
	std::string price = ui->sb_price->text().toStdString();

	if (name.empty()) { QMessageBox::critical(this,"error","Please enter name"); return;}
	if (email.empty()) { QMessageBox::critical(this,"error","Please enter email");  return;}
	if (cnic.empty()) { QMessageBox::critical(this,"error","Please enter cnic");   return;}
	if (cnic.length() != 13) { QMessageBox::critical(this,"error","Please use 13 digits for cnic");   return;}
	if (contact.empty()) { QMessageBox::critical(this,"error","Please enter contact");  return;}
	if (country.empty()) { QMessageBox::critical(this,"error","Please enter country");  return;}
	if (city.empty()) { QMessageBox::critical(this,"error","Please enter city");  return;}
	if (address.empty()) { QMessageBox::critical(this,"error","Please enter address");  return;}
	if (serial.empty()) { QMessageBox::critical(this,"error","Please enter serial");  return;}
	if (price.empty()) { QMessageBox::critical(this,"error","Please enter price");  return;}

	std::vector<data::Email> e;
	std::vector<data::Contact> c;
	std::vector<data::CNIC> cid;
	std::vector<data::Location> lv;
	std::vector<data::Person> p;
	std::string pass;
	std::string q = "insert into emails(email) values ('" + email +"')";
	db::PSQL::getInstance()->set(&q);
	q = " insert into cnics(cnic) values ('"+ cnic +"')";
	db::PSQL::getInstance()->set(&q);
	q = "insert into contacts (contact) values ('" + contact + "')";
	db::PSQL::getInstance()->set(&q);

	std::string select, from, where;
	select = "*";
	from = "locations";
	where = "city ='"+city+"' and country ='"+country+"' and address = '"+address+"'";

	db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
	if (lv.size() < 1) {
			q = "insert into locations(city, country, address) values ('" + city + "','" + country + "','" + address +"')";

			db::PSQL::getInstance()->set(&q);
			db::PSQL::getInstance()->get(&select, &from, &where ,&lv);
		}

	from = "emails";
	where = "email ='" + email + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &e);

	from = "cnics";
	where = "cnic ='" + cnic + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &cid);

	from = "contacts";
	where = "contact ='" + contact + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &c);

	q = "insert into persons(name,emailid,contactid,cnicid,locationid) values ('"+name+"','"+e.at(0).getId()+"','"+c.at(0).getId()+"','"+cid.at(0).getId()+"','"+lv.at(0).getId()+"')";
	db::PSQL::getInstance()->set(&q);

	from = "persons";
	where = "emailid ='" + e.at(0).getId() + "'";
	db::PSQL::getInstance()->get(&select, &from, &where, &p);

	from = "inventory"; where="serial ='" + serial + "'";
	std::vector<data::Inventory> invVec;
	db::PSQL::getInstance()->get(&select, &from, &where, &invVec);

	q = "UPDATE inventory SET atrributes ='" + ui->te_attributes_text->toPlainText().toStdString() + "', colour ='" + ui->le_colour->text().toStdString() + "' WHERE id = '" + invVec.at(0).getId() + "'";
	db::PSQL::getInstance()->set(&q);


	double profit =  ( ui->sb_price->text().toDouble() - (ui->sb_discount->text().toDouble() * ui->sb_discount->text().toDouble() / 100 ) ) - invVec.at(0).getPrice() ;

	q = "insert into deals (inventoryid, price, discount, personid, userid, branchid, profit) values ( '" + invVec.at(0).getId() + "','" + price + "','" + ui->sb_discount->text().toStdString() + "','" + p.at(0).getId() + "','" + data::User::getCurrentUser()->getId() + "','" + invVec.at(0).getBranch().getId() + "'," + QString::number( profit ).toStdString() + ")";

	if (db::PSQL::getInstance()->set(&q).empty()) {
			ui->le_name->clear();
			ui->le_phone->clear();
			ui->le_cnic->clear();
			ui->le_email->clear();
			ui->le_country->clear();
			ui->le_city->clear();
			ui->le_address->clear();
			ui->le_serial->clear();
			ui->sb_price->clear();
			ui->le_colour->clear();
			ui->sb_discount->clear();
			db::PSQL::clearLayout(ui->v_layout_tab_selectors);
			qDeleteAll(avwQvec);
			avwQvec.clear();
			ui->te_attributes_text->clear();
		}
}

void Sell::on_btn_remove_last_clicked()
{
	delete this->avwQvec.last();
	this->avwQvec.removeLast();
}

