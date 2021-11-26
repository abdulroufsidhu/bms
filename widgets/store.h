#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QMessageBox>
#include "./libs/api.h"

namespace Ui {
	class Store;
}

class Store : public QWidget
{
	Q_OBJECT

public:
	explicit Store(QWidget *parent = nullptr);
	~Store();

	void updateItemsList(std::string where = "");
private slots:
	void initiate();

	void on_tabWidget_currentChanged(int index);

	void on_btn_list_filter_clicked();

	void on_cb_list_branches_currentIndexChanged(const QString &arg1);

	void on_le_update_serial_returnPressed();

	void on_btn_update_item_clicked();

private:
	Ui::Store *ui;
};

#endif // STORE_H
