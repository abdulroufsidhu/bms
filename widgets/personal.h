#ifndef PERSONAL_H
#define PERSONAL_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
	class Person;
}

class Personal : public QWidget
{
	Q_OBJECT

public:
	explicit Personal (QWidget *parent = nullptr);
	~Personal ();

private slots:
	void on_btn_return_to_business_clicked();

	void on_btn_return_to_job_clicked();

private:
	Ui::Person *ui;
};

#endif // PERSONAL_H
