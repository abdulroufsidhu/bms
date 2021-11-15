#ifndef ORG_H
#define ORG_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Org;
}

class Org : public QWidget
{
    Q_OBJECT

public:
    explicit Org(QWidget *parent = nullptr);
    ~Org ();

private:
    Ui::Org *ui;
};

#endif // ORG_H
