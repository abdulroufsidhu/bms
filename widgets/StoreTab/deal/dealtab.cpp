#include "dealtab.h"
#include "ui_dealtab.h"

DealTab::DealTab(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DealTab)
{
	ui->setupUi(this);
	ui->tab_widget_deals->tabBar()->setStyle(new CustomTabStyle);
	ui->tab_widget_deals->tabBar()->setStyleSheet("background-color: transparent");
	ui->tab_widget_deals->addTab(new Sell(), "SELL");
	ui->tab_widget_deals->addTab(new Sell(), "LIST");
}

DealTab::~DealTab()
{
	delete ui;
}
