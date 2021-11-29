#ifndef SELL_H
#define SELL_H

#include <QDialog>
#include "../../attrvalwdgt.h"

namespace Ui {
	class Sell;
}

class Sell : public QDialog
{
	Q_OBJECT

public:
	explicit Sell(QWidget *parent = nullptr);
	~Sell();

private slots:
	void on_btn_plus_clicked();

	void on_pushButton_clicked();

private:
	Ui::Sell *ui;

	QVector<AttrValWdgt *> avwQvec ;

};

#endif // SELL_H
