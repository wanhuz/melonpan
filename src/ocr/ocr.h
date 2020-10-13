#pragma once
#include <qstring.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


class Ocr {
public:
	Ocr();
	~Ocr();
	QString recognize(Pix* image);


private:
	tesseract::TessBaseAPI* api;
};



