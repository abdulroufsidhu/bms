#ifndef PERSONAL_H
#define PERSONAL_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Personal;
}

class Personal : public QWidget
{
    Q_OBJECT

public:
    explicit Personal (QWidget *parent = nullptr);
    ~Personal ();

private:
    Ui::Personal *ui;
};

#endif // PERSONAL_H
