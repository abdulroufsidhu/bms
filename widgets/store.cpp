#include "store.h"
#include "ui_store.h"
#include <QTimer>
#include <QUuid>

Store::Store(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Store)
{
	ui->setupUi(this);
	if (data::User::getCurrentUser() == NULL) return;

	data::User::getCurrentUser()->updataBranchVec();
	data::User::getCurrentUser()->updateBranchesNamesList();

	available = new Available ();
	ui->layout_avaiability->addWidget(available);
	ui->layout_deals->addWidget(new DealTab());

}

Store::~Store()
{
	delete ui;
}

