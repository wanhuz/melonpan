#pragma once
#include <qthread.h>
#include <Windows.h>

class capturekey : public QThread {
	Q_OBJECT;

public:
	enum CaptureType {OCR, TEXT_GENERIC};
	capturekey();
	int startCapture(CaptureType captureType);
	int stopCapture(CaptureType captureType);
	int setKey();
	


private:
	static HHOOK captHook;
	static capturekey* capturekeys;
	bool enableTextGeneric;
	int keyOCR;
	int keyTextGeneric;
	bool enableOCR;
	
	void run() override;
	void startHook();
	void stopHook();
	static LRESULT CALLBACK LowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);

signals:
	void OCRkeyStateChanged();
	void TextkeyStateChanged();

};