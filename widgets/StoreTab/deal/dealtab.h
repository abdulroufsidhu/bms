#ifndef DEALTAB_H
#define DEALTAB_H

#include <QDialog>
#include "../../../libs/api.h"
#include "./sell.h"
#include "./listdeals.h"

namespace Ui {
	class DealTab;
}

class DealTab : public QDialog
{
	Q_OBJECT

public:
	explicit DealTab(QWidget *parent = nullptr);
	~DealTab();

private:
	Ui::DealTab *ui;
};

#endif // DEALTAB_H
