#include "capturekey.h"
#include <Windows.h>
#include <WinUser.h>

capturekey::capturekey() {
	this->setKey();
}

int capturekey::startCapture(int captureType) {
	if (captureType == 0) {
		this->enableOCR = true;
		this->enableTextGeneric = false;
	}
	else if (captureType == 1) {
		this->enableTextGeneric = true;
		this->enableOCR = false;
	}
	
	return 0;
}

int capturekey::stopCapture(int captureType) {
	if (captureType == 0) {
		this->enableOCR = false;
	}
	else if (captureType == 1) {
		this->enableTextGeneric = false;
	}
	
	return 0;
}


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

bool capturekey::keyPressed(int key) {
	return (GetAsyncKeyState(key) & (0x8000 != 0)); //Why does this work? I dont know
}

int capturekey::setKey() {
	keyOCR = VK_LCONTROL;
	keyTextGeneric = VK_LCONTROL;
	return 0;
}
