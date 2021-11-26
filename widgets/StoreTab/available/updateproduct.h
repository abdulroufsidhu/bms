#ifndef UPDATEPRODUCT_H
#define UPDATEPRODUCT_H

#include <QDialog>
#include "../../../libs/api.h"
#include "../../../libs/user.h"
#include "../../../libs/inventory.h"

namespace Ui {
	class UpdateProduct;
}

class UpdateProduct : public QDialog
{
	Q_OBJECT

public:
	explicit UpdateProduct(QWidget *parent = nullptr);
	~UpdateProduct();

private slots:
	void on_le_update_serial_returnPressed();

	void on_btn_update_item_clicked();

private:
	Ui::UpdateProduct *ui;
};

#endif // UPDATEPRODUCT_H
