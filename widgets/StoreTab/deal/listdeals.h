#ifndef LISTDEALS_H
#define LISTDEALS_H

#include <QDialog>
#include "../../../libs/deal.h"
#include "../../../libs/api.h"

namespace Ui {
class ListDeals;
}

class ListDeals : public QDialog
{
	Q_OBJECT

public:
	explicit ListDeals(QWidget *parent = nullptr);
	~ListDeals();

private slots:
	void on_btn_search_clicked();

private:
	Ui::ListDeals *ui;

	std::vector<data::Deal> dv;

};

#endif // LISTDEALS_H
