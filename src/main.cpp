#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"
#include "ui/popup.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}
