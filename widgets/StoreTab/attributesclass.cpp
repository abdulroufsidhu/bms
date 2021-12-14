#include "attributesclass.h"
#include "ui_attributesclass.h"
#include <QTabBar>

AttributesClass::AttributesClass(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AttributesClass)
{
	ui->setupUi(this);
	this->ui->tab_widget_attributes->tabBar()->installEventFilter(new DisableMouseScroll());

}

void AttributesClass::setAttributes(QString attr) { this->ui->te_attributes_text->setPlainText(attr); }

QTextEdit* AttributesClass::getTextEditAttr() {return  this->ui->te_attributes_text;}

QString AttributesClass::getAttributes() { return this->ui->te_attributes_text->toPlainText(); }

AttributesClass::~AttributesClass()
{
	delete ui;
}

void AttributesClass::on_btn_remove_last_clicked()
{
	delete this->avwQvec.last();
	this->avwQvec.removeLast();
}

void AttributesClass::on_btn_plus_clicked()
{
	this->avwQvec.append( new AttrValWdgt());
	ui->v_layout_tab_selectors->addWidget(this->avwQvec.last());
}

void AttributesClass::on_btn_insert_attrib_clicked()
{
	ui->te_attributes_text->clear();
	ui->te_attributes_text->toHtml();
	QString t = QString("<table>");
	for (auto i : this->avwQvec) {
			t+=( ("<tr> <td> " + i->attr + " :- </td>" + "<td> " + i->val + " </td></tr> ").c_str() );
		}
	t += ("</table>");
	ui->te_attributes_text->textCursor().insertHtml(t);
	ui->tab_widget_attributes->setCurrentIndex(1);
}

