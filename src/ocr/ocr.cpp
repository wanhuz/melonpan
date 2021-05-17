#include "ocr.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <qmessagebox.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <qdir.h>
#include <qdebug.h>



Ocr::Ocr() {
    api = new tesseract::TessBaseAPI();
    //Path to tesseract Data
    QString resPath = QDir::currentPath();
    resPath = resPath.replace("/", "\\");
    resPath = resPath + "\\res\\tessdata\\";
    resPath = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\tessdata\\"; //Debug Mode
    QByteArray resPath_char = resPath.toLocal8Bit();
    const char* resPath_char2 = resPath_char.data();
    qDebug() << resPath;
    
    if (api->Init(resPath_char2, "jpn_vert_fast")) {
        QMessageBox err;
        err.setText("Could not initialize Tesseract file at " + resPath + " .Program will now exit ");
        err.setIcon(QMessageBox::Critical);
        err.exec();
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(10);
    }
}


QString Ocr::recognize(Pix* image) {

    char* outText;
    QString outstring;

    // Open input image with leptonica library
    api->SetPageSegMode(tesseract::PageSegMode(5));
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    outstring = QString::fromUtf8(outText);

    // Destroy used object and release memory
    delete[] outText;
    pixDestroy(&image);

    return outstring;
}

Ocr::~Ocr() {
    api->End();
    delete api;
}