#include "ocr.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


Ocr::Ocr() {

}

QString Ocr::recognize(Pix* image) {
    char* outText;
    QString outstring;


    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "jpn_vert_fast")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    api->SetPageSegMode(tesseract::PageSegMode(5));
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
