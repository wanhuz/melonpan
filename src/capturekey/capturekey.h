#pragma once
#include <qthread.h>

class capturekey : public QThread {
	Q_OBJECT;

public:
	capturekey();
	int startCapture(int captureType);
	int stopCapture(int captureType);
	int setKey();
	const int OCR = 0;
	const int TEXT_GENERIC = 1;
	

private:
	bool enableOCR;
	bool enableTextGeneric;
	int keyOCR;
	int keyTextGeneric;
	bool keyPressed(int key);
	void run() override;


signals:
	void OCRkeyStateChanged();
	void TextkeyStateChanged();

};