#include "available.h"
#include "ui_available.h"

Available::Available(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Available)
{
	ui->setupUi(this);
	ui->tab_widget_available->tabBar()->setStyle(new CustomTabStyle);
	ui->tab_widget_available->tabBar()->setStyleSheet("background-color: transparent;");

	if (this->ap == NULL) this->ap = new AddProduct();
	ui->add_layout->addWidget(this->ap);
	if (this->la == NULL) this->la = new ListAvailable();
	ui->list_layout->addWidget(this->la);
	if (this->up == NULL) this->up = new UpdateProduct();
	ui->update_layout->addWidget(this->up);

}

Available::~Available()
{
	delete ui;
}

void Available::on_tab_widget_available_currentChanged(int index)
{
	switch (index) {
		case 1:
			this->la->updateItemsList();
			break;
		default:
			break;
		}
}

