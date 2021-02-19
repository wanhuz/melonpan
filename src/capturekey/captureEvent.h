#pragma once
#include <qobject.h>
#include <qthread.h>
#include "../ui/frame.h"
#include "../ocr/ocr.h"
#include "../util/util.h"
#include <qstring.h>
#include "../capturekey/capturekey.h"

class captureEvent : public QObject
{
	Q_OBJECT
	QThread captureThread;

public:
	captureEvent();
	~captureEvent();
	void start();
	void stop();

private:
	Frame* frame;
	Ocr* ocr;
	capturekey *capturekeypress;

private slots:
	void captureOCR();

signals:
	void OcrResult(QString OcrText);

};