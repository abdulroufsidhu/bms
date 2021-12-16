#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./libs/api.h"
#include "./libs/user.h"
#include "./widgets/home.h"
#include "./widgets/store.h"
#include "./widgets/org.h"
#include "./widgets/personal.h"
#include "./libs/disablemousescroll.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:

	void on_tab_main_currentChanged(int index);

private:
	Ui::MainWindow *ui;
	Home* h = nullptr;
	Store* s = nullptr;
	Org* o = nullptr;
	Personal* p = nullptr;

	QGridLayout *hl;
	QGridLayout *sl;
	QGridLayout *ol;
	QGridLayout *pl;

	QWidget* hw = new QWidget();
	QWidget* sw = new QWidget();
	QWidget* ow = new QWidget();
	QWidget* pw = new QWidget();


};
#endif // MAINWINDOW_H
