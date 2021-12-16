#include "addproduct.h"
#include "ui_addproduct.h"

#include <QFontDatabase>
#include <QPainter>
#include <qrencode.h>

AddProduct::AddProduct(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddProduct)
{
	ui->setupUi(this);

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	ui->cb_add_item_branch->addItems(data::User::getCurrentUser()->getBranchesNamesList() );
	ac = new AttributesClass();
	ui->v_layout->addWidget(this->ac);

	ui->sb_price->installEventFilter(new DisableMouseScroll());
	ui->sb_quantity->installEventFilter(new DisableMouseScroll());
	ui->cb_add_item_branch->installEventFilter(new DisableMouseScroll());
	ui->cb_item_type->installEventFilter(new DisableMouseScroll());

}

AddProduct::~AddProduct()
{
	delete ui;
}

void AddProduct::on_btn_add_inventory_clicked()
{

	if (data::User::getCurrentUser()->getOrganizationVec().size() < 1) return;

	std::string select, from, where, query;
	QString itemType, name, modal, manufacturer, vendor, serial, version, price, quantity;
	itemType = ui->cb_item_type->currentText();
	name = ui->le_item_name->text();
	modal = ui->le_modal->text();
	manufacturer = ui->le_manufecturer->text();
	vendor = ui->le_vendor->text();
	serial = ui->le_serial->text();
	price = ui->sb_price->text();
	version = ui->le_version->text();
	quantity = ui->sb_quantity->text();

	query = "INSERT INTO items"
					"(name, company, itemtype, modal, version, vendor)"
					" SELECT '" + name.toStdString() + "','" + manufacturer.toStdString() + "','" + itemType.toStdString() + "','" +modal.toStdString() + "','" + version.toStdString() + "','" + vendor.toStdString() + "' WHERE NOT EXISTS ( SELECT name, company, itemtype, modal, version, vendor FROM items WHERE name = '" + name.toStdString() + "' AND COMPANY = '" + manufacturer.toStdString() + "' AND itemtype = '" + itemType.toStdString() + "' AND modal = '" + modal.toStdString() + "' AND version = '" + version.toStdString() + "' AND vendor = '" + vendor.toStdString() + "')";

	db::PSQL::getInstance()->set(&query);

	select = "*";
	from = "items";
	where = "itemtype = '" + itemType.toStdString() +"' AND company ='" + manufacturer.toStdString() + "' AND name ='" + name.toStdString() + "' AND modal ='" + modal.toStdString() + "' AND vendor ='" + vendor.toStdString() + "' AND version ='" + version.toStdString() +"'";

	std::vector<data::Item> iv;
	db::PSQL::getInstance()->get(&select, &from, &where, &iv);

	query = "INSERT INTO inventory(itemid, serial, branchid, price, quantity, attributes ) values ( '"+iv.at(0).getId()+"','"+serial.toStdString()+"','"+data::User::getCurrentUser()->getBranchVec().at(ui->cb_add_item_branch->currentIndex()).getId()+"'," +price.toStdString()+ "," + quantity.toStdString() + ",'" + this->ac->getAttributes().toStdString() + "')" ;

	std::string err = db::PSQL::getInstance()->set(&query);

	if (!err.empty()) {
			ui->le_serial->setStyleSheet("color: #f00");
			return;
		}
	ui->le_serial->setStyleSheet("");
	ui->cb_item_type->setCurrentIndex(0);
	ui->le_item_name->clear();
	ui->le_modal->clear();
	ui->le_manufecturer->clear();
	ui->le_vendor->clear();
	ui->le_serial->clear();
	ui->sb_price->setValue(0);
	ui->sb_quantity->setValue(0);
	ui->sb_price->clear();
	ui->le_version->clear();

}

void AddProduct::on_btn_generate_uuid_clicked()
{

	QUuid uid = QUuid::createUuid();
	//0 default for uuid enclosed in curly braces with dashes 1 for with dashes without curly braces and 3 for without dashes as well this 3rd cannot be reused with QUuid class
	ui->le_serial->setVisible(true);
//	ui->le_serial->setText(uid.toString(QUuid::StringFormat(1)));
	std::string qstr = uid.toString(QUuid::StringFormat(3)).toStdString();

	ui->le_serial->setText(qstr.c_str());

}


void AddProduct::on_pushButton_clicked()
{

	QPrinter printer ;
	printer.setPageMargins(0.0,0.0,0.0,0.0,QPrinter::Millimeter);
	printer.setPageOrientation(QPageLayout::Landscape);
	printer.setPaperSize(QPrinter::B9);
	QPrintDialog dialogue (&printer, this);
	dialogue.setWindowTitle("Print Barcode");
	if (dialogue.exec() != QDialog::Accepted) return;

	int id = QFontDatabase::addApplicationFont(":/fonts/fonts/code128.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont code128(family,32,QFont::Normal);
	QImage barcode(190,30, QImage::Format_Mono);
	barcode.fill(1);

 //Printer DPI = 203 => 8 dots per mm FORMULAE IS printerDPI / 25.375 ==> dpi(dots per inch) to dpmm (dots per milimeter) // its there because it could be helpful in future.

	QString temp = this->ui->le_serial->text();
	QPainter painter;

	QPixmap qrmap = data::QRCode::genereate_from_str_8_bit(&temp);

	painter.begin(&printer);
	QRectF rf(QPointF(0,0),QSizeF(qrmap.width() ,qrmap.height() ));
	painter.drawPixmap(rf,qrmap,qrmap.rect());
	QFont sys_def(QFont().defaultFamily());
	sys_def.setPointSize(5);
	painter.setFont(sys_def);
	painter.drawText(QPointF(qrmap.width() + sys_def.pointSize(), qrmap.height()/2),temp);

	painter.end();

}

