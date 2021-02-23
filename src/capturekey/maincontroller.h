#pragma once
#include <qobject.h>
#include "../ui/frame.h"
#include "../ocr/ocr.h"
#include "../capturekey/capturekey.h"
#include "../dict/dict.h"

class MainController : public QObject
{
	Q_OBJECT;

public:
	MainController();
	void killCaptureKey();
	void startCaptureKey();
	void stopCaptureKey();
	QVector<QStringList> searchDict(QString searchStr);

private:
	Frame* frame;
	Ocr* ocr;
	capturekey *capturekeypress;
	Dict* dict;
	

private slots:
	void captureOCR();

signals:
	void OcrResult(QString OcrText);

};