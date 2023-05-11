#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    a.setQuitOnLastWindowClosed(false);
    m.show();
    return a.exec();
}
