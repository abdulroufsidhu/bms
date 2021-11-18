#ifndef ORG_H
#define ORG_H

#include <QWidget>
#include <QMessageBox>
#include "./libs/api.h"
#include <./libs/email.h>
#include <./libs/user.h>

namespace Ui {
class Organization;
}

class Org : public QWidget
{
    Q_OBJECT

public:
    explicit Org(QWidget *parent = nullptr);
    ~Org ();

private slots:
    void on_btn_register_clicked();

    void on_btn_relocate_clicked();

    void on_btn_revoke_clicked();

    void on_btn_add_branch_clicked();

    void on_btn_hire_clicked();

private:
    Ui::Organization *ui;
};

#endif // ORG_H
