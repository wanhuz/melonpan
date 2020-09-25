#include "ui/KanjiProgram.h"
#include <QtWidgets/QApplication>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <qtextcodec.h>
#include "ui/MainWindow.h"

QString runOCR() {
    char * outText;
    QString outstring;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "jpn")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead("../test/17sx.jpg");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    outstring = QString::fromUtf8(outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return outstring;
}


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    
    QApplication a(argc, argv);
    QString text = runOCR();
    MainWindow m;
    m.displayOCRresult(text);
    m.show();


    return a.exec();
}
