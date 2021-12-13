#ifndef SELL_H
#define SELL_H

#include <QDialog>
#include "./itemdetails.h"

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
	void on_btn_sell_clicked();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::Sell *ui;
	QVector<ItemDetails *> iDetQvec;
};

#endif // SELL_H
