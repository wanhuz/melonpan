#include "ui/KanjiProgram.h"
#include <QtWidgets/QApplication>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <qtextcodec.h>

QString runOCR() {
    char * outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "jpn")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead("C:/Users/WanHuz/Documents/KanjiTomo v2/test/17sx.jpg");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    QString outstring;
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
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    QApplication a(argc, argv);
    KanjiProgram w;
    QString text = runOCR();
    w.displayOCRresult(text);
    
    w.show();
    return a.exec();
}
