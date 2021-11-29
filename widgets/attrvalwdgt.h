#ifndef ATTRVALWDGT_H
#define ATTRVALWDGT_H

#include <QDialog>

namespace Ui {
	class AttrValWdgt;
}

class AttrValWdgt : public QDialog
{
	Q_OBJECT

public:
	std::string attr, val;

public:
	explicit AttrValWdgt(QWidget *parent = nullptr);
	~AttrValWdgt();
	static short int& getInstancesCount();

private slots:
	void on_cb_attr_currentIndexChanged(const QString &arg1);

	void on_cb_val_currentIndexChanged(const QString &arg1);

private:
	Ui::AttrValWdgt *ui;
	static short int instancesCount;

protected:
	bool eventFilter(QObject *obj, QEvent *ev) override;

};

#endif // ATTRVALWDGT_H
