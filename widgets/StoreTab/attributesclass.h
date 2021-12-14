#ifndef ATTRIBUTESCLASS_H
#define ATTRIBUTESCLASS_H

#include <QDialog>
#include <QTextEdit>
#include "../attrvalwdgt.h"
#include "../../libs/disablemousescroll.h"

namespace Ui {
class AttributesClass;
}

class AttributesClass : public QDialog
{
	Q_OBJECT

public:
	explicit AttributesClass(QWidget *parent = nullptr);
	~AttributesClass();

	QString getAttributes();

	QTextEdit* getTextEditAttr();

	void setAttributes(QString attr);

private slots:
	void on_btn_plus_clicked();

	void on_btn_insert_attrib_clicked();

	void on_btn_remove_last_clicked();

private:
	QVector<AttrValWdgt *> avwQvec ;

	Ui::AttributesClass *ui;
};

#endif // ATTRIBUTESCLASS_H
