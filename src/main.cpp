#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"
#include <windows.h>
#pragma execution_character_set( "utf-8" )

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001);
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}
