#ifndef QRCODE_H
#define QRCODE_H

#include <QPainter>
#include <QPixmap>
#include <qrencode.h>

namespace data {
	class QRCode;
}

class data::QRCode
{
public:
	QRCode();

	static QPixmap genereate_from_str_8_bit(QString *value) ;

};

#endif // QRCODE_H
