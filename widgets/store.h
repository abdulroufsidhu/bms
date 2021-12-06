#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QMessageBox>
#include "./libs/api.h"
#include "../libs/user.h"
#include "../libs/item.h"
#include "../libs/inventory.h"
#include "./StoreTab/available/available.h"
#include "./StoreTab/deal/dealtab.h"

namespace Ui {
	class Store;
}

class Store : public QWidget
{
	Q_OBJECT

public:
	explicit Store(QWidget *parent = nullptr);
	~Store();

private:
	Ui::Store *ui;
	Available* available = NULL;

};

#endif // STORE_H
