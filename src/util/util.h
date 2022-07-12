#pragma once
#include <leptonica/allheaders.h>
#include <qpixmap.h>

class Util {

public:
	static Pix* qPixMap2PIX(QPixmap* pixmap);
	static int sendKeyInput();
	static QString getRootWord(QString targetWord);

};