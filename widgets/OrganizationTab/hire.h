#ifndef HIRE_H
#define HIRE_H

#include <QDialog>
#include "../../libs/api.h"
#include "../../libs/person.h"
#include "../../libs/job.h"
#include "../../libs/user.h"
#include "../../libs/disablemousescroll.h"

namespace Ui {
	class Hire;
}

class Hire : public QDialog
{
	Q_OBJECT

public:
	explicit Hire(QWidget *parent = nullptr);
	~Hire();

private slots:
	void on_btn_hire_clicked();

private:
	Ui::Hire *ui;
};

#endif // HIRE_H
