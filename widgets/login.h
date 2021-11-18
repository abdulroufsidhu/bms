#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ui_login.h"
#include "../libs/api.h"
#include "../libs/person.h"
#include "../libs/user.h"
#include "../libs/auth.h"
#include "../mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
