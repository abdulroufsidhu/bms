#ifndef SELL_H
#define SELL_H

#include <QDialog>

namespace Ui {
	class Sell;
}

class Sell : public QDialog
{
	Q_OBJECT

public:
	explicit Sell(QWidget *parent = nullptr);
	~Sell();

private:
	Ui::Sell *ui;
};

#endif // SELL_H
