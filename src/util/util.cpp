#include "util.h"
#include <qimage.h>
#include <Windows.h>
#include <qdebug.h>
#include <iostream>
#include <locale>
#include <qtextcodec.h>
#include "mecab/mecab.h"
#include <qmessagebox.h>

#pragma QT_NO_CAST_FROM_ASCII
#pragma QT_NO_CAST_TO_ASCII
#pragma QT_NO_CAST_FROM_BYTEARRAY

#define CHECK(eval) if (! eval) { \
   const char *e = tagger ? tagger->what() : MeCab::getTaggerError(); \
   std::cerr << "Exception:" << e << std::endl; \
   delete tagger; \
   return -1; }

/*QPixmap to Leptonica's Pix conversion*/
Pix* Util::qPixMap2PIX(QPixmap* pixmap) {
	Pix* pix;
	QImage qimage;
	l_uint32* lines;
	
	qimage = QImage(pixmap->toImage());

	int dpm = 300 / 0.0254; // ~300 DPI
	qimage.setDotsPerMeterX(dpm);
	qimage.setDotsPerMeterY(dpm);

	qimage = qimage.rgbSwapped();
	int width = qimage.width();
	int height = qimage.height();
	int depth = qimage.depth();
	int wpl = qimage.bytesPerLine() / 4;

	pix = pixCreate(width, height, depth);
	pixSetWpl(pix, wpl);
	pixSetColormap(pix, NULL);
	l_uint32* datas = pix->data;

	for (int y = 0; y < height; y++) {
		lines = datas + y * wpl;
		QByteArray a((const char*)qimage.scanLine(y), qimage.bytesPerLine());
		for (int j = 0; j < a.size(); j++) {
			*((l_uint8*)lines + j) = a[j];
		}
	}
	return pixEndianByteSwapNew(pix);
}

/*Send CTRL+C key input to Windows*/
int Util::sendKeyInput() {
	INPUT inputs[4];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_RCONTROL;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 0x43;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = VK_RCONTROL;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = 0x43;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	if (uSent != ARRAYSIZE(inputs)) {
		printf("Sendinput failed");
		return 1;
	}

	return 0;
}

/*Extract and return root word from Japanese sentence. Only return first word in a given string*/
QString Util::getRootWord(QString targetWord) {


	//QString to const char conversion
	QByteArray array = targetWord.toLocal8Bit();
	const char* data = array.constData();

	//Init MeCab
	MeCab::Model* model = MeCab::createModel("");
	MeCab::Tagger* tagger = model->createTagger();
	CHECK(tagger);

	const char* result = tagger->parse(data);
	CHECK(result);

	//Get root word of first word in the sentence
	QString resultQString(result);
	QStringList resultQStrings = resultQString.split("\t");

	if (!(resultQStrings.at(0).contains("EOS"))) {
		resultQStrings = resultQStrings[1].split(",");
		return resultQStrings[6];
	}

	return "";
	
}