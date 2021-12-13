#include "itemdetails.h"
#include "ui_itemdetails.h"

ItemDetails::ItemDetails(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ItemDetails)
{
	ui->setupUi(this);
}

ItemDetails::~ItemDetails()
{
	delete ui;
}

void ItemDetails::on_btn_plus_clicked()
{
	this->avwQvec.append( new AttrValWdgt());
	ui->v_layout_tab_selectors->addWidget(this->avwQvec.last());
}

void ItemDetails::on_btn_insert_attrib_clicked()
{
	ui->te_attributes_text->clear();
	ui->te_attributes_text->toHtml();
	QString t = QString("<table>");
	for (auto i : this->avwQvec) {
			t+=( ("<tr> <td> " + i->attr + " :- </td>" + "<td> " + i->val + " </td></tr> ").c_str() );
		}
	t += ("</table>");
	ui->te_attributes_text->textCursor().insertHtml(t);
	ui->tab_widget_attributes->setCurrentIndex(1);
}

QString ItemDetails::getSerial() { return this->ui->le_serial->text(); }
QString ItemDetails::getPrice() { return this->ui->sb_price->text(); }
QString ItemDetails::getDiscount() { return this->ui->sb_discount->text(); }
QString ItemDetails::getColour() { return this->ui->le_colour->text(); }
QString ItemDetails::getAttributes() { return this->ui->te_attributes_text->toPlainText(); }
QString ItemDetails::getQuantity() { return this->ui->sb_quantity->text(); }

void ItemDetails::on_btn_remove_last_clicked()
{
	delete this->avwQvec.last();
	this->avwQvec.removeLast();
}

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
		this->ui->te_attributes_text->setPlainText(iv.at(0).getAttributes().c_str());
		this->ui->sb_price->setValue(iv.at(0).getPrice() + (iv.at(0).getPrice() * 10 / 100) );

}
