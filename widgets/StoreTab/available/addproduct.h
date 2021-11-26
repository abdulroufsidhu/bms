#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include <QUuid>
#include "../../../libs/api.h"
#include "../../../libs/item.h"
#include "../../../libs/inventory.h"
#include "../../../libs/user.h"

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

private:
	Ui::AddProduct *ui;
};

#endif // ADDPRODUCT_H
