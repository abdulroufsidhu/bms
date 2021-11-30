#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
//	data::User::getCurrentUser()->updataBranchVec();

	ui->tab_main->tabBar()->setStyle(new CustomTabStyle);
	QString tabbarStylesheet = " background-color: transparent; ";
	ui->tab_main->tabBar()->setStyleSheet(tabbarStylesheet);

	QTimer::singleShot(3000,this, [=]() {
			ui->tab_main->addTab(new Home(), QIcon(":/icons/icons/home-svgrepo-com.svg"), "HOME");
			ui->tab_main->addTab(new Store(), QIcon(":/icons/icons/stock-svgrepo-com.svg"), "STORE");
			ui->tab_main->addTab(new Org(), QIcon(":/icons/icons/organization-administration-svgrepo-com.svg"), "ORGANIZATION");
			ui->tab_main->addTab(new Personal(), QIcon(":/icons/icons/person-svgrepo-com.svg"), "PERSONAL");
			ui->tab_main->setIconSize(QSize(48,48));
		});

}

MainWindow::~MainWindow()
{
	delete ui;
}

