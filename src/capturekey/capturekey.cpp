#include "capturekey.h"
#include <Windows.h>
#include <WinUser.h>

capturekey::capturekey() {
	this->setKey();
}

int capturekey::setEnable() {
	this->enable = true;
	return 0;
}

int capturekey::disable() {
	this->enable = false;
	return 0;
}

void capturekey::run() {
	while (enable) {
		if (keyPressed(key)) {
			emit keyStateChanged();
		}
	}
}

bool capturekey::keyPressed(int key) {
	return (GetAsyncKeyState(key) & (0x8000 != 0)); //Why does this work? I dont know
}

int capturekey::setKey() {
	key = VK_CONTROL;
	return 0;
}
