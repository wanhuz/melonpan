#pragma once
#include <qobject.h>
#include "../ui/frame.h"
#include "../ocr/ocr.h"
#include "../capturekey/capturekey.h"
#include "../dict/dict.h"
#include <qclipboard.h>

class MainController : public QObject
{
	Q_OBJECT;

public:
	MainController();
	void killCaptureKey();
	void startCaptureKeyOCR();
	void startCaptureKeyTextGeneric();
	void stopCaptureKey();
	QVector<QStringList> searchDict(QString searchStr);

private:
	Frame* frame;
	Ocr* ocr;
	capturekey *capturekeypress;
	Dict* dict;
	QClipboard* clipboard;
	

private slots:
	void captureOCR();
	void captureTextGeneric();
	void setSearchBox();

signals:
	void OcrResult(QString OcrText);

};