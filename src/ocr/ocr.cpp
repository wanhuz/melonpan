#include "ocr.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <qmessagebox.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <qdir.h>
#include <qdebug.h>

#ifdef DEBUG_MODE
#define ABSTESSDATAPATH tessDataPath = "C:\\xxx\\melonpan\\res\\tessdata\\"
#else
#define ABSTESSDATAPATH
#endif

Ocr::Ocr() {
    QString tessDataPath;

    api = new tesseract::TessBaseAPI();

    tessDataPath = QDir::currentPath();
    tessDataPath = tessDataPath.replace("/", "\\");
    tessDataPath = tessDataPath + "\\res\\tessdata\\";

    ABSTESSDATAPATH;

    QByteArray tessDataPath_char = tessDataPath.toLocal8Bit();
    const char* tessDataPath_char2 = tessDataPath_char.data();
    
    if (api->Init(tessDataPath_char2, "jpn_vert_zodiac3539")) {
        QMessageBox err;
        err.setText("Could not initialize Tesseract file at " + tessDataPath + "\nProgram will now exit ");
        err.setIcon(QMessageBox::Critical);
        err.exec();
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(3);
    }

}


QString Ocr::recognize(Pix* image) {
    char* outText;
    QString outstring;

    api->SetPageSegMode(tesseract::PageSegMode(5));
    api->SetImage(image);

    outText = api->GetUTF8Text();
    outstring = QString::fromUtf8(outText);

    pixDestroy(&image);

    return outstring;
}

Ocr::~Ocr() {
    api->End();
    delete api;
}