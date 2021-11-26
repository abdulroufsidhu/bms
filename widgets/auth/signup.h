#pragma once
#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include "ui_signup.h"
#include "../../libs/api.h"
#include "../../libs/location.h"
#include "../../libs/person.h"
#include "../../libs/user.h"
#include "../../libs/auth.h"
#include "../../mainwindow.h"
#include <QCompleter>

namespace Ui {
	class Signup;
}

class Signup : public QWidget
{
	Q_OBJECT

public:
	explicit Signup(QWidget *parent = nullptr);
	~Signup();

private slots:

	void on_btn_signup_clicked();

private:
	Ui::Signup *ui;
};

#endif // SIGNUP_H
