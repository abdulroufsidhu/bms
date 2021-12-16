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
		if (data::User::getCurrentUser()== NULL) return;
		this->h = new Home();
		this->s = new Store();
		this->o = new Org();
		this->p = new Personal();

		this->hl = new QGridLayout(this->hw);
		this->sl = new QGridLayout(this->sw);
		this->ol = new QGridLayout(this->ow);
		this->pl = new QGridLayout(this->pw);

		this->ui->tab_main->addTab(hw, QIcon(":/icons/icons/home-svgrepo-com.svg"), "HOME");
		this->ui->tab_main->addTab(sw, QIcon(":/icons/icons/stock-svgrepo-com.svg"), "STORE");
		this->ui->tab_main->addTab(ow, QIcon(":/icons/icons/organization-administration-svgrepo-com.svg"), "ORGANIZATION");
		this->ui->tab_main->addTab(pw, QIcon(":/icons/icons/person-svgrepo-com.svg"), "PERSONAL");
		this->ui->tab_main->setIconSize(QSize(48,48));
		this->ui->tab_main->tabBar()->installEventFilter(new DisableMouseScroll());
	});

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_tab_main_currentChanged(int index)
{
	switch (index) {
		case 0:
			if (this->hl == nullptr) this->hl = new QGridLayout(this->hw);
			this->hl->addWidget(h);
			delete(this->ol),this->ol = nullptr;
			delete(this->sl),this->sl = nullptr;
			delete(this->pl),this->pl = nullptr;
			break;
		case 1:
			if (this->sl == nullptr) this->sl = new QGridLayout(this->sw);
			this->sl->addWidget(s);
			delete(this->hl),this->hl = nullptr;
			delete(this->ol),this->ol = nullptr;
			delete(this->pl),this->pl = nullptr;
			break;
		case 2:
			if (this->ol == nullptr) this->ol = new QGridLayout(this->ow);
			this->ol->addWidget(o);
			delete(this->sl),this->sl = nullptr;
			delete(this->hl),this->hl = nullptr;
			delete(this->pl),this->pl = nullptr;
			break;
		case 3:
			if (this->pl == nullptr) this->pl = new QGridLayout(this->pw);
			this->pl->addWidget(p);
			delete(this->ol),this->ol = nullptr;
			delete(this->sl),this->sl = nullptr;
			delete(this->hl),this->hl = nullptr;
			break;
		default:
			break;
	}
}

