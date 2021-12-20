#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QMessageBox>
#include "../libs/api.h"
#include "../libs/user.h"

namespace Ui {
	class Home;
}

class Home : public QWidget
{
	Q_OBJECT

public:
	explicit Home(QWidget *parent = nullptr);
	~Home();

	void updateCBattribAddVal();
private slots:
	void on_btn_add_attrib_clicked();

	void on_btn_attrib_add_val_clicked(std::string attrib = "");

	void on_cb_branch_list_currentIndexChanged(int index);

	void on_btn_remove_attrib_clicked();

	void on_btn_attrib_remove_val_clicked();

	void on_pushButton_clicked();

private:
	Ui::Home *ui;
};

#endif // HOME_H
