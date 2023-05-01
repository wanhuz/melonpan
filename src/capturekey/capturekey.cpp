#include "capturekey.h"
#include <Windows.h>
#include <WinUser.h>
#include <qdebug.h>
#pragma comment(lib, "user32.lib")

capturekey* capturekey::capturekeys = NULL;
HHOOK capturekey::captHook = NULL;

capturekey::capturekey() {
	this->setKey(); //Set default key
	capturekeys = this;
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
	UnhookWindowsHookEx(captHook);
	capturekeys->exit();

	return 0;
}

//Run the thread to start the hook
void capturekey::run() {
	capturekeys->startHook();
	capturekeys->exec();
}

int capturekey::setKey() {
	keyOCR = VK_OEM_3;
	keyTextGeneric = VK_OEM_3;
	return 0;
}

LRESULT CALLBACK capturekey::LowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYDOWN)
	{
		//Get Key information
		KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);

		wchar_t buffer[5];

		BYTE keyboard_state[256];
		GetKeyboardState(keyboard_state);

		HKL keyboard_layout = GetKeyboardLayout(0);

		//Do Microsoft's vodoo magic
		char lpszName[0x100] = { 0 };
		
		DWORD dwMsg = 1;
		dwMsg += cKey.scanCode << 16;
		dwMsg += cKey.flags << 24;

		//Get key in unicode
		int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);
		int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer, 4, 0, keyboard_layout);
		buffer[4] = L'\0';

		//Emit signal if match
		if (cKey.vkCode == capturekeys->keyOCR && capturekeys->enableOCR) {
			emit capturekeys->OCRkeyStateChanged();
		}
		else if (cKey.vkCode == capturekeys->keyTextGeneric && capturekeys->enableTextGeneric) {
			emit capturekeys->TextkeyStateChanged();
		}
	
	}

	return CallNextHookEx(captHook, nCode, wParam, lParam);
}

void capturekey::startHook() {
	captHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyBoardProc, NULL, 0);

	if (captHook == NULL) {
		printf("Hook initialization failed");
		return;
	}


}

