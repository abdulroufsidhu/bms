#ifndef HIRE_H
#define HIRE_H

#include <QDialog>

namespace Ui {
	class Hire;
}

class Hire : public QDialog
{
	Q_OBJECT

public:
	explicit Hire(QWidget *parent = nullptr);
	~Hire();

private:
	Ui::Hire *ui;
};

#endif // HIRE_H
