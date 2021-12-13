#ifndef ITEMDETAILS_H
#define ITEMDETAILS_H

#include <QDialog>
#include "../../attrvalwdgt.h"
#include "../../../libs/api.h"
#include "../../../libs/inventory.h"


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
	void on_btn_plus_clicked();

	void on_btn_insert_attrib_clicked();

	void on_btn_remove_last_clicked();

	void on_btn_conf_serial_clicked();

private:
	QVector<AttrValWdgt *> avwQvec ;

	Ui::ItemDetails *ui;
};

#endif // ITEMDETAILS_H
