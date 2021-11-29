#include "store.h"
#include "ui_store.h"
#include <QTimer>
#include <QUuid>

Store::Store(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Store)
{
	ui->setupUi(this);

	data::User::getCurrentUser()->updataBranchVec();
	data::User::getCurrentUser()->updateBranchesNamesList();

	available = new Available ();
	ui->layout_avaiability->addWidget(available);
	ui->layout_deals->addWidget(new Sell());

}

Store::~Store()
{
	delete ui;
}

