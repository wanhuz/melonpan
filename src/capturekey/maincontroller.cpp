#include "../capturekey/maincontroller.h"
#include "../capturekey/capturekey.h"
#include "../ui/frame.h"
#include "../util/util.h"
#include "../dict/DictLoader.h"
#include "../dict/dict.h"


MainController::MainController() {
	DictLoader* dictloader = new DictLoader();
	dict = new Dict();
	frame = new Frame();
	ocr = new Ocr();
	capturekeypress = new capturekey();

	dictloader->setDict(dict);
	dictloader->start();

	connect(capturekeypress, SIGNAL(keyStateChanged()), this, SLOT(captureOCR()));
}

void MainController::killCaptureKey() {
	capturekeypress->disable();
	capturekeypress->quit();
	capturekeypress->wait();
}

void MainController::stopCaptureKey() {
	capturekeypress->disable();
}

void MainController::startCaptureKey() {
	capturekeypress->setEnable();

	if (!capturekeypress->isRunning()) {
		capturekeypress->start();
	}

}

QVector<QStringList> MainController::searchDict(QString searchStr) {
	return dict->search(searchStr);
}

void MainController::captureOCR() {
	frame->setBoxSize();
	QPixmap screenshot = frame->shootScreenshot();
	frame->show();
	frame->activateWindow();
	Pix* pix = Util::qPixMap2PIX(&screenshot);
	QString text = ocr->recognize(pix);
	emit OcrResult(text);
}

//void MainWindow::captureText() {
//    QClipboard* clipboard = QApplication::clipboard();
//    QString clipText = clipboard->text();
//    textbox->setText(clipText);
//}