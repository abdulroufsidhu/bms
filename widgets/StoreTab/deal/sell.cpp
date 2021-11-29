#include "sell.h"
#include "ui_sell.h"

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
	for (auto i : this->avwQvec) {
			ui->te_attributes_text->appendPlainText( ( i->attr + "\t\t: " + i->val ).c_str() );
		}
	ui->tab_widget_attributes->setCurrentIndex(1);
}

