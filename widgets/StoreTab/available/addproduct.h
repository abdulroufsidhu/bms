#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QUuid>
#include <QDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include "../../../libs/api.h"
#include "../../../libs/item.h"
#include "../../../libs/inventory.h"
#include "../../../libs/user.h"
#include "../attributesclass.h"
#include "../../../libs/barcodegenerator.h"

namespace Ui {
	class AddProduct;
}

class AddProduct : public QDialog
{
	Q_OBJECT

public:
	explicit AddProduct(QWidget *parent = nullptr);
	~AddProduct();

private slots:
	void on_btn_add_inventory_clicked();

	void on_btn_generate_uuid_clicked();

	void on_pushButton_clicked();

private:
	Ui::AddProduct *ui;
	AttributesClass* ac;
};

#endif // ADDPRODUCT_H
