#include <QtWidgets/QApplication>
#include "../ui/MainWindow.h"
#include "../ui/frame.h"
#include "shana.h"


shana::shana()
{
    QApplication a(argc, argv);
    
    //QString text = runOCR();
    //MainWindow m;
    Frame kek;

    //m.displayOCRresult(text);
    //m.show();


    return a.exec();
}
