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

private slots:
    void on_btn_generate_uuid_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::Store *ui;
};

#endif // STORE_H
