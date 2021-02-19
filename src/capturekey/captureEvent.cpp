#include "../capturekey/captureEvent.h"
#include "../capturekey/capturekey.h"
#include "../ui/frame.h"
#include <qdebug.h>


captureEvent::captureEvent() {

	capturekeypress = new capturekey();
	frame = new Frame();
	ocr = new Ocr();
	connect(capturekeypress, SIGNAL(keyStateChanged()), this, SLOT(captureOCR()));
}

captureEvent::~captureEvent() {
	capturekeypress->disable();
	captureThread.quit();
	captureThread.wait();
}

void captureEvent::stop() {
	capturekeypress->disable();
}

void captureEvent::start() {
	capturekeypress->setEnable();

	if (!capturekeypress->isRunning()) {
		capturekeypress->start();
	}

}


void captureEvent::captureOCR() {
	frame->setBoxSize();
	QPixmap screenshot = frame->shootScreenshot();
	frame->show();
	frame->activateWindow();
	Pix* pix = Util::qPixMap2PIX(&screenshot);
	QString text = ocr->recognize(pix);
	emit OcrResult(text);
}

