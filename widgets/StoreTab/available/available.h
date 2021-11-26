#ifndef AVAILABLE_H
#define AVAILABLE_H

#include <QDialog>
#include "./addproduct.h"
#include "./listavailable.h"
#include "./updateproduct.h"

namespace Ui {
	class Available;
}

class Available : public QDialog
{
	Q_OBJECT

public:
	explicit Available(QWidget *parent = nullptr);
	~Available();

private slots:
	void on_tab_widget_available_currentChanged(int index);

private:
	Ui::Available *ui;
	AddProduct* ap = NULL;
	ListAvailable* la = NULL;
	UpdateProduct* up = NULL;
};

#endif // AVAILABLE_H
