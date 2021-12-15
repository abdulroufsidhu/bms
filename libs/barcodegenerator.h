#ifndef BARCODEGENERATOR_H
#define BARCODEGENERATOR_H

#include "./common_headers.h"
#include <QString>

#define CODE128_B_START 0x00CB
#define CODE128_STOP 0x00CE

class BarcodeGenerator
{
public:
	BarcodeGenerator();

	QString generateBarcode(QString * string);

private:
	/** Adds start/check/stop characters to the code */
	QString encodeBarcode(QString* code);

	/** Calculates the checksum character from the code */
	int calculateCheckCharacter(QString* code);

	int codeToChar(int code);
	int charToCode(int ch);
};

#endif // BARCODEGENERATOR_H
