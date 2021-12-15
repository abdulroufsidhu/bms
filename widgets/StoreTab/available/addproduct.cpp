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

	double MmToDot = 8; //Printer DPI = 203 => 8 dots per mm FORMULAE IS printerDPI / 25.375 ==> dpi(dots per inch) to dpmm (dots per milimeter)
	QPainter painter;
//	painter().begin(&printer);

	QRect barcodeRect = QRect(5*MmToDot,10*MmToDot,67.5*MmToDot,10*MmToDot);
	QRect barcodeTextRect = QRect(5*MmToDot,20.5*MmToDot,67.5*MmToDot,5*MmToDot);

	QFont barcodefont = QFont("Code 128", 16, QFont::Normal);
	barcodefont.setLetterSpacing(QFont::AbsoluteSpacing,0.0);
//	painter.setFont(barcodefont);

	QString temp = this->ui->le_serial->text();

//	QRcode *qrcode = QRcode_encodeString(temp.toStdString().c_str(),1,QRecLevel::QR_ECLEVEL_H,QRencodeMode::QR_MODE_8,1);

	QRcode *qrcode = QRcode_encodeString8bit(temp.toStdString().c_str(),1,QRecLevel::QR_ECLEVEL_H);

	BarcodeGenerator bg = BarcodeGenerator( );
	QString qstr = bg.generateBarcode( &temp );

	QString arr = qstr;
//	painter.drawText(barcodeRect, Qt::AlignCenter, arr);

	QPixmap qrmap(100,100);

	painter.begin(&qrmap);

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor("white"));

	for (short i = 0; i< qrcode->width; i++) {
		for (short j=0; j< qrcode->width; j++) {
			if (qrcode->data[i * qrcode->width + j] & 1) {
				// draw black at (j,i)
				const double rx1=(j+1), ry1=(i+1);
				QRectF r(rx1, ry1, 1, 1 );
				painter.drawRects(&r,1);
			} else {
				// draw white at (j,i)
			}
		}
	}

	painter.end();
	painter.begin(&printer);
	QRectF rf(QPointF(0,0),QSizeF(100,100));
	painter.drawPixmap(rf,qrmap,qrmap.rect());

	painter.setFont(QFont("PT Sans", 6));

	painter.drawText(barcodeTextRect, Qt::AlignCenter, temp);

	painter.end();

	QRcode_free(qrcode);

}

