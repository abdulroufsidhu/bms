#ifndef AUTHSCREEN_H
#define AUTHSCREEN_H

#include <QDialog>
#include <QMessageBox>
#include "./libs/api.h"
#include "./widgets/login.h"
#include "./widgets/signup.h"

namespace Ui {
	class AuthScreen;
}

class AuthScreen : public QDialog
{
	Q_OBJECT

public:
	explicit AuthScreen(QWidget *parent = nullptr);
	~AuthScreen();

private slots:

private:
	Ui::AuthScreen *ui;
};

#endif // AUTHSCREEN_H
