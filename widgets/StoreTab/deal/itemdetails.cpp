#include "itemdetails.h"
#include "ui_itemdetails.h"

ItemDetails::ItemDetails(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ItemDetails)
{
	ui->setupUi(this);
	ac = new AttributesClass();
	this->ui->v_layout->addWidget(this->ac);

	this->ui->sb_discount->installEventFilter(new DisableMouseScroll());
	this->ui->sb_price->installEventFilter(new DisableMouseScroll());
	this->ui->sb_quantity->installEventFilter(new DisableMouseScroll());

}

ItemDetails::~ItemDetails()
{
	delete ui;
}

QString ItemDetails::getSerial() { return this->ui->le_serial->text(); }
QString ItemDetails::getPrice() { return this->ui->sb_price->text(); }
QString ItemDetails::getDiscount() { return this->ui->sb_discount->text(); }
QString ItemDetails::getColour() { return this->ui->le_colour->text(); }
QString ItemDetails::getQuantity() { return this->ui->sb_quantity->text(); }
QString ItemDetails::getAttributes() {return this->ac->getAttributes();}

void ItemDetails::on_btn_conf_serial_clicked()
{
		if (this->getSerial().isEmpty()) return;
		std::string select, from , where;
		std::vector<data::Inventory> iv;
		select= "*";
		from = "inventory";
		where = "serial = '" + this->getSerial().toStdString() + "'";
		db::PSQL::getInstance()->get(&select, &from, &where, &iv);
		if (iv.size() < 1) return;
		this->ac->setAttributes(iv.at(0).getAttributes().c_str());
		this->ui->sb_price->setValue(iv.at(0).getPrice() + (iv.at(0).getPrice() * 10 / 100) );

}
