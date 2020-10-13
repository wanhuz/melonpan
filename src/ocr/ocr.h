#pragma once
#include <qstring.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


class Ocr {
public:
	Ocr();
	QString recognize(Pix* image);
};



