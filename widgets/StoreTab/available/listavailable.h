#ifndef LISTAVAILABLE_H
#define LISTAVAILABLE_H

#include <QDialog>
#include "../../../libs/api.h"
#include "../../../libs/user.h"
#include "../../../libs/inventory.h"


namespace Ui {
	class ListAvailable;
}

class ListAvailable : public QDialog
{
	Q_OBJECT

public:
	explicit ListAvailable(QWidget *parent = nullptr);
	~ListAvailable();

	void updateItemsList(std::string where = "");
private slots:
	void on_btn_list_filter_clicked();

	void on_cb_list_branches_currentIndexChanged(int index);

private:
	Ui::ListAvailable *ui;
};

#endif // LISTAVAILABLE_H
