#include "capturekey.h"
#include <Windows.h>
#include <WinUser.h>

capturekey::capturekey() {
	this->setKey();
}

int capturekey::startCapture(CaptureType captureType) {
	if (captureType == OCR) {
		this->enableOCR = true;
		this->enableTextGeneric = false;
	}
	else if (captureType == TEXT_GENERIC) {
		this->enableTextGeneric = true;
		this->enableOCR = false;
	}
	
	return 0;
}

int capturekey::stopCapture(CaptureType captureType) {
	if (captureType == OCR) {
		this->enableOCR = false;
	}
	else if (captureType == TEXT_GENERIC) {
		this->enableTextGeneric = false;
	}
	
	return 0;
}

//While loop and checking for key press increased CPU usage
void capturekey::run() {
	while (enableOCR) {
		if (keyPressed(keyOCR)) {
			emit OCRkeyStateChanged();
		}
	}
	while (enableTextGeneric) {
		if (keyPressed(keyTextGeneric)) {
			emit TextkeyStateChanged();
		}
	}
}

/*If a particular key is pressed, return true*/
bool capturekey::keyPressed(int key) {
	return (GetAsyncKeyState(key) & (0x8000 != 0)); //Why does this work? I dont know
}

int capturekey::setKey() {
	keyOCR = VK_LCONTROL;
	keyTextGeneric = VK_LCONTROL;
	return 0;
}
