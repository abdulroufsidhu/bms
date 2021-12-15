#include "barcodegenerator.h"

#include <QMessageBox>

BarcodeGenerator::BarcodeGenerator()
{

}

QString BarcodeGenerator::generateBarcode(QString *string) {
	return this->encodeBarcode(string);
}

QString BarcodeGenerator::encodeBarcode(QString *code)
{
		QString encoded;

		encoded.append(QChar((CODE128_B_START))); //Start set with B Code 104
		encoded.append(code);
		encoded.append(QChar(calculateCheckCharacter(code)));
		encoded.append(QChar((CODE128_STOP))); //End set with Stop Code 106

		return encoded;
}

int BarcodeGenerator::calculateCheckCharacter(QString* code)
{
		QByteArray encapBarcode(code->toUtf8()); //Convert code to utf8

		//Calculate check character
		long long sum = CODE128_B_START; //The sum starts with the B Code start character value
		int weight = 1; //Initial weight is 1

		foreach(char ch, encapBarcode) {
				int code_char = charToCode((int)ch); //Calculate character code
				sum += code_char*weight; //add weighted code to sum
				weight++; //increment weight

		}

		int remain = sum%103; //The check character is the modulo 103 of the sum

		//Calculate the font integer from the code integer
		if(remain >= 0x005F)
				remain += 0x0064;
		else
				remain += 0x0021;
		return remain;
}

int BarcodeGenerator::codeToChar(int code)
{
		return code + 0x0064;
}

int BarcodeGenerator::charToCode(int ch)
{
		return ch - 0x0021;
}
