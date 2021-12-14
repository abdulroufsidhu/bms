#ifndef ITEMDETAILS_H
#define ITEMDETAILS_H

#include <QDialog>
#include "../../../libs/api.h"
#include "../../../libs/inventory.h"
#include "../attributesclass.h"

namespace Ui {
class ItemDetails;
}

class ItemDetails : public QDialog
{
	Q_OBJECT


public:
	explicit ItemDetails(QWidget *parent = nullptr);
	~ItemDetails();

	QString getSerial();
	QString getPrice();
	QString getDiscount();
	QString getColour();
	QString getAttributes();
	QString getQuantity();

private slots:
	void on_btn_conf_serial_clicked();

private:
	AttributesClass *ac;
	Ui::ItemDetails *ui;
};

#endif // ITEMDETAILS_H
