#pragma once
#include <qthread.h>

class capturekey : public QThread {
	Q_OBJECT;

public:
	enum CaptureType {OCR, TEXT_GENERIC};
	capturekey();
	int startCapture(CaptureType captureType);
	int stopCapture(CaptureType captureType);
	int setKey();

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