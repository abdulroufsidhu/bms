#include "qrcode.h"

data::QRCode::QRCode() {}

QPixmap data::QRCode::genereate_from_str_8_bit(QString * value) {

	QPixmap qrmap(40,40);
	if (value->isEmpty()) return qrmap;

	QPainter painter;
	QRcode *qrcode = QRcode_encodeString8bit(value->toStdString().c_str(),1,QRecLevel::QR_ECLEVEL_H);

	painter.begin(&qrmap);

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor("white"));
	painter.drawRect(0,0,qrmap.width(),qrmap.height());
	painter.setBrush(QColor("black"));

	double scale = qrmap.width() / qrcode->width;

	for (short i = 0; i< qrcode->width; i++) {
		for (short j=0; j< qrcode->width; j++) {
			if (qrcode->data[i * qrcode->width + j] & 1) {
				// draw black at (j,i)
				const double rx1=(j+1) * scale, ry1=(i+1) * scale;
				QRectF r(rx1, ry1, scale, scale);
				painter.drawRects(&r,1);
			} else {
				// draw white at (j,i)
			}
		}
	}

	painter.end();
	QRcode_free(qrcode);
	return qrmap;
}
